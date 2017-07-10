// AudioSourceImpl.h.h
// Created by Caner Korkmaz on 2/7/2017.
// Copyright 2017 Caner Korkmaz
//

#ifndef SOCKETPLAY_AUDIOSOURCEIMPL_H_H
#define SOCKETPLAY_AUDIOSOURCEIMPL_H_H

#include "Windows/AudioSource.h"
#include <thread>

namespace socketplay::windows {

BasicAudioSource::BasicAudioSource(unsigned short num_channels, unsigned long samples_per_sec)
    : num_channels_(num_channels),
      delta_phase_constant_(2.0 * M_PI / samples_per_sec) {
}
void BasicAudioSource::load_data(user_ptr<float> data, uint32_t frame_count) {
  MY_LOG << "Loading data with hertz " << hertz_ << '\n';
  auto dphase = delta_phase();
  for (uint32_t frame = 0; frame < frame_count; ++frame) {
    const auto value = sin(phase_) * 1.f;
    for (unsigned short channel = 0; channel < num_channels_; ++channel) {
      *data++ = static_cast<float>(value);
    }
    phase_ += dphase;
  }
}

template<typename AudioSource>
WindowsSource<AudioSource>::WindowsSource(ComPtr <IAudioClient> audio_client)
    : audio_client_(audio_client) {
  WAVEFORMATEX *waveformat_raw;
  throw_if_failed(audio_client_->GetMixFormat(&waveformat_raw));
  format_ = co_make_unique(waveformat_raw);

  MY_LOG << "Got mix format:\n"
         << "\tNumber of Channels: " << format_->nChannels << '\n'
         << "\tSamples per Second: " << format_->nSamplesPerSec << '\n'
         << "\tBits per Sample: " << format_->wBitsPerSample << '\n'
         << "\tBlock Size: " << format_->cbSize << '\n'
         << "\tAverage Bytes per Second: " << format_->nAvgBytesPerSec << '\n'
         << "\tNumber of Block Aligns: " << format_->nBlockAlign << '\n'
         << "\tFormat Tag: " << format_->wFormatTag << '\n';

  throw_if_failed(audio_client->Initialize(AUDCLNT_SHAREMODE_SHARED, 0, requested_duration_, 0,
                                           format_.get(), nullptr));
  MY_LOG << "Initialized audio client\n";

  throw_if_failed(audio_client->GetBufferSize(&buffer_size_));
  MY_LOG << "Got buffer size: " << buffer_size_ << '\n';

  throw_if_failed(audio_client_->GetService(IID_PPV_ARGS(&render_client_)));

  actual_duration_ =
      static_cast<REFERENCE_TIME>(static_cast<double>(reftimes_per_second_) * buffer_size_ / format_->nSamplesPerSec);
  sleep_duration_ = static_cast<DWORD>(actual_duration_ / (reftimes_per_millisec_ * 2));

  source_ = std::make_unique<AudioSource>(format_->nChannels, format_->nSamplesPerSec);
}
template<typename AudioSource>
bool WindowsSource<AudioSource>::load_initial_data() {
  start_ = std::chrono::system_clock::now();
  start_set_ = true;

  BYTE *data;
  throw_if_failed(render_client_->GetBuffer(buffer_size_, &data));
  MY_LOG << "Got initial buffer\n";

  auto result = load_data_impl_(data, buffer_size_);

  throw_if_failed(render_client_->ReleaseBuffer(buffer_size_, result));
  MY_LOG << "Released initial buffer\n";

  return result != AUDCLNT_BUFFERFLAGS_SILENT;
}
template<typename AudioSource>
bool WindowsSource<AudioSource>::load_data() {
  uint32_t num_frames_padding;
  throw_if_failed(audio_client_->GetCurrentPadding(&num_frames_padding));

  auto num_frames_available = buffer_size_ - num_frames_padding;
  MY_LOG << "Playing for " << sleep_duration_ << "ms with " << num_frames_available << " frames\n";

  BYTE *data;
  throw_if_failed(render_client_->GetBuffer(num_frames_available, &data));

  auto result = load_data_impl_(data, num_frames_available);

  throw_if_failed(render_client_->ReleaseBuffer(num_frames_available, result));

  return result != AUDCLNT_BUFFERFLAGS_SILENT;
}
template<typename AudioSource>
void WindowsSource<AudioSource>::start() const {
  throw_if_failed(audio_client_->Start());
}
template<typename AudioSource>
void WindowsSource<AudioSource>::stop() const {
  throw_if_failed(audio_client_->Stop());
}
template<typename AudioSource>
void WindowsSource<AudioSource>::sleep() const {
  using namespace std::chrono;
  static auto _duration = milliseconds{sleep_duration_};
  static auto _begin = system_clock::now();
  static auto _now = system_clock::now();
  _now = system_clock::now();
  static milliseconds _elapsed;
  _elapsed = duration_cast<milliseconds>(_now - _begin);
  std::this_thread::sleep_for(_duration - _elapsed);
  MY_LOG << "Elapsed " << _elapsed.count() << "ms -> " << (_duration - _elapsed).count() << "ms\n";
  _begin = system_clock::now();
}
template<typename AudioSource>
typename WindowsSource<AudioSource>::flag_type WindowsSource<AudioSource>::load_data_impl_(WindowsSource::data_type *data,
                                                                                           uint32_t frame_count) {
  using namespace std::chrono;

  source_->load_data(reinterpret_cast<float *>(data), frame_count);

  // TODO: Fix this and return SILENT(?) when required, requires info from source so actually the source should return this info
  //auto end = system_clock::now();
  //return (start_set_ && duration<milliseconds>(end - start_).count() > 2000) ? AUDCLNT_BUFFERFLAGS_SILENT : 0;
  // Always playing
  return 0;
}

}

#endif //SOCKETPLAY_AUDIOSOURCEIMPL_H_H

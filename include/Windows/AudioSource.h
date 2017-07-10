// AudioSource.h
// Created by Caner Korkmaz on 2/7/2017.
// Copyright 2017 Caner Korkmaz
//

#ifndef SOCKETPLAY_AUDIOSOURCE_H
#define SOCKETPLAY_AUDIOSOURCE_H


#include <fstream>

#include <chrono>
#include <cmath>

#include "ComHelper.h"
#include "Logger.h"

namespace socketplay::windows{

using namespace ABI::Windows::Foundation;
using namespace Microsoft::WRL;

template<typename T>
using user_ptr = T*;

class BasicAudioSource {
 public:
  BasicAudioSource(unsigned short num_channels, unsigned long samples_per_sec);

  void load_data(user_ptr<float> data, uint32_t frame_count);
 private:
  double delta_phase() const { return hertz_ * delta_phase_constant_; }

  unsigned short num_channels_ = 0;
  double phase_ = 0.;

  const double delta_phase_constant_;
  double hertz_ = 440.;
};


template<typename AudioSource>
class WindowsSource {
 public:
  using data_type = unsigned char;
  using flag_type = unsigned long;
  using reference_time = long long;

  static constexpr reference_time reftimes_per_second_ = 10000000;
  static constexpr reference_time reftimes_per_millisec_ = reftimes_per_second_/1000;
  static constexpr reference_time requested_duration_ = reftimes_per_second_;
 public:
  explicit WindowsSource(ComPtr<IAudioClient> audio_client);

  bool load_initial_data();

  bool load_data();

  void start() const;
  void stop() const;
  void sleep() const;

  uint32_t buffer_size() const { return buffer_size_; }
  reference_time actual_duration() const { return actual_duration_; }
  unsigned long sleep_duration() const { return sleep_duration_; }
 private:
  flag_type load_data_impl_(data_type *data, uint32_t frame_count);

  ComPtr<IAudioClient> audio_client_;
  ComPtr<IAudioRenderClient> render_client_;
  co_taskmem_ptr<WAVEFORMATEX> format_;
  std::unique_ptr<AudioSource> source_;

  uint32_t buffer_size_;

  std::chrono::time_point<std::chrono::system_clock> start_;
  bool start_set_ = false;

  reference_time actual_duration_;
  unsigned long sleep_duration_;
};

}

#include "detail/AudioSourceImpl.h"


#endif //SOCKETPLAY_AUDIOSOURCE_H

// AudioPlayerWindows.cpp
// Created by Caner Korkmaz on 2/7/2017.
// Copyright 2017 Caner Korkmaz
//
#include "Windows/AudioPlayerWindows.h"
#include "Windows/ComHelper.h"
#include "Windows/AudioSource.h"

#include <thread>
#include <atomic>

using namespace socketplay::windows;

class AudioPlayer::impl {
 public:
  CoContext context;
  ComPtr<IAudioClient> audio_client;
  std::thread worker;
  std::atomic<bool> should_stop = false;

  impl(){
    MY_LOG << "Initialized COM\n";
    audio_client = activate_audio_client_from_endpoint(
        get_default_audio_endpoint(get_device_enumerator(CLSCTX_ALL), eRender, eConsole), CLSCTX_ALL);
    MY_LOG << "Created audio client\n";
  }

  struct Player{
    AudioPlayer::impl& impl_;
    explicit Player(AudioPlayer::impl& impl)
      : impl_(impl){

    }
    void operator()() const{
      // Set the source audio format to waveformat
      WindowsSource<BasicAudioSource> source(impl_.audio_client);
      MY_LOG << "Created Windows source from Basic Audio Source\n";

      auto playing = source.load_initial_data();

      source.start();
      MY_LOG << "Started playing\n";

      while (playing && !impl_.should_stop) {
        source.sleep();
        playing = source.load_data();
      }

      source.sleep();

      source.stop();
      MY_LOG << "Stopped playing\n";
    }
  };
};

AudioPlayer::AudioPlayer()
  : pimpl_(std::make_unique<impl>()){
}

AudioPlayer::~AudioPlayer() noexcept(true) {

}

void AudioPlayer::start() {
  pimpl_->should_stop=false;
  pimpl_->worker = std::thread(impl::Player{*pimpl_});
}
void AudioPlayer::stop() {
  pimpl_->should_stop = true;
  pimpl_->worker.join();
}

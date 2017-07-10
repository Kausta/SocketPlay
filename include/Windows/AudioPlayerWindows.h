// AudioPlayerWindows.h
// Created by Caner Korkmaz on 2/7/2017.
// Copyright 2017 Caner Korkmaz
//

#ifndef SOCKETPLAY_AUDIOPLAYERWINDOWS_H
#define SOCKETPLAY_AUDIOPLAYERWINDOWS_H

#include <memory>

namespace socketplay::windows{
class AudioPlayer{
 public:
  AudioPlayer();
  ~AudioPlayer() noexcept(true);

  AudioPlayer(const AudioPlayer& other) = delete;
  AudioPlayer& operator=(const AudioPlayer& other) = delete;
  AudioPlayer(AudioPlayer&& other) = default;
  AudioPlayer& operator=(AudioPlayer&& other) = default;

  void start();
  void stop();
 private:
  class impl;
  std::unique_ptr<impl> pimpl_;
};
}

#endif //SOCKETPLAY_AUDIOPLAYER_H

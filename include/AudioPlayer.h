// AudioPlayer.h
// Created by Caner Korkmaz on 7/7/2017.
// Copyright 2017 Caner Korkmaz
//

#ifndef SOCKETPLAY_AUDIOPLAYER_H
#define SOCKETPLAY_AUDIOPLAYER_H

#ifdef WIN32

#include "Windows/AudioPlayerWindows.h"

namespace socketplay{
using AudioPlayer = socketplay::windows::AudioPlayer;
}

#endif

#endif //SOCKETPLAY_AUDIOPLAYER_H

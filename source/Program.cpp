// Program.cpp
// Created by Caner Korkmaz on 20/5/2017.
// Copyright 2017 Caner Korkmaz
//

#include <iostream>
#include "Program.h"
#include "ProgramOptionsParser.h"
#include "AudioPlayer.h"

using namespace socketplay;

Program::Program() = default;

void Program::run_stream_mode(StreamOptions &&options) {
  std::cout << "Running in stream mode.\n";
  std::cout << "Streaming from " << options.port << '\n';
}
void Program::run_stream_file_mode(StreamFileOptions &&options) {
  std::cout << "Running in file stream mode.\n";
  std::cout << "Streaming " << options.source << " from " << options.port << '\n';
}
void Program::run_play_mode(PlayOptions &&options) {
  std::cout << "Running in play mode.\n";
  std::cout << "Target: " << options.target_address << ":" << options.target_port << '\n';

#ifdef WIN32
  AudioPlayer player;
  player.start();

  std::cin.get();

  player.stop();
#endif
}


// Program.h
// Created by Caner Korkmaz on 20/5/2017.
// Copyright 2017 Caner Korkmaz
//

#ifndef SOCKETPLAY_PROGRAM_H
#define SOCKETPLAY_PROGRAM_H

#include <vector>
#include <string>
#include "ProgramMode.h"

namespace socketplay {
/**
 * @brief Entry class for Socket Play app
 */
class Program {
 public:
  /// Default constructor for program
  Program();

  /// Run in stream mode with given options
  void run_stream_mode(StreamOptions&& options);
  /// Run in file streaming mode with given options
  void run_stream_file_mode(StreamFileOptions&& options);
  /// Run in playing mode with given options
  void run_play_mode(PlayOptions&& options);
 private:

};
}

#endif //SOCKETPLAY_PROGRAM_H

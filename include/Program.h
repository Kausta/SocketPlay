// Program.h
// Created by Caner Korkmaz on 20/5/2017.
// Copyright 2017 Caner Korkmaz
//

#ifndef SOCKETPLAY_PROGRAM_H
#define SOCKETPLAY_PROGRAM_H

#include <vector>
#include <string>

namespace socketplay {
/**
 * @brief Entry class for Socket Play app
 */
class Program {
 public:
  /// Default constructor for program
  Program();

  /**
   * Runs the application from given arguments
   * @param argc Argument count
   * @param argv Arguments
   */
  void run(int argc, const char *const *argv);
 private:

};
}

#endif //SOCKETPLAY_PROGRAM_H

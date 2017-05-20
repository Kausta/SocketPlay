// ProgramOptions.h
// Created by Caner Korkmaz on 20/5/2017.
// Copyright 2017 Caner Korkmaz
//

#ifndef SOCKETPLAY_PROGRAMOPTIONS_H
#define SOCKETPLAY_PROGRAMOPTIONS_H

#include "ProgramMode.h"

namespace socketplay {
class ProgramOptionsParser;
class ProgramOptions {
 public:
  explicit ProgramOptions(const ProgramOptionsParser &parser);

  ProgramMode mode() const { return mode_; }
  const std::string &source_file() const { return source_file_; }
 private:
  void parse_stream_options_(const ProgramOptionsParser &parser);
  // TODO: parse_play_options

  ProgramMode mode_;
  std::string source_file_;
};
}
#endif //SOCKETPLAY_PROGRAMOPTIONS_H

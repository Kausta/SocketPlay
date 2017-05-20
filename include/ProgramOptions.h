// ProgramOptions.h
// Created by Caner Korkmaz on 20/5/2017.
// Copyright 2017 Caner Korkmaz
//

#ifndef SOCKETPLAY_PROGRAMOPTIONS_H
#define SOCKETPLAY_PROGRAMOPTIONS_H

#include "ProgramMode.h"

namespace socketplay {
class ProgramOptionsParser;
/**
 * Program Options helper to check and get values from Program Options Parser
 */
class ProgramOptions {
 public:
  /**
   * Create Program Options from given parser
   * @param parser Parser to read parsed options from
   */
  explicit ProgramOptions(const ProgramOptionsParser &parser);

  /// Returns program mode
  ProgramMode mode() const { return mode_; }
  /// Returns source file name
  /// @pre Mode is Stream
  const std::string &source_file() const { return source_file_; }
  /// Returns target address
  /// @pre Mode is Play
  const std::string &target_address() const { return target_address_; }
  /// Returns target port
  /// @pre Mode is Play
  const std::string &target_port() const { return target_port_; }
 private:
  /// Parses options for Stream mode
  void parse_stream_options_(const ProgramOptionsParser &parser);
  /// Parses options for Play mode
  void parse_play_options_(const ProgramOptionsParser &parser);

  ProgramMode mode_;
  std::string source_file_;
  std::string target_address_;
  std::string target_port_;
};
}
#endif //SOCKETPLAY_PROGRAMOPTIONS_H

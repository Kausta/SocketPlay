// ProgramMode.h
// Created by Caner Korkmaz on 20/5/2017.
// Copyright 2017 Caner Korkmaz
//

#ifndef SOCKETPLAY_PROGRAMMODE_H
#define SOCKETPLAY_PROGRAMMODE_H

#include <string>

namespace socketplay {
enum class ProgramMode {
  HELP,
  VERSION,
  STREAM,
  STREAM_FILE,
  PLAY
};
struct GenericOptions {
  ProgramMode mode;

  explicit GenericOptions(ProgramMode mode_)
      : mode(mode_) {}
};
struct StreamOptions : GenericOptions {
  unsigned short port;

  explicit StreamOptions(unsigned short port_)
      : GenericOptions(ProgramMode::STREAM), port(port_) {}
};
struct StreamFileOptions : GenericOptions {
  std::string source;
  unsigned short port;

  explicit StreamFileOptions(std::string source_, unsigned short port_)
      : GenericOptions(ProgramMode::STREAM_FILE), source(std::move(source_)), port(port_) {}
};
struct PlayOptions : GenericOptions {
  std::string target_address;
  unsigned short target_port;

  explicit PlayOptions(std::string target_address_, unsigned short target_port_)
      : GenericOptions(ProgramMode::PLAY), target_address(std::move(target_address_)), target_port(target_port_) {}
};
}

#endif //SOCKETPLAY_PROGRAMMODE_H

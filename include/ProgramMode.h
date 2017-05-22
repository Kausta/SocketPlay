// ProgramMode.h
// Created by Caner Korkmaz on 20/5/2017.
// Copyright 2017 Caner Korkmaz
//

#ifndef SOCKETPLAY_PROGRAMMODE_H
#define SOCKETPLAY_PROGRAMMODE_H

#include <string>
#include <variant>

namespace socketplay {
enum class ProgramMode {
  HELP,
  VERSION,
  STREAM,
  STREAM_FILE,
  PLAY
};
struct GenericOptions {

};
struct StreamOptions {
  unsigned short port;

  explicit StreamOptions(unsigned short port_)
      : port(port_) {}
};
struct StreamFileOptions {
  std::string source;
  unsigned short port;

  explicit StreamFileOptions(std::string source_, unsigned short port_)
      : source(std::move(source_)), port(port_) {}
};
struct PlayOptions {
  std::string target_address;
  unsigned short target_port;

  explicit PlayOptions(std::string target_address_, unsigned short target_port_)
      : target_address(std::move(target_address_)), target_port(target_port_) {}
};
using OptionsContainer = std::variant<std::monostate, GenericOptions, StreamOptions, StreamFileOptions, PlayOptions>;
}

#endif //SOCKETPLAY_PROGRAMMODE_H

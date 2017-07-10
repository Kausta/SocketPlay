// Logger.h
// Created by Caner Korkmaz on 2/7/2017.
// Copyright 2017 Caner Korkmaz
//

#ifndef SOCKETPLAY_LOGGER_H
#define SOCKETPLAY_LOGGER_H

#include <iostream>
#include <chrono>

namespace socketplay::detail {
class Logger {
 public:
  std::ostream &os_;

  static Logger& instance(){
    static Logger logger{std::cout};
    return logger;
  }

  template<typename T>
  Logger &operator<<(T &&t) {
    os_ << t;
    return *this;
  }

  template<typename T>
  Logger const &operator<<(T &&t) const {
    os_ << t;
    return *this;
  }

  Logger const &operator<<(std::ostream &(*func)(std::ostream &)) const {
    func(os_);
    return *this;
  }
 private:
  explicit Logger(std::ostream &os)
      : os_(os) {
  }
};

inline std::ostream& log(const char* filename, int line, const char* function){
  return Logger::instance().os_ << "[LOG(" << filename << ":" << line << ":" << function << ")]: ";
}
inline std::ostream& log(const char* level, const char* filename, int line, const char* function){
  return Logger::instance().os_ << "[" << level << "(" << filename << ":" << line << ":" << function << ")]: ";
}
inline void log_flush(){
  socketplay::detail::Logger::instance().os_ << std::flush;
}
}
#define MY_LOG socketplay::detail::log(__FILE__, __LINE__, __func__)
#define MY_WARN socketplay::detail::log("WARN", __FILE__, __LINE__, __func__)
#define MY_ERROR socketplay::detail::log("ERROR", __FILE__, __LINE__, __func__)

#endif //SOCKETPLAY_LOGGER_H

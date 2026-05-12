#pragma once

#include <string>

class Logger {
public:
  Logger();
  ~Logger();
  static Logger& getInstance();
  
  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;
  Logger(Logger&&) = delete;
  Logger& operator=(Logger&&) = delete;

  void info(const std::string &message);
  void warning(const std::string &message);
  void error(const std::string &message);
  void debug(const std::string &message);
};
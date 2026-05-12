#include "Logger.hpp"
#include <iostream>

Logger::Logger() {
  this->info("Logger created");

}
Logger::~Logger() {
  this->info("Logger destroyed");
}
Logger& Logger::getInstance() {
  static Logger instance;
  return instance;
}
void Logger::info(const std::string &message) {
  std::cout << "INFO: " << message << std::endl;
}
void Logger::warning(const std::string &message) {
  std::cout << "WARNING: " << message << std::endl;
}
void Logger::error(const std::string &message) {
  std::cout << "ERROR: " << message << std::endl;
}
void Logger::debug(const std::string &message) {
  std::cout << "DEBUG: " << message << std::endl;
}

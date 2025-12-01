// Ed Callaghan
// Logging interface
// December 2025

#include "Logger.h"

Logger::level_t Logger::INFO    = 2;
Logger::level_t Logger::DETAIL  = 4;
Logger::level_t Logger::VERBOSE = 6;

Logger::Logger(std::string path): path(path){
  this->fout.open(this->path);
}

Logger::~Logger(){
  this->fout.close();
}

void Logger::write(const Logger::level_t level, const std::string& content){
  std::string buff;
  this->now(buff);
  std::string line = buff + ' ' + std::to_string(level) + ' ' + content;
  std::lock_guard lock(this->mutex);
  std::cout  << line << std::endl;
  this->fout << line << std::endl;
}

void Logger::now(std::string& out){
  time_t now = time(NULL);
  out = std::string(ctime(&now));
  out = out.substr(0, out.size()-1);
}

// Ed Callaghan
// Logging interface
// December 2025

#ifndef LOGGER_H
#define LOGGER_H

#include <ctime>
#include <iostream>
#include <fstream>
#include <mutex>
#include <string>

class Logger{
  public:
    using level_t = unsigned int;
    static level_t INFO;
    static level_t DETAIL;
    static level_t VERBOSE;

    Logger(std::string);
   ~Logger();

    void write(const level_t, const std::string&);

  protected:
    std::string path;
    std::ofstream fout;
    std::mutex mutex;

    void now(std::string&);

  private:
    /**/
};

#endif

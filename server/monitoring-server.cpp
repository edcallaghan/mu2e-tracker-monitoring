// Ed Callaghan
// Interface for monitoring tracker frontend queries over RS485 serial line
// August 2025

#include <ctime>
#include <string>
#include "DigitalConversionMap.h"
#include "Foyer.h"
#include "HardwareLoop.h"
#include "InitializeServer.h"
#include "Logger.h"
#include "StandardQueries.h"
#include "Queue.h"
#include "RS485Bus.h"
using namespace std;

std::string zero_padded_string(int field, unsigned int length){
  std::string casted = std::to_string(field);
  std::string rv;
  unsigned int pad = length - casted.size();
  for (unsigned int i = 0 ; i < pad ; i++){
    rv += "0";
  }
  rv += casted;
  return rv;
}

int main(int argc, char** argv){
  // begin logging
  time_t now = time(NULL);
  struct tm* fields = localtime(&now);
  std::string base = "/var/log/monitoring/monitoring-server.";
  std::string lpath = base
                    + zero_padded_string(fields->tm_year + 1900, 4)
                    + zero_padded_string(fields->tm_mon  + 1,    2)
                    + zero_padded_string(fields->tm_mday,        2)
                    + zero_padded_string(fields->tm_hour,        2)
                    + zero_padded_string(fields->tm_min,         2)
                    + zero_padded_string(fields->tm_sec,         2)
                    + "." + std::to_string(getpid())
                    + ".log";
  Logger logger(lpath);

  // claim hardware
  auto context = asio::io_context();
  RS485Bus bus("/dev/gpiochip4", 24,
               context,
               "/dev/ttyAMA0", 38400);

  // reserve task queue
  Queue queue(1024);

  // define readback conversions
  DigitalConversionMap conversions;
  define_standard_conversions(conversions);

  // connect to hardware
  std::thread hardware_thread(hardware_loop, std::ref(bus), std::ref(queue),
                              std::ref(logger));

  // begin listening for connections
  int sfd = initialize_server(12001, 512);
  std::thread foyer_thread(foyer, sfd, std::ref(queue), std::ref(conversions),
                           std::ref(logger));
  foyer_thread.join();

  return 0;
}

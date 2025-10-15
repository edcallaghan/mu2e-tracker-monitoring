// Ed Callaghan
// Interface for monitoring tracker frontend queries over RS485 serial line
// August 2025

#include <string>
#include "DigitalConversionMap.h"
#include "Foyer.h"
#include "HardwareLoop.h"
#include "InitializeServer.h"
#include "StandardQueries.h"
#include "Queue.h"
#include "RS485Bus.h"
using namespace std;

int main(int argc, char** argv){
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
  std::thread hardware_thread(hardware_loop, std::ref(bus), std::ref(queue));

  // begin listening for connections
  int sfd = initialize_server(12001, 512);
  std::thread foyer_thread(foyer, sfd, std::ref(queue), std::ref(conversions));
  foyer_thread.join();

  return 0;
}

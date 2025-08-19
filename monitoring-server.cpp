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

  /*
  RS485Bus::Address_t address = 400;
  RS485Bus::OpCode_t command = 252;
  RS485Bus::Payload_t payload;
  auto f = [address, command] (RS485Bus& bus, ostream& cout){
    RS485Bus::Payload_t payload;
    bus.send(address, command);
    bus.recv(payload);
    cout << to_string(payload) << endl;
  };
  std::thread tmp;
  for (size_t i = 0 ; i < 3 ; i++){
    tmp = std::thread(f, std::ref(bus), std::ref(cout));
    tmp.join();
  }
  */

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

  /*
  RS485Bus::Address_t address = 400;
  RS485Bus::OpCode_t command = 252;
  bus.send(address, command);

  RS485Bus::Payload_t payload;
  bus.recv(payload);

  cout << to_string(payload) << endl;

  PriorityQueue<int> queue(1024);
  queue.push(42);
  queue.push(99);
  cout << queue.pop() << endl;
  cout << queue.pop() << endl;
  */

  return 0;
}

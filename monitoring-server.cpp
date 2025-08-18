// Ed Callaghan
// Interface for monitoring tracker frontend queries over RS485 serial line
// August 2025

#include <string>
#include "InitializeServer.h"
#include "Foyer.h"
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

  // begin listening for connections
  int sfd = initialize_server(12001, 512);
  std::thread foyer_thread(foyer, sfd, std::ref(queue));
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

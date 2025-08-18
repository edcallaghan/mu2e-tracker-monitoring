// Ed Callaghan
// Interface for monitoring tracker frontend queries over RS485 serial line
// August 2025

#include <string>
#include "RS485Bus.h"
using namespace std;

int main(int argc, char** argv){
  auto context = asio::io_context();
  RS485Bus bus("/dev/gpiochip4", 24,
               context,
               "/dev/ttyAMA0", 38400);

  Address_t address = 400;
  OpCode_t command = 252;
  bus.send(address, command);

  Payload_t payload;
  bus.recv(payload);

  cout << to_string(payload) << endl;

  return 0;
}

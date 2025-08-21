// Ed Callaghan
// Work loop for hardware interaction
// August 2025

#include "HardwareLoop.h"

void hardware_loop(RS485Bus& bus, Queue& queue){
  bool timed_out = false;
  auto interval = std::chrono::milliseconds(10);
  RS485Bus::Payload_t payload;
  while (true){
    while (queue.size() < 1){
      std::this_thread::sleep_for(interval);
    }

    auto task = queue.pop();
    auto address = task->Address();
    auto opcode = task->OpCode();
    bus.send(address, opcode);
    bus.recv(payload, timed_out);

    task->SetReturn(payload);
    if (!timed_out){
      task->MarkComplete();
    }
    else{
      task->MarkTimedOut();
    }
  }
}

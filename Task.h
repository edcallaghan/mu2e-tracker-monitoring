// Ed Callaghan
// Simple bundle necessary to execute/return a single hardware query
// August 2025

#ifndef TASK_H
#define TASK_H

#include <condition_variable>
#include <mutex>
#include "RS485Bus.h"

class Task{
  public:
    Task(RS485Bus::Address_t, RS485Bus::OpCode_t);

    RS485Bus::Address_t Address();
    RS485Bus::OpCode_t OpCode();
    void Wait();
    bool IsComplete();
    void MarkComplete();
    void SetReturn(RS485Bus::Payload_t);
    RS485Bus::Payload_t Return();

  protected:
    RS485Bus::Address_t address;
    RS485Bus::OpCode_t opcode;
    std::mutex mutex;
    std::condition_variable condition;
    bool complete;
    RS485Bus::Payload_t rv;
};

#endif

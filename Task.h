// Ed Callaghan
// Simple bundle necessary to execute/return a single hardware query
// August 2025

#ifndef TASK_H
#define TASK_H

#include <condition_variable>
#include <memory>
#include <mutex>
#include "Messages.h"
#include "RS485Bus.h"

class Task{
  public:
    Task(RS485Bus::Address_t, RS485Bus::OpCode_t);

    RS485Bus::Address_t Address();
    RS485Bus::OpCode_t OpCode();
    void Wait();
    bool IsComplete();
    void MarkComplete();
    void SetReturn(Message_t*);
    std::shared_ptr<Message_t> Return();

  protected:
    RS485Bus::Address_t address;
    RS485Bus::OpCode_t opcode;
    std::mutex mutex;
    std::condition_variable condition;
    bool complete;
    std::shared_ptr<Message_t> rv;
};

#endif

// Ed Callaghan
// Simple bundle necessary to execute/return a single hardware query
// August 2025

#include "Task.h"

Task::Task(RS485Bus::Address_t address, RS485Bus::OpCode_t opcode):
    address(address), opcode(opcode), complete(false){
  /**/
}

RS485Bus::Address_t Task::Address(){
  auto rv = this->address;
  return rv;
}

RS485Bus::OpCode_t Task::OpCode(){
  auto rv = this->opcode;
  return rv;
}

void Task::Wait(){
  std::unique_lock lock(this->mutex);
  auto predicate = [this] () { return this->IsComplete(); };
  this->condition.wait(lock, predicate);
}

bool Task::IsComplete(){
  auto rv = this->complete;
  return rv;
}

void Task::MarkComplete(){
  this->complete = true;
}

void Task::SetReturn(Message_t* message){
  this->rv = std::shared_ptr<Message_t>(message);
}

std::shared_ptr<Message_t> Task::Return(){
  auto rv = this->rv;
  return rv;
}

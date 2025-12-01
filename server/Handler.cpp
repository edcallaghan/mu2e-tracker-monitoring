// Ed Callaghan
// Mediate messages from outside with hardware requests
// August 2025

#include "Handler.h"

void client_handler(const Connection connection, Queue& queue,
                    DigitalConversionMap& conversions, Logger& logger){
  std::string str_timeout = "Timeout";
  char* cstr_timeout = const_cast<char*>(str_timeout.c_str());
  Message_t* msg_timeout = message_wrap_chars(cstr_timeout);
  Message_t* message;
  std::mutex mutex;
  std::string textip = connection.AsString();
  while (0 < message_recv(&message, connection.fd)){
    // if connection closed unexpectedly, just abort
    if (errno == EPIPE){
      std::string line = "connection from " + textip + " closed";
      logger.write(Logger::INFO, line);
      break;
    }
    // bad message, just send back error
    if (message->valid != 1){
      std::string line = "bad message read from " + textip;
      logger.write(Logger::INFO, line);
      break;
    }

    // only accept RS485+addr+opcode
    if (message->count != 3){
      std::string line = "malformed message (blocks != 3) from " + textip;
      logger.write(Logger::INFO, line);
      break;
    }
    if (message->blocks[1]->type != 'U'){
      std::string line = "malformed message from " + textip;
      logger.write(Logger::INFO, line);
      break;
    }
    if (message->blocks[1]->count != 1){
      std::string line = "malformed message from " + textip;
      logger.write(Logger::INFO, line);
      break;
    }
    if (message->blocks[2]->type != 'U'){
      std::string line = "malformed message from " + textip;
      logger.write(Logger::INFO, line);
      break;
    }
    if (message->blocks[2]->count != 1){
      std::string line = "malformed message from " + textip;
      logger.write(Logger::INFO, line);
      break;
    }

    // this can be specified in the request
    priority_t priority = 100;

    // push into queue
    auto hwaddr = static_cast<RS485Bus::Address_t>(
      block_as_uint(message->blocks[1])
    );
    auto opcode = static_cast<RS485Bus::OpCode_t>(
      block_as_uint(message->blocks[2])
    );
    auto task = std::make_shared<Task>(hwaddr, opcode);
    queue.push(task, priority);

    // wait for task to complete
    task->Wait();

    // send output back to client
    if (task->IsComplete()){
      RS485Bus::Payload_t payload = task->Return();
      message = conversions.AsMessage(opcode, payload);
    }
    else if (task->IsTimedOut()){
      message = msg_timeout;
    }
    else{
      throw std::runtime_error("impossible state in client handler");
    }
    message_send(message, connection.fd);
  }

  std::string line = "connection from " + textip + " closed";
  logger.write(Logger::INFO, line);
}

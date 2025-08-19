// Ed Callaghan
// Mediate messages from outside with hardware requests
// August 2025

#ifndef HANDLER_H
#define HANDLER_H

#include <mutex>
#include <thread>
#include "DigitalConversionMap.h"
#include "Messages.h"
#include "Queue.h"
#include "Task.h"

class Connection{
  public:
    Connection(int fd, struct sockaddr_in address, int addrlen):
        fd(fd), address(address), addrlen(addrlen){
      /**/
    }
    int fd;
    struct sockaddr_in address;
    int addrlen;
};

void client_handler(const Connection, Queue&, DigitalConversionMap&);

#endif

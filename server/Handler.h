// Ed Callaghan
// Mediate messages from outside with hardware requests
// August 2025

#ifndef HANDLER_H
#define HANDLER_H

#include <mutex>
#include <stdexcept>
#include <thread>
#include "DigitalConversionMap.h"
#include "Logger.h"
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

    std::string AsString() const{
      char text[INET_ADDRSTRLEN];
      inet_ntop(AF_INET, &(this->address), text, INET_ADDRSTRLEN);
      std::string rv(text);
      return rv;
    }

  protected:
    /**/

  private:
    /**/
};

void client_handler(const Connection, Queue&, DigitalConversionMap&, Logger&);

#endif

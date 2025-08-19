// Ed Callaghan
// Listen for new connections and defer to client handler
// August 2025

#include "Foyer.h"

void foyer(const int sfd, Queue& queue, DigitalConversionMap& conversions){
  int cfd;
  struct sockaddr_in address;
  int addrlen = sizeof(address);

  while (true){
    cfd = accept(sfd, (struct sockaddr*) &address, (socklen_t*) &addrlen);
    if (cfd < 0){
        throw std::runtime_error("bad client connection");
    }

    Connection connection(cfd, address, addrlen);
    std::thread child(client_handler,
                      connection,
                      std::ref(queue),
                      std::ref(conversions));
    child.detach();
  }
}

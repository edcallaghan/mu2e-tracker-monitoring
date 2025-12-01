// Ed Callaghan
// Listen for new connections and defer to client handler
// August 2025

#include "Foyer.h"

void foyer(const int sfd, Queue& queue, DigitalConversionMap& conversions,
           Logger& logger){
  int cfd;
  struct sockaddr_in address;
  int addrlen = sizeof(address);

  while (true){
    cfd = accept(sfd, (struct sockaddr*) &address, (socklen_t*) &addrlen);
    if (cfd < 0){
        logger.write(Logger::INFO, "bad client connection");
        throw std::runtime_error("bad client connection");
    }

    Connection connection(cfd, address, addrlen);
    std::string line = "accepted connection from " + connection.AsString();
    logger.write(Logger::INFO, line);

    std::thread child(client_handler,
                      connection,
                      std::ref(queue),
                      std::ref(conversions),
                      std::ref(logger));
    child.detach();
  }
}

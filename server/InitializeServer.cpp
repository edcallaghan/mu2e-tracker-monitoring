// Ed Callaghan
// Begin listening on socket connection
// August 2025

#include "InitializeServer.h"

int initialize_server(unsigned int port, unsigned int backlog){
  // get socket
  int rv = socket(AF_INET, SOCK_STREAM, 0);
  if (rv < 0){
    throw std::runtime_error("bad socket fd");
  }

  // set options
  int opt = 1;
  if (setsockopt(rv, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                 &opt, sizeof(opt)) != 0){
    throw std::runtime_error("failed to set socket options");
  }

  // bind to port
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);
  if (bind(rv, (struct sockaddr*) &address, sizeof(address)) < 0){
    throw std::runtime_error("failed to bind to port" + std::to_string(port));
  }

  // listen
  if (listen(rv, backlog) < 0){
    throw std::runtime_error("failed to begin listening");
  }

  return rv;
}

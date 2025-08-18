// Ed Callaghan
// Begin listening on socket connection
// August 2025

#ifndef INITIALIZESERVER_H
#define INITIALIZESERVER_H

#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stddef.h>
#include <stdexcept>

int initialize_server(unsigned int, unsigned int);

#endif

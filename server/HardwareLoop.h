// Ed Callaghan
// Work loop for hardware interaction
// August 2025

#ifndef HARDWARELOOP_H
#define HARDWARELOOP_H

#include <chrono>
#include <thread>
#include "Logger.h"
#include "RS485Bus.h"
#include "Queue.h"

void hardware_loop(RS485Bus&, Queue&, Logger&);

#endif

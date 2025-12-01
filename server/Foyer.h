// Ed Callaghan
// Listen for new connections and defer to child handler
// August 2025

#ifndef FOYER_H
#define FOYER_H

#include <thread>
#include "DigitalConversionMap.h"
#include "Handler.h"
#include "Logger.h"

void foyer(const int, Queue&, DigitalConversionMap&, Logger&);

#endif

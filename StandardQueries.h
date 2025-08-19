// Ed Callaghan
// Opcodes and readback conversions for standard suite of operations
// August 2025

#ifndef STANDARDQUERIES_H
#define STANDARDQUERIES_H

#include <cmath>
#include "DigitalConversionMap.h"
#include "RS485Bus.h"

namespace StandardQueries{
  extern const RS485Bus::OpCode_t I3p3;
  extern const RS485Bus::OpCode_t I2p5;
  extern const RS485Bus::OpCode_t I1p8HV;
  extern const RS485Bus::OpCode_t IHV5p0;
  extern const RS485Bus::OpCode_t VDMBHV5p0;
  extern const RS485Bus::OpCode_t V1p8HV;
  extern const RS485Bus::OpCode_t V3p3HV;
  extern const RS485Bus::OpCode_t V2p5;
  extern const RS485Bus::OpCode_t Flow;
  extern const RS485Bus::OpCode_t AbsPressure;
  extern const RS485Bus::OpCode_t DMBTEMP;
  extern const RS485Bus::OpCode_t A3;
  extern const RS485Bus::OpCode_t I1p8CAL;
  extern const RS485Bus::OpCode_t I1p2;
  extern const RS485Bus::OpCode_t ICAL5p0;
  extern const RS485Bus::OpCode_t ADCSPARE;
  extern const RS485Bus::OpCode_t V3p3;
  extern const RS485Bus::OpCode_t VCAL5p0;
  extern const RS485Bus::OpCode_t V1p8CAL;
  extern const RS485Bus::OpCode_t V1p0;
  extern const RS485Bus::OpCode_t ROCPCBTEMP;
  extern const RS485Bus::OpCode_t HVPCBTEMP;
  extern const RS485Bus::OpCode_t CALPCBTEMP;
  extern const RS485Bus::OpCode_t RTD;
  extern const RS485Bus::OpCode_t V5KEY;
  extern const RS485Bus::OpCode_t KEYPCBTEMP;
  extern const RS485Bus::OpCode_t DCDCTEMP;
  extern const RS485Bus::OpCode_t V2p5KEY;
  extern const RS485Bus::OpCode_t ROC_RAIL_1V;
  extern const RS485Bus::OpCode_t ROC_RAIL_1p8V;
  extern const RS485Bus::OpCode_t ROC_RAIL_2p5V;
  extern const RS485Bus::OpCode_t ROC_TEMP;
  extern const RS485Bus::OpCode_t CAL_RAIL_1V;
  extern const RS485Bus::OpCode_t CAL_RAIL_1p8V;
  extern const RS485Bus::OpCode_t CAL_RAIL_2p5V;
  extern const RS485Bus::OpCode_t CAL_TEMP;
  extern const RS485Bus::OpCode_t HV_RAIL_1V;
  extern const RS485Bus::OpCode_t HV_RAIL_1p8V;
  extern const RS485Bus::OpCode_t HV_RAIL_2p5V;
  extern const RS485Bus::OpCode_t HV_TEMP;
  extern const RS485Bus::OpCode_t ID;
  extern const RS485Bus::OpCode_t HB;
  extern const RS485Bus::OpCode_t DBG;
} // namespace StandardQueries

void define_standard_conversions(DigitalConversionMap&);

#endif

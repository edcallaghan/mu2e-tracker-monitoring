// Ed Callaghan
// Opcodes and readback conversions for standard suite of operations
// August 2025

#include "StandardQueries.h"

namespace StandardQueries{
  const RS485Bus::OpCode_t I3p3          = 0;
  const RS485Bus::OpCode_t I2p5          = 1;
  const RS485Bus::OpCode_t I1p8HV        = 2;
  const RS485Bus::OpCode_t IHV5p0        = 3;
  const RS485Bus::OpCode_t VDMBHV5p0     = 4;
  const RS485Bus::OpCode_t V1p8HV        = 5;
  const RS485Bus::OpCode_t V3p3HV        = 6;
  const RS485Bus::OpCode_t V2p5          = 7;
  const RS485Bus::OpCode_t Flow          = 8;
  const RS485Bus::OpCode_t AbsPressure   = 9;
  const RS485Bus::OpCode_t DMBTEMP       = 10;
  const RS485Bus::OpCode_t A3            = 11;
  const RS485Bus::OpCode_t I1p8CAL       = 12;
  const RS485Bus::OpCode_t I1p2          = 13;
  const RS485Bus::OpCode_t ICAL5p0       = 14;
  const RS485Bus::OpCode_t ADCSPARE      = 15;
  const RS485Bus::OpCode_t V3p3          = 16;
  const RS485Bus::OpCode_t VCAL5p0       = 17;
  const RS485Bus::OpCode_t V1p8CAL       = 18;
  const RS485Bus::OpCode_t V1p0          = 19;
  const RS485Bus::OpCode_t ROCPCBTEMP    = 20;
  const RS485Bus::OpCode_t HVPCBTEMP     = 21;
  const RS485Bus::OpCode_t CALPCBTEMP    = 22;
  const RS485Bus::OpCode_t RTD           = 23;
  const RS485Bus::OpCode_t V5KEY         = 24;
  const RS485Bus::OpCode_t KEYPCBTEMP    = 25;
  const RS485Bus::OpCode_t DCDCTEMP      = 26;
  const RS485Bus::OpCode_t V2p5KEY       = 27;
  const RS485Bus::OpCode_t ROC_RAIL_1V   = 28;
  const RS485Bus::OpCode_t ROC_RAIL_1p8V = 29;
  const RS485Bus::OpCode_t ROC_RAIL_2p5V = 30;
  const RS485Bus::OpCode_t ROC_TEMP      = 31;
  const RS485Bus::OpCode_t CAL_RAIL_1V   = 32;
  const RS485Bus::OpCode_t CAL_RAIL_1p8V = 33;
  const RS485Bus::OpCode_t CAL_RAIL_2p5V = 34;
  const RS485Bus::OpCode_t CAL_TEMP      = 35;
  const RS485Bus::OpCode_t HV_RAIL_1V    = 36;
  const RS485Bus::OpCode_t HV_RAIL_1p8V  = 37;
  const RS485Bus::OpCode_t HV_RAIL_2p5V  = 38;
  const RS485Bus::OpCode_t HV_TEMP       = 39;
  const RS485Bus::OpCode_t ID            = 252;
  const RS485Bus::OpCode_t HB            = 253;
  const RS485Bus::OpCode_t DBG           = 254;
} // namespace StandardQueries

void define_standard_conversions(DigitalConversionMap& conversions){
  conversions.Register<double>(StandardQueries::I3p3,
    [] (RS485Bus::Payload_t x){
      auto rv = (x * 3.3 / (4096 * 0.006 * 20));
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::I2p5,
    [] (RS485Bus::Payload_t x){
      auto rv = (x * 3.3 / (4096 * 0.006 * 20));
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::I1p8HV,
    [] (RS485Bus::Payload_t x){
      auto rv = (x * 3.3 / (4096 * 0.006 * 20));
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::IHV5p0,
    [] (RS485Bus::Payload_t x){
      auto rv = (x * 3.3 / (4096 * 0.5 * 20));
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::VDMBHV5p0,
    [] (RS485Bus::Payload_t x){
      auto rv = (x * 3.3 * 2 / 4096);
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::V1p8HV,
    [] (RS485Bus::Payload_t x){
      auto rv = (x * 3.3 * 2 / 4096);
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::V3p3HV,
    [] (RS485Bus::Payload_t x){
      auto rv = (x * 3.3 * 2 / 4096);
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::V2p5,
    [] (RS485Bus::Payload_t x){
      auto rv = (x * 3.3 * 2 / 4096);
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::Flow,
    [] (RS485Bus::Payload_t x){
      auto rv = (x * 3.3 / 4096);
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::AbsPressure,
    [] (RS485Bus::Payload_t x){
      auto rv = (x * 3.3 / 4096);
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::DMBTEMP,
    [] (RS485Bus::Payload_t x){
      auto rv = ((-3.9083e-3 + (pow(pow(3.9083e-3, 2) - 4*-5.775e-7*(1 - (3.3 - x * 3.3 / 4096)/(x * 3.3 / 4096)), 0.5)) / (2 * -5.775e-7)));
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::A3,
    [] (RS485Bus::Payload_t x){
      auto rv = (x * 3.3 / 4096);
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::I1p8CAL,
    [] (RS485Bus::Payload_t x){
      auto rv = (x * 3.3 / (4096 * 0.006 * 20));
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::I1p2,
    [] (RS485Bus::Payload_t x){
      auto rv = (x * 3.3 / (4096 * 0.006 * 20));
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::ICAL5p0,
    [] (RS485Bus::Payload_t x){
      auto rv = (x * 3.25 / (4096 * 0.5 * 20));
      return rv;
    }
  );
  conversions.Register<unsigned int>(StandardQueries::ADCSPARE,
    [] (RS485Bus::Payload_t x){
      auto rv = (x);
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::V3p3,
    [] (RS485Bus::Payload_t x){
      auto rv = (x * 3.3 / 4096);
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::VCAL5p0,
    [] (RS485Bus::Payload_t x){
      auto rv = (x * 3.3 * 2 / 4096);
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::V1p8CAL,
    [] (RS485Bus::Payload_t x){
      auto rv = (x * 3.3 * 2 / 4096);
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::V1p0,
    [] (RS485Bus::Payload_t x){
      auto rv = (x * 3.3 * 2 / 4096);
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::ROCPCBTEMP,
    [] (RS485Bus::Payload_t x){
      auto rv = ((x * 0.080566));
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::HVPCBTEMP,
    [] (RS485Bus::Payload_t x){
      auto rv = ((x * 0.080566));
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::CALPCBTEMP,
    [] (RS485Bus::Payload_t x){
      auto rv = ((x * 0.080566));
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::RTD,
    [] (RS485Bus::Payload_t x){
      auto rv = (x * 3.3 / 4096);
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::V5KEY,
    [] (RS485Bus::Payload_t x){
      auto rv = (x * 3.3 * 2 / 4096);
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::KEYPCBTEMP,
    [] (RS485Bus::Payload_t x){
      auto rv = (x / 4096 * 3300 / 10);
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::DCDCTEMP,
    [] (RS485Bus::Payload_t x){
      auto rv = (x / 4096 * 3300 / 10);
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::V2p5KEY,
    [] (RS485Bus::Payload_t x){
      auto rv = (x * 3.3 / 4096);
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::ROC_RAIL_1V,
    [] (RS485Bus::Payload_t x){
      auto rv = (x / 8);
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::ROC_RAIL_1p8V,
    [] (RS485Bus::Payload_t x){
      auto rv = (x / 8);
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::ROC_RAIL_2p5V,
    [] (RS485Bus::Payload_t x){
      auto rv = (x / 8);
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::ROC_TEMP,
    [] (RS485Bus::Payload_t x){
      auto rv = (x / 16 - 273.15);
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::CAL_RAIL_1V,
    [] (RS485Bus::Payload_t x){
      auto rv = (x / 8);
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::CAL_RAIL_1p8V,
    [] (RS485Bus::Payload_t x){
      auto rv = (x / 8);
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::CAL_RAIL_2p5V,
    [] (RS485Bus::Payload_t x){
      auto rv = (x / 8);
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::CAL_TEMP,
    [] (RS485Bus::Payload_t x){
      auto rv = (x / 16 - 273.15);
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::HV_RAIL_1V,
    [] (RS485Bus::Payload_t x){
      auto rv = (x / 8);
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::HV_RAIL_1p8V,
    [] (RS485Bus::Payload_t x){
      auto rv = (x / 8);
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::HV_RAIL_2p5V,
    [] (RS485Bus::Payload_t x){
      auto rv = (x / 8);
      return rv;
    }
  );
  conversions.Register<double>(StandardQueries::HV_TEMP,
    [] (RS485Bus::Payload_t x){
      auto rv = (x / 16 - 273.15);
      return rv;
    }
  );
  conversions.Register<unsigned int>(StandardQueries::ID,
    [] (RS485Bus::Payload_t x){
      auto rv = (x);
      return rv;
    }
  );
  conversions.Register<unsigned int>(StandardQueries::HB,
    [] (RS485Bus::Payload_t x){
      auto rv = (x);
      return rv;
    }
  );
  conversions.Register<unsigned int>(StandardQueries::DBG,
    [] (RS485Bus::Payload_t x){
      auto rv = (x);
      return rv;
    }
  );
}

// Ed Callaghan
// Single interface to all conversions of digital readbacks to analog values
// August 2025

#ifndef DIGITALCONVERSIONMAP_H
#define DIGITALCONVERSIONMAP_H

#include <functional>
#include <stdexcept>
#include <unordered_map>
#include "Messages.h"
#include "RS485Bus.h"

class DigitalConversionMap{
  public:
    DigitalConversionMap() = default;
    template<typename T>
    void Register(RS485Bus::OpCode_t, std::function<T(RS485Bus::Payload_t)>);
    Message_t* AsMessage(RS485Bus::OpCode_t, RS485Bus::Payload_t);

  protected:
    // unforgivable mechanism to duck-type conversions
    using blob_t = union{
      unsigned int u;
      double d;
    };
    using conversion_t = std::function<blob_t(RS485Bus::Payload_t)>;
    std::unordered_map<RS485Bus::OpCode_t, conversion_t> conversions;
    std::unordered_map<RS485Bus::OpCode_t, char> typecodes;

    blob_t AsBlob(RS485Bus::OpCode_t, RS485Bus::Payload_t);

  private:
    /**/
};

/*
Message_t* DigitalConversionMap::AsMessage(RS485Bus::Payload_t payload){
  std::string msg = "unsupported blob type";
  throw std::runtime_error(msg);
}
*/

#endif

// Ed Callaghan
// Single interface to all conversions of digital readbacks to analog values
// August 2025

#include "DigitalConversionMap.h"

template<typename T>
void DigitalConversionMap::Register(RS485Bus::OpCode_t opcode,
                                    std::function<T(RS485Bus::Payload_t)> f){
  std::string msg = "unsupported blob type";
  throw std::runtime_error(msg);
}

template<>
void DigitalConversionMap::Register(RS485Bus::OpCode_t opcode,
                                    std::function<unsigned int(RS485Bus::Payload_t)> f){
  auto cast = [f] (RS485Bus::Payload_t x) { blob_t rv; rv.u = f(x); return rv;};
  this->conversions[opcode] = cast;
  this->typecodes[opcode] = 'U';
}

template<>
void DigitalConversionMap::Register(RS485Bus::OpCode_t opcode,
                                    std::function<double(RS485Bus::Payload_t)> f){
  auto cast = [f] (RS485Bus::Payload_t x) { blob_t rv; rv.d = f(x); return rv;};
  this->conversions[opcode] = cast;
  this->typecodes[opcode] = 'D';
}

Message_t* DigitalConversionMap::AsMessage(RS485Bus::OpCode_t opcode,
                                           RS485Bus::Payload_t payload){
  Message_t* rv;
  blob_t blob = this->AsBlob(opcode, payload);
  if (this->typecodes[opcode] == 'U'){
    rv = message_wrap_uint(blob.u);
  }
  else if (this->typecodes[opcode] == 'D'){
    rv = message_wrap_double(blob.u);
  }
  else{
    std::string msg = "no typecode defined for opcode ";
    msg += std::to_string(opcode);
    throw std::runtime_error(msg);
  }
  return rv;
}

DigitalConversionMap::blob_t DigitalConversionMap::AsBlob(
                                                  RS485Bus::OpCode_t opcode,
                                                  RS485Bus::Payload_t payload){
  if (this->conversions.count(opcode) < 1){
    std::string msg = "no digital conversion defined for opcode ";
    msg += std::to_string(opcode);
    throw std::runtime_error(msg);
  }

  auto f = this->conversions[opcode];
  blob_t rv = f(payload);
  return rv;
}

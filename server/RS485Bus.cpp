// Ed Callaghan
// Endpoint to RS485 bus line, control of which is set via gpio pin state
// August 2025

#include "RS485Bus.h"

RS485Bus::RS485Bus(const std::string& cpath, const unsigned int pin,
                   asio::io_context& context,
                   const std::string& spath, const unsigned int baud_rate):
    chip(cpath),
    enable_pin(pin),
    context(context),
    executor(asio::make_strand(context)),
    device(executor),
    timeout(std::chrono::seconds(1)){
  // claim ownership of gpio pin state
  gpiod::line_settings settings;
  settings.set_direction(gpiod::line::direction::OUTPUT);
  gpiod::request_builder builder = this->chip.prepare_request();
  builder.set_consumer("MYDEVICE");
  builder.add_line_settings(this->enable_pin, settings);
  this->request = std::make_unique<gpiod::line_request>(builder.do_request());
  if (!(*(this->request))){
    std::string msg = "bad line request";
    throw std::runtime_error(msg);
  }
  // open serial device and set options
  this->device.open(spath);
  asio::serial_port_base::baud_rate baud(baud_rate);
  asio::serial_port_base::parity parity(asio::serial_port_base::parity::none);
  asio::serial_port_base::stop_bits stop(asio::serial_port_base::stop_bits::one);
  asio::serial_port_base::character_size character(8);
  this->device.set_option(baud);
  this->device.set_option(parity);
  this->device.set_option(stop);
  this->device.set_option(character);
}

void RS485Bus::send(const Address_t address, const OpCode_t opcode){
  SerialMessage_t message;
  this->pack_message(address, opcode, message);
  this->set_transmitting();
  size_t bytes = this->write(message);
  if (bytes != 3){
    std::string msg = "message of incorrect size written";
    throw std::runtime_error(msg);
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void RS485Bus::recv(Payload_t& rv){
  this->read_error.clear();
  SerialMessage_t message;
  this->set_receiving();
  size_t bytes = this->read(message);
  if (!(this->timed_out)){
    if (bytes != 3){
      std::string msg = "read message of incorrect size";
      throw std::runtime_error(msg);
    }
    this->unpack_message(message, rv);
  }
  else{
    /**/
  }

  // begin a cool-off period for the line to settle; the literal
  // waiting is deferred to a separate thread so that the current
  // readback value can be returned to the client immediately
  auto f = [this] () { this->pause_io(); };
  std::thread pause(f);
  pause.detach();
}

void RS485Bus::recv(Payload_t& rv, bool& timed_out){
  this->recv(rv);
  timed_out = this->timed_out;
}

void RS485Bus::set_line_value(gpiod::line::value value){
  this->request->set_value(this->enable_pin, value);
}

void RS485Bus::set_transmitting(){
  this->set_line_value(gpiod::line::value::ACTIVE);
}

void RS485Bus::set_receiving(){
  this->set_line_value(gpiod::line::value::INACTIVE);
}

size_t RS485Bus::write(const SerialMessage_t& message){
  asio::const_buffer buffer(&message, sizeof(SerialMessage_t));
  std::lock_guard lock(this->mutex);
  size_t rv = asio::write(this->device, buffer);
  return rv;
}

size_t RS485Bus::read(SerialMessage_t& message){
  asio::mutable_buffer buffer(&message, sizeof(SerialMessage_t));
  std::lock_guard lock(this->mutex);
  size_t rv = 0;
  auto callback = [&] (const std::error_code& ec, size_t size){
    this->read_error = ec;
    rv = size;
  };
  asio::async_read(this->device, buffer, callback);

  this->timed_out = false;
  this->context.restart();
  auto completed = this->context.run_one_for(this->timeout);
  if (completed < 1){
    this->timed_out = true;
  }
  return rv;
}

void RS485Bus::pack_message(const Address_t address, const OpCode_t opcode,
                            SerialMessage_t& message){
  char msb = (address >> 8) & 0x01;
  char lsbs = 0b1011010;
  message[0] = (msb << 7) | lsbs;
  message[1] = address & 0xFF;
  char* base = &message[0];
  memcpy(base+sizeof(Address_t), &opcode, sizeof(OpCode_t));
}

void RS485Bus::unpack_message(const SerialMessage_t& message, Payload_t& payload){
  if (message[0] != RS485Bus::recv_header){
    std::string msg = "incorrect header byte in device response";
    throw std::runtime_error(msg);
  }

  const char* base = &message[0];
  memcpy(&payload, base+sizeof(RS485Bus::recv_header), sizeof(Payload_t));
}

void RS485Bus::pause_io(){
  std::lock_guard lock(this->mutex);
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

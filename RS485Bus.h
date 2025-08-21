// Ed Callaghan
// Endpoint to RS485 bus line, control of which is set via gpio pin state
// August 2025

#ifndef RS485BUS_H
#define RS485BUS_H

#include <chrono>
#include <mutex>
#include <stdexcept>
#include <thread>
#include <asio.hpp>
#include <gpiod.hpp>

class RS485Bus{
  static const char recv_header = 0xEF;
  static const int gpiod_line_inactive = 0;
  static const int gpiod_line_active = 1;

  public:
    using SerialMessage_t = char[3];
    using Address_t = unsigned short;
    using OpCode_t = char;
    using Header_t = char;
    using Payload_t = unsigned short;
    RS485Bus(const std::string&, const unsigned int,
             asio::io_context&,
             const std::string&, const unsigned int);
   ~RS485Bus() = default;

    void send(const Address_t, const OpCode_t);
    void recv(Payload_t&);

  protected:
    gpiod::chip chip;
    unsigned int enable_pin;
    gpiod::line line;
    asio::any_io_executor executor;
    asio::serial_port device;
    std::mutex mutex;

    void set_line_value(int);
    void set_transmitting();
    void set_receiving();
    size_t write(const SerialMessage_t&);
    size_t read(SerialMessage_t&);
    void pack_message(const Address_t, const OpCode_t, SerialMessage_t&);
    void unpack_message(const SerialMessage_t&, Payload_t&);
    void pause_io();

  private:
    /**/
};

#endif

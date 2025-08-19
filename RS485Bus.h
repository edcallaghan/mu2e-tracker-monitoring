// Ed Callaghan
// Endpoint to RS485 bus line, control of which is set via gpio pin state
// August 2025

#ifndef RS485BUS_H
#define RS485BUS_H

#include <chrono>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <thread>
#include <asio.hpp>
#include <gpiod.hpp>

/*
typedef char           SerialMessage_t[3];
typedef unsigned short Address_t;
typedef char           OpCode_t;
typedef unsigned short Payload_t;
*/

class RS485Bus{
  static const char recv_header = 0xEF;

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
    gpiod::line::offset enable_pin;
    std::unique_ptr<gpiod::line_request> request;
    asio::any_io_executor executor;
    asio::serial_port device;
    std::mutex mutex;

    void set_line_value(gpiod::line::value);
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

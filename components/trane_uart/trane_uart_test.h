#pragma once
#include "esphome.h"
#include "esphome/components/uart/uart.h"

namespace trane_uart {

class TraneUARTTestComponent : public esphome::Component {
 public:
  TraneUARTTestComponent(esphome::uart::UARTComponent *uart, esphome::GPIOPin *tx_enable_pin);

  void setup() override;
  void loop() override;
  void send_message(const uint8_t *data, size_t len);

 protected:
  esphome::uart::UARTComponent *uart_;
  esphome::GPIOPin *tx_enable_pin_;
};

}  // namespace trane_uart

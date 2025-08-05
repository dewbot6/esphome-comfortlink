#include "trane_uart_test.h"

namespace trane_uart {

TraneUARTTestComponent::TraneUARTTestComponent(esphome::uart::UARTComponent *uart, esphome::GPIOPin *tx_enable_pin)
  : uart_(uart), tx_enable_pin_(tx_enable_pin) {}

void TraneUARTTestComponent::setup() {
  tx_enable_pin_->setup();
  tx_enable_pin_->digital_write(false);
  esphome::delay(2000);

  const uint8_t msg[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x01};
  send_message(msg, sizeof(msg));
}

void TraneUARTTestComponent::loop() {
  uint8_t b;
  while (uart_->read_byte(&b)) {
    ESP_LOGI("trane_uart", "RX: 0x%02X", b);
  }
}

void TraneUARTTestComponent::send_message(const uint8_t *data, size_t len) {
  ESP_LOGI("trane_uart", "Sending %d bytes", (int)len);
  tx_enable_pin_->digital_write(true);
  esphome::delayMicroseconds(100);

  for (size_t i = 0; i < len; i++) {
    uart_->write_byte(data[i]);
  }

  uart_->flush();
  esphome::delayMicroseconds(100);
  tx_enable_pin_->digital_write(false);
}

}  // namespace trane_uart

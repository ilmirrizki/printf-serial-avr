#ifndef PRINTF_SERIAL_H
#define PRINTF_SERIAL_H

#include <Arduino.h>
#include <stdio.h>

// Variable FILE internal
static FILE uart_output;

// Fungsi helper untuk mengirim karakter ke Serial
static int _serial_putchar(char c, FILE *stream) {
  if (c == '\n') Serial.write('\r');
  Serial.write(c);
  return 0;
}

// Fungsi inisialisasi library
static inline void init_printf(unsigned long baud_rate) {
  Serial.begin(baud_rate);
  fdev_setup_stream(&uart_output, _serial_putchar, NULL, _FDEV_SETUP_WRITE);
  stdout = &uart_output;
}

#endif

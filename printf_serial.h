#ifndef PRINTF_SERIAL_H
#define PRINTF_SERIAL_H

#include <Arduino.h>
#include <stdio.h>

static FILE uart_str;

// Helper Output (stdout) -> Mengirim karakter ke Serial
static int _serial_putchar(char c, FILE *stream) {
  if (c == '\n') Serial.write('\r');
  Serial.write(c);
  return 0;
}

// Helper Input (stdin) -> Membaca karakter dari Serial
static int _serial_getchar(FILE *stream) {
  while (!Serial.available()); // Tunggu sampai ada karakter masuk di Serial
  return Serial.read();
}

// Inisialisasi Serial + Stdout + Stdin
static inline void init_serial_io(unsigned long baud_rate) {
  Serial.begin(baud_rate);
  
  // Setup stream untuk Baca & Tulis (_FDEV_SETUP_RW)
  fdev_setup_stream(&uart_str, _serial_putchar, _serial_getchar, _FDEV_SETUP_RW);
  
  stdout = &uart_str; // Arahkan printf
  stdin  = &uart_str; // Arahkan scanf
}

#endif

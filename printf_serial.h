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

// =========================================================================
// HELPER PRINTER UNTUK PECAHAN (FLOAT & DOUBLE)
// Membantu mengatasi keterbatasan avr-libc yang mematikan format %f di printf
// =========================================================================

/**
 * @brief Mencetak nilai float dengan presisi yang dapat ditentukan.
 * @param val Nilai float yang akan dicetak.
 * @param precision Jumlah angka di belakang koma (default: 2).
 */
static inline void print_float(float val, int precision = 2) {
  char buf[20];
  dtostrf(val, 0, precision, buf);
  printf("%s", buf);
}

/**
 * @brief Mencetak nilai double dengan presisi yang dapat ditentukan.
 * @param val Nilai double yang akan dicetak.
 * @param precision Jumlah angka di belakang koma (default: 4).
 */
static inline void print_double(double val, int precision = 4) {
  char buf[25];
  dtostrf(val, 0, precision, buf);
  printf("%s", buf);
}

/**
 * @brief Membersihkan sisa karakter enter / newline pada buffer Serial input.
 * Berguna dipanggil sebelum atau sesudah scanf agar tidak terlewat otomatis.
 */
static inline void clear_serial_buffer() {
  while (Serial.available()) {
    Serial.read();
  }
}

#endif

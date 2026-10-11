#ifndef PRINTF_SERIAL_H
#define PRINTF_SERIAL_H

#include <Arduino.h>
#include <stdio.h>
#include <stdarg.h>

static FILE uart_str;

static int _serial_putchar(char c, FILE *stream) {
  if (c == '\n') Serial.write('\r');
  Serial.write(c);
  return 0;
}

static int _serial_getchar(FILE *stream) {
  while (!Serial.available());
  return Serial.read();
}

static inline void init_serial_io(unsigned long baud_rate) {
  Serial.begin(baud_rate);
  fdev_setup_stream(&uart_str, _serial_putchar, _serial_getchar, _FDEV_SETUP_RW);
  stdout = &uart_str;
  stdin  = &uart_str;
}

// =========================================================================
// HELPER PRINTF KHUSUS FLOAT (Mendukung %.1f, %.2f, %.4f, dll.)
// =========================================================================

/**
 * @brief Fungsi wrapper printf khusus yang mendukung specifier %.2f / %f
 */
static inline void printf_flt(const char *format, double val) {
  char buf[20];
  int precision = 2; // Default presisi 2 angka dibelakang koma

  // Cek jika format meminta presisi spesifik seperti %.1f, %.3f, %.4f
  const char *p = strchr(format, '.');
  if (p && *(p + 1) >= '0' && *(p + 1) <= '9') {
    precision = *(p + 1) - '0';
  }

  dtostrf(val, 0, precision, buf);

  // Buat format string baru menggantikan %.Xf dengan %s
  char fmt_clean[50];
  int i = 0, j = 0;
  while (format[i] != '\0' && j < 48) {
    if (format[i] == '%' && (format[i+1] == 'f' || (format[i+1] == '.' && format[i+3] == 'f'))) {
      fmt_clean[j++] = '%';
      fmt_clean[j++] = 's';
      if (format[i+1] == '.') i += 3;
      else i += 1;
    } else {
      fmt_clean[j++] = format[i];
    }
    i++;
  }
  fmt_clean[j] = '\0';

  printf(fmt_clean, buf);
}

static inline void print_float(float val, int precision = 2) {
  char buf[20];
  dtostrf(val, 0, precision, buf);
  printf("%s", buf);
}

static inline void print_double(double val, int precision = 4) {
  char buf[25];
  dtostrf(val, 0, precision, buf);
  printf("%s", buf);
}

static inline void clear_serial_buffer() {
  while (Serial.available()) {
    Serial.read();
  }
}

#endif

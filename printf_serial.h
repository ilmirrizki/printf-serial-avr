#ifndef PRINTF_SERIAL_H
#define PRINTF_SERIAL_H

#include <Arduino.h>
#include <stdio.h>
#include <string.h>

static FILE uart_str;

// Helper Output (stdout) -> Sender tegn til Serial
static int _serial_putchar(char c, FILE *stream) {
  if (c == '\n') Serial.write('\r');
  Serial.write(c);
  return 0;
}

// Helper Input (stdin) -> Læser tegn fra Serial
static int _serial_getchar(FILE *stream) {
  while (!Serial.available());
  return Serial.read();
}

// Initialisering af Serial, stdout og stdin
static inline void init_serial_io(unsigned long baud_rate = 9600) {
  Serial.begin(baud_rate);
  fdev_setup_stream(&uart_str, _serial_putchar, _serial_getchar, _FDEV_SETUP_RW);
  stdout = &uart_str;
  stdin  = &uart_str;
}

// Hjælpefunktion til konvertering af float/double
static inline void _print_flt_helper(const char *format, double val) {
  char buf[20];
  int precision = 2;

  const char *p = strchr(format, '.');
  if (p && *(p + 1) >= '0' && *(p + 1) <= '9') {
    precision = *(p + 1) - '0';
  }

  dtostrf(val, 0, precision, buf);

  char fmt_clean[60];
  int i = 0, j = 0;
  while (format[i] != '\0' && j < 58) {
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

// Makro til automatisk float-håndtering
#define printf(fmt, ...) \
  if (strstr(fmt, "%f") || strstr(fmt, "%.")) { \
    _print_flt_helper(fmt, ##__VA_ARGS__); \
  } else { \
    printf(fmt, ##__VA_ARGS__); \
  }

#endif

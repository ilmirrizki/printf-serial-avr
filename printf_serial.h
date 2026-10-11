#ifndef PRINTF_SERIAL_H
#define PRINTF_SERIAL_H

#include <Arduino.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

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

// Inisialisasi Stream Stdout & Stdin
static inline void _setup_printf_stream() {
  fdev_setup_stream(&uart_str, _serial_putchar, _serial_getchar, _FDEV_SETUP_RW);
  stdout = &uart_str; // Arahkan printf
  stdin  = &uart_str; // Arahkan scanf
}

// Helper khusus penanganan Serial.begin + Setup Stream
static inline void _init_serial_begin(unsigned long baud) {
  Serial.begin(baud);
  _setup_printf_stream();
}

// Helper internal untuk konversi float/double otomatis saat mencetak printf
static inline void _smart_printf_handler(const char *format, ...) {
  va_list args;
  va_start(args, format);

  if (strstr(format, "%f") || strstr(format, "%.")) {
    double val = va_arg(args, double);

    char buf[20];
    int precision = 2; // Default 2 angka di belakang koma

    // Cari presisi kustom (misal %.1f, %.2f, %.4f)
    const char *p = strchr(format, '.');
    if (p && *(p + 1) >= '0' && *(p + 1) <= '9') {
      precision = *(p + 1) - '0';
    }

    dtostrf(val, 0, precision, buf);

    // Ubah specifier %f atau %.Xf menjadi %s
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

    vfprintf(stdout, fmt_clean, (va_list)&buf);
  } else {
    vfprintf(stdout, format, args);
  }
  
  va_end(args);
}

// Clear Serial Input Buffer
static inline void clear_serial_buffer() {
  while (Serial.available()) {
    Serial.read();
  }
}

// TRIK MACRO BERSIH:
#define begin(baud) _init_serial_begin(baud)
#define printf(...) _smart_printf_handler(__VA_ARGS__)

#endif

#ifndef PRINTF_SERIAL_H
#define PRINTF_SERIAL_H

#include <Arduino.h>
#include <stdio.h>
#include <string.h>

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

// Helper internal untuk konversi float/double saat mencetak
static inline void _smart_printf_handler(const char *format, ...) {
  // Jika dalam format string ada %f atau %. (float/double)
  if (strstr(format, "%f") || strstr(format, "%.")) {
    va_list args;
    va_start(args, format);
    double val = va_arg(args, double);
    va_end(args);

    char buf[20];
    int precision = 2; // Default 2 angka belakang koma

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

    printf(fmt_clean, buf);
  } else {
    // Jika integer, char, string biasa -> gunakan printf standar
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
  }
}

// Clear Serial Input Buffer
static inline void clear_serial_buffer() {
  while (Serial.available()) {
    Serial.read();
  }
}

// Trik Macro: Menimpa kata 'printf' agar mendukung float secara otomatis
#define printf(...) _smart_printf_handler(__VA_ARGS__)

#endif

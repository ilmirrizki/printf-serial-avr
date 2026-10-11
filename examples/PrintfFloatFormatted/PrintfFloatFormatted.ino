#include <printf_serial.h>

int a = 10;
float pi = 3.14159;
double temp = 36.7542;

void setup() {
  init_serial_io(9600);

  // Tipe Data Integer
  printf("Nilai integer : %d\n", a);

  // Bisa langsung pakai format %.2f / %.4f dalam 1 baris!
  printf_flt("Nilai float   : %.2f\n", pi);
  printf_flt("Nilai double  : %.4f\n", temp);
}

void loop() {
  // Empty
}

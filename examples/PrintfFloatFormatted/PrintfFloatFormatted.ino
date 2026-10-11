#include "printf_serial.h"

int a = 10;
float pi = 3.14159;
double temp = 36.7542;

void setup() {
  init_serial_io(9600);

  // Sintaks printf murni standar C untuk semua tipe data!
  printf("Nilai integer : %d\n", a);
  printf("Nilai float   : %.2f\n", pi);
  printf("Nilai double  : %.1f\n", temp);
}

void loop() {
  // Empty
}

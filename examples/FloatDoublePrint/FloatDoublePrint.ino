#include <printf_serial.h>

int a = 10;
float pi = 3.14159;
double temp = 36.7542;

void setup() {
  init_serial_io(9600);

  // 1. Tipe Data Integer (%d)
  printf("Nilai integer : %d\n", a);

  // 2. Tipe Data Float (Mencetak 2 desimal)
  printf("Nilai float   : ");
  print_float(pi, 2);
  printf("\n");

  // 3. Tipe Data Double (Mencetak 4 desimal)
  printf("Nilai double  : ");
  print_double(temp, 4);
  printf("\n");
}

void loop() {
  // Empty
}

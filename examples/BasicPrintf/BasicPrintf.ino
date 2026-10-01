#include <stdio.h>
#include <printf_serial.h>

void setup() {
  // Inisialisasi Serial I/O 2-arah (printf + scanf)
  init_serial_io(9600);

  printf("=================================\n");
  printf("  DEMO PRINTF & SCANF AVR/WOKWI  \n");
  printf("=================================\n\n");
}

void loop() {
  char nama[20];
  int umur;

  printf("\nMasukkan nama Anda: ");
  scanf("%s", nama);

  printf("Masukkan umur Anda: ");
  scanf("%d", &umur);

  printf("\nHalo %s, umur Anda %d tahun.\n", nama, umur);
  delay(2000);
}

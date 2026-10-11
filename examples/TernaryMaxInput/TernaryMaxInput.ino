/**
 * @file TernaryMaxInput.ino
 * @brief Example using printf and scanf to compare two integers with a ternary operator.
 * @repository printf-serial-avr
 */

#include <printf_serial.h>

int a, b, maks;

void setup() {
  // Inisialisasi Serial UART pada Baud Rate 9600
  init_serial_io(9600);

  // Bersihkan buffer masukan serial di awal
  while (Serial.available()) Serial.read();

  // Input nilai A
  printf("Masukkan nilai a : ");
  fflush(stdout); // Memastikan prompt tercetak di terminal sebelum scanf
  scanf("%d", &a);

  // Bersihkan sisa karakter enter/newline
  while (Serial.available()) Serial.read();

  // Input nilai B
  printf("Masukkan nilai b : ");
  fflush(stdout);
  scanf("%d", &b);

  // Evaluasi nilai maksimum dengan Operator Ternary
  maks = (a > b) ? a : b;

  // Cetak hasil evaluasi
  printf("\nNilai maks dari a = %d dan b = %d adalah : %d\n", a, b, maks);
}

void loop() {
  // Tidak ada proses berulang
}

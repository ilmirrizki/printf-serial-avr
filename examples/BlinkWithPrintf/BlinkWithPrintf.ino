#include <printf_serial.h>

const int ledPin = 13;

void setup() {
  // Inisialisasi pin LED sebagai output
  pinMode(ledPin, OUTPUT);

  // Inisialisasi Serial + printf/scanf
  init_serial_io(9600);

  printf("===================================\n");
  printf("  DEMO BLINK LED 13 WITH PRINTF    \n");
  printf("===================================\n\n");
}

void loop() {
  static int counter = 1;

  // LED menyala
  digitalWrite(ledPin, HIGH);
  printf("[Iterasi %d] LED Pin 13: HIGH (ON)\n", counter);
  delay(1000);

  // LED mati
  digitalWrite(ledPin, LOW);
  printf("[Iterasi %d] LED Pin 13: LOW  (OFF)\n", counter);
  delay(1000);

  counter++;
}

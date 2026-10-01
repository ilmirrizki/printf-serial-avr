#include <avr/io.h>
#include <util/delay.h>
#include <printf_serial.h>

#define LED_PORT PORTB
#define LED_DDR  DDRB
#define LED_BIT  PB5 // Pin 13 pada Arduino Uno (PB5)

int main(void) {
  // Inisialisasi pin LED sebagai output
  LED_DDR |= (1 << LED_BIT);

  // Inisialisasi Serial + printf
  init_serial_io(9600);

  printf("===================================\n");
  printf("  DEMO BLINK LED (PURE AVR C)      \n");
  printf("===================================\n\n");

  int counter = 1;

  while (1) {
    // Nyalakan LED (Set HIGH)
    LED_PORT |= (1 << LED_BIT);
    printf("[Iterasi %d] LED Pin 13: HIGH (ON)\n", counter);
    _delay_ms(1000);

    // Matikan LED (Set LOW)
    LED_PORT &= ~(1 << LED_BIT);
    printf("[Iterasi %d] LED Pin 13: LOW  (OFF)\n", counter);
    _delay_ms(1000);

    counter++;
  }

  return 0;
}

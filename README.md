# printf-serial-avr

Pustaka C/AVR ringan untuk mengarahkan stream I/O standar (`stdout` & `stdin`) ke port Serial UART Hardware. Memungkinkan fungsi `printf()` dan `scanf()` standar bahasa C bekerja langsung pada simulator Wokwi maupun mikrokontroler AVR fisik (seperti Arduino Uno/Nano).

---

## 🛠️ Cara Memasang di Wokwi

1. Unduh repositori ini sebagai file ZIP.
2. Ekstrak ZIP tersebut, lalu kompres ulang **file-file utamanya secara langsung** menjadi file ZIP baru (pastikan `printf_serial.h` berada di tingkat paling atas/root, bukan di dalam subfolder).
3. Di Wokwi, buka **Library Manager** -> klik tombol **`+`** -> pilih **`UPLOAD A LIBRARY`**.
4. Unggah file ZIP yang telah dipadatkan tersebut.

---

## 💻 Contoh Kode Program

### 1. Versi Arduino IDE / Wokwi Sketch (`sketch.ino`)
Menggabungkan kontrol Arduino, Output `printf()`, dan Input `scanf()` sekaligus:

```cpp
#include <stdio.h>
#include <printf_serial.h>

const int ledPin = 13;

void setup() {
  // Inisialisasi pin LED sebagai Output
  pinMode(ledPin, OUTPUT);

  // Inisialisasi Serial UART + Stream I/O 2-Arah (printf & scanf)
  init_serial_io(9600);

  printf("=======================================\n");
  printf("  DEMO PRINTF, SCANF & BLINK LED 13   \n");
  printf("=======================================\n\n");
}

void loop() {
  static int counter = 1;
  char nama[20];
  int umur;

  // 1. Uji Coba Blink LED & printf Output
  digitalWrite(ledPin, HIGH);
  printf("[Iterasi %d] Status LED 13: HIGH (ON)\n", counter);
  delay(1000);

  digitalWrite(ledPin, LOW);
  printf("[Iterasi %d] Status LED 13: LOW  (OFF)\n", counter);
  delay(1000);

  // 2. Uji Coba scanf Input dari Serial Monitor
  printf("\n--- FITUR INTERAKTIF SCANF ---\n");
  printf("Masukkan Nama Anda : ");
  scanf("%s", nama);

  printf("Masukkan Umur Anda : ");
  scanf("%d", &umur);

  printf("\nHasil -> Halo %s, umur Anda saat ini %d tahun.\n\n", nama, umur);
  delay(2000);

  counter++;
}
```

---

### 2. Versi Pure AVR C (`main.c`)
Menggunakan pengaksesan register hardware secara langsung (`DDRB`, `PORTB`):

```c
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <printf_serial.h>

#define LED_PORT PORTB
#define LED_DDR  DDRB
#define LED_BIT  PB5 // Pin 13 pada Arduino Uno

int main(void) {
  LED_DDR |= (1 << LED_BIT); // Set Pin 13 sebagai Output
  init_serial_io(9600);      // Inisialisasi Serial + I/O streams

  printf("===================================\n");
  printf("  DEMO BLINK LED (PURE AVR C)      \n");
  printf("===================================\n\n");

  int counter = 1;

  while (1) {
    LED_PORT |= (1 << LED_BIT);
    printf("[Iterasi %d] LED Pin 13: HIGH (ON)\n", counter);
    _delay_ms(1000);

    LED_PORT &= ~(1 << LED_BIT);
    printf("[Iterasi %d] LED Pin 13: LOW  (OFF)\n", counter);
    _delay_ms(1000);

    counter++;
  }

  return 0;
}
```

---

## 📄 Lisensi
MIT License

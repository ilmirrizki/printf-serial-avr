void setup() {
  Serial.begin(9600);
  
  delay(1000); // Tunggu Serial Monitor siap

  Serial.println("======================================");
  Serial.println("   PROGRAM MENCARI NILAI MAX & MIN    ");
  Serial.println("======================================");

  // --- BACA ANGKA PERTAMA ---
  Serial.print("Masukkan Angka Pertama : ");
  while (Serial.available() == 0) {} // Tunggu input
  int angka1 = Serial.parseInt();
  Serial.println(angka1);
  while (Serial.available() > 0) Serial.read(); // Bersihkan buffer enter

  // --- BACA ANGKA KEDUA ---
  Serial.print("Masukkan Angka Kedua   : ");
  while (Serial.available() == 0) {} // Tunggu input
  int angka2 = Serial.parseInt();
  Serial.println(angka2);
  while (Serial.available() > 0) Serial.read(); // Bersihkan buffer enter

  // --- BACA ANGKA KETIGA ---
  Serial.print("Masukkan Angka Ketiga  : ");
  while (Serial.available() == 0) {} // Tunggu input
  int angka3 = Serial.parseInt();
  Serial.println(angka3);
  while (Serial.available() > 0) Serial.read(); // Bersihkan buffer enter

  // --- CARI NILAI MAKSIMUM ---
  int max = angka1;
  if (angka2 > max) {
    max = angka2;
  }
  if (angka3 > max) {
    max = angka3;
  }

  // --- CARI NILAI MINIMUM ---
  int min = angka1;
  if (angka2 < min) {
    min = angka2;
  }
  if (angka3 < min) {
    min = angka3;
  }

  // --- TAMPILKAN HASIL ---
  Serial.println("--------------------------------------");
  Serial.print("Nilai Maksimum (MAX) : ");
  Serial.println(max);

  Serial.print("Nilai Minimum  (MIN) : ");
  Serial.println(min);
  Serial.println("--------------------------------------");
}

void loop() {
  // Kosong
}

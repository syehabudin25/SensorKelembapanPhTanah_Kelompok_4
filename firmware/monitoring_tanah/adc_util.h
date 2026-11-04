#pragma once
// Baca ADC 'jumlah' kali, urutkan, buang 'buang' nilai terkecil dan terbesar,
// lalu rata-ratakan sisanya (default: 10 sampel, tengah 6 diambil).
float bacaADCTrimmed(int pin, int jumlah = 10, int buang = 2, int jedaMs = 30) {
  if (jumlah > 32) jumlah = 32;
  int buf[32];
  for (int i = 0; i < jumlah; i++) {
    buf[i] = analogRead(pin);
    delay(jedaMs);
  }
  for (int i = 0; i < jumlah - 1; i++) {
    for (int j = i + 1; j < jumlah; j++) {
      if (buf[i] > buf[j]) { int t = buf[i]; buf[i] = buf[j]; buf[j] = t; }
    }
  }
  long total = 0;
  int n = 0;
  for (int i = buang; i < jumlah - buang; i++) { total += buf[i]; n++; }
  return (float)total / n;
}

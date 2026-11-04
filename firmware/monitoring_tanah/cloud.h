#pragma once
// Semua urusan Blynk ada di sini. Butuh secrets.h + library Blynk sudah di-include.

void cloudMulai() {
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);
}

void cloudKirim(float ph, float volt, float soil) {
  if (!Blynk.connected()) {
    Serial.println("Blynk: Disconnected");
    return;
  }
  Blynk.virtualWrite(VPIN_PH, ph);
  Blynk.virtualWrite(VPIN_VOLT, volt);
  if (!isnan(soil)) Blynk.virtualWrite(VPIN_SOIL, soil);
  Serial.println("Blynk: Data Sent");
}

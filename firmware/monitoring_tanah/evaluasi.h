#pragma once
// Notifikasi bila di luar batas. Nonaktif selama AKTIFKAN_NOTIFIKASI = false.
// Event Code di Blynk Console harus persis: ph_abnormal, kelembapan_rendah, kelembapan_tinggi

void evaluasiNotifikasi(float ph, float soil) {
  if (!AKTIFKAN_NOTIFIKASI || !Blynk.connected()) return;
  char msg[48];

  if (ph < PH_MIN) {
    snprintf(msg, sizeof(msg), "pH %.2f terlalu asam", ph);
    Blynk.logEvent("ph_abnormal", msg);
  } else if (ph > PH_MAX) {
    snprintf(msg, sizeof(msg), "pH %.2f terlalu basa", ph);
    Blynk.logEvent("ph_abnormal", msg);
  }

  if (!isnan(soil)) {
    if (soil < SOIL_MIN) {
      snprintf(msg, sizeof(msg), "Tanah terlalu kering: %.1f %%", soil);
      Blynk.logEvent("kelembapan_rendah", msg);
    } else if (soil > SOIL_MAX) {
      snprintf(msg, sizeof(msg), "Tanah terlalu basah: %.1f %%", soil);
      Blynk.logEvent("kelembapan_tinggi", msg);
    }
  }
}

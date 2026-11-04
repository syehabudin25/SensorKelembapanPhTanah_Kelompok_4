#pragma once
#include "adc_util.h"

// ===== KALIBRASI pH =====
// Rumus: pH = PH_SLOPE * volt + PH_OFFSET   (volt diukur di pin ESP32)
// TODO-KALIBRASI: ganti dengan hasil kalibrasi (lihat docs/catatan_kalibrasi.md)
const float PH_SLOPE  = -5.70;
const float PH_OFFSET = 21.34 - 0.1;   // = 21.24

struct HasilPH {
  float adc;
  float volt;
  float ph;
};

HasilPH bacaPH() {
  HasilPH h;
  h.adc  = bacaADCTrimmed(PH_SENSOR_PIN, 10, 2, 30);
  h.volt = h.adc * 3.3 / 4095.0;
  h.ph   = PH_SLOPE * h.volt + PH_OFFSET;
  return h;
}

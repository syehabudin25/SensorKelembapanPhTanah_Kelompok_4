#ifndef CLOUD_H
#define CLOUD_H

#include <Arduino.h>
#include <BlynkSimpleEsp32.h>

#include "config.h"
#include "secrets.h"

void cloudMulai() {
    Blynk.config(BLYNK_AUTH_TOKEN);
}

// Mengirim empat data sesuai datastream dashboard Blynk:
// V0 = pH, V1 = kelembapan, V2 = status pH, V3 = status kelembapan.
void cloudKirim(
    float ph,
    float kelembapan,
    String statusPH,
    String statusKelembapan
) {
    Blynk.virtualWrite(VPIN_PH, ph);
    Blynk.virtualWrite(VPIN_MOISTURE, kelembapan);
    Blynk.virtualWrite(VPIN_STATUS, statusPH);
    Blynk.virtualWrite(VPIN_MOISTURE_STATUS, statusKelembapan);
}

#endif

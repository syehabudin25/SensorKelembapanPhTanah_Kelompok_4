#ifndef CLOUD_H
#define CLOUD_H

#include <Arduino.h>
#include <BlynkSimpleEsp32.h>

#include "config.h"
#include "secrets.h"

// Konfigurasi Blynk
void cloudMulai() {

    Blynk.config(BLYNK_AUTH_TOKEN);

}

// Mengirim data sensor ke Blynk
void cloudKirim(float ph, float volt, String status) {

    // Nilai pH
    Blynk.virtualWrite(VPIN_PH, ph);

    // Tegangan sensor
    Blynk.virtualWrite(VPIN_VOLT, volt);

    // Kesimpulan kondisi tanah
    Blynk.virtualWrite(VPIN_STATUS, status);

}

#endif
#ifndef SENSOR_KELEMBAPAN_H
#define SENSOR_KELEMBAPAN_H

#include <Arduino.h>
#include "config.h"

// Nilai awal kalibrasi. Sesuaikan melalui pengujian sensor.
#define NILAI_KERING 3500
#define NILAI_BASAH  1500

struct HasilKelembapan {
    int adc;
    float persen;
};

// Membaca sensor kelembapan dan mengubah ADC menjadi persen.
// Asumsi sensor yang digunakan: ADC tinggi = kering, ADC rendah = basah.
HasilKelembapan bacaSensorKelembapan() {

    HasilKelembapan hasil;
    long total = 0;

    for (int i = 0; i < JUMLAH_SAMPEL_MOISTURE; i++) {
        total += analogRead(MOISTURE_SENSOR_PIN);
        delay(5);
    }

    hasil.adc = total / JUMLAH_SAMPEL_MOISTURE;

    if (NILAI_KERING == NILAI_BASAH) {
        hasil.persen = 0;
        return hasil;
    }

    hasil.persen =
        ((float)(NILAI_KERING - hasil.adc) /
        (NILAI_KERING - NILAI_BASAH)) * 100.0;

    hasil.persen = constrain(hasil.persen, 0.0, 100.0);

    return hasil;
}

#endif

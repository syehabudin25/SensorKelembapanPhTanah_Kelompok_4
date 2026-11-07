#ifndef SENSOR_PH_H
#define SENSOR_PH_H

#include <Arduino.h>
#include "config.h"
#include "adc_util.h"

// Kalibrasi sensor pH
#define PH_SLOPE -5.70
#define PH_CALIBRATION 21.24

// Struktur hasil pembacaan sensor
struct HasilPH {
    float adc;
    float volt;
    float ph;
};

// Membaca sensor pH
HasilPH bacaSensorPH() {

    HasilPH hasil;

    // Membaca rata-rata ADC
    hasil.adc = bacaADC(PH_SENSOR_PIN);

    // Konversi ADC ke tegangan
    hasil.volt = hasil.adc * 3.3 / 4095.0;

    // Menghitung nilai pH
    hasil.ph = PH_SLOPE * hasil.volt + PH_CALIBRATION;

    return hasil;
}

#endif
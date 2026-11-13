#ifndef SENSOR_PH_H
#define SENSOR_PH_H

#include <Arduino.h>
#include "config.h"
#include "adc_util.h"

// Kalibrasi pH mengikuti kode yang saat ini berjalan
#define PH_SLOPE -5.70
#define PH_CALIBRATION 21.24

struct HasilPH {
    float adc;
    float volt;
    float ph;
};

HasilPH bacaSensorPH() {

    HasilPH hasil;

    hasil.adc = bacaADC(PH_SENSOR_PIN);
    hasil.volt = hasil.adc * 3.3 / 4095.0;
    hasil.ph = PH_SLOPE * hasil.volt + PH_CALIBRATION;

    return hasil;
}

#endif

#ifndef ADC_UTIL_H
#define ADC_UTIL_H

#include <Arduino.h>
#include "config.h"

// Membaca ADC dengan 10 sampel, Bubble Sort,
// lalu mengambil rata-rata 6 nilai tengah.
float bacaADC(uint8_t pin) {

    int buffer_arr[JUMLAH_SAMPEL];

    for (int i = 0; i < JUMLAH_SAMPEL; i++) {
        buffer_arr[i] = analogRead(pin);
        delay(10);
    }

    // Bubble Sort
    for (int i = 0; i < JUMLAH_SAMPEL - 1; i++) {
        for (int j = i + 1; j < JUMLAH_SAMPEL; j++) {
            if (buffer_arr[i] > buffer_arr[j]) {
                int temp = buffer_arr[i];
                buffer_arr[i] = buffer_arr[j];
                buffer_arr[j] = temp;
            }
        }
    }

    int avgval = 0;

    for (int i = 2; i < 8; i++) {
        avgval += buffer_arr[i];
    }

    return avgval / 6.0;
}

#endif

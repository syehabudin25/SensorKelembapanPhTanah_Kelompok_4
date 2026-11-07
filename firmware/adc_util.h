#ifndef ADC_UTIL_H
#define ADC_UTIL_H

#include <Arduino.h>
#include "config.h"

float bacaADC(uint8_t pin) {

    int buffer_arr[JUMLAH_SAMPEL];

    // Membaca 10 sampel ADC
    for (int i = 0; i < JUMLAH_SAMPEL; i++) {
        buffer_arr[i] = analogRead(pin);
        delay(30);
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

    // Menghitung rata-rata 6 nilai tengah
    int avgval = 0;

    for (int i = 2; i < 8; i++) {
        avgval += buffer_arr[i];
    }

    return avgval / 6.0;
}

#endif
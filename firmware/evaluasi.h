#ifndef EVALUASI_H
#define EVALUASI_H

#include <Arduino.h>

// Klasifikasi pH mengikuti batas pada kode terbaru.
String klasifikasiTanah(float ph) {

    if (ph < 4.5) {
        return "Sangat Asam";
    }
    else if (ph <= 6.0) {
        return "Asam";
    }
    else if (ph <= 7.0) {
        return "Netral";
    }
    else if (ph <= 7.5) {
        return "Agak Basa";
    }
    else {
        return "Basa";
    }
}

// Klasifikasi kelembapan tanah.
String klasifikasiKelembapan(float kelembapan) {

    if (kelembapan < 30) {
        return "Kering";
    }
    else if (kelembapan < 70) {
        return "Normal";
    }
    else {
        return "Basah";
    }
}

#endif

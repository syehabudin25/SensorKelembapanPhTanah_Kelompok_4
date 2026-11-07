#ifndef EVALUASI_H
#define EVALUASI_H

#include <Arduino.h>

// Klasifikasi kondisi tanah berdasarkan pH
String klasifikasiTanah(float ph) {

    if (ph < 4.5) {
        return "Sangat Asam";
    }
    else if (ph <= 5.5) {
        return "Asam";
    }
    else if (ph <= 6.5) {
        return "Agak Asam";
    }
    else if (ph <= 7.5) {
        return "Netral";
    }
    else if (ph <= 8.5) {
        return "Agak Basa";
    }
    else if (ph <= 9.0) {
        return "Basa";
    }
    else {
        return "Sangat Basa";
    }
}

#endif
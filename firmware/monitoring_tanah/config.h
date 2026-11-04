#pragma once
// ===== PIN =====
#define PH_SENSOR_PIN   34   // ADC1, aman dipakai bersama WiFi
#define SOIL_SENSOR_PIN 35   // dipakai jika ADA_SENSOR_KELEMBAPAN = true

// ===== LCD I2C =====
#define LCD_ALAMAT 0x27      // SDA = GPIO21, SCL = GPIO22

// ===== BLYNK VIRTUAL PIN =====
#define VPIN_PH   V0
#define VPIN_VOLT V1
#define VPIN_SOIL V2         // hanya dikirim jika ADA_SENSOR_KELEMBAPAN = true

// ===== FITUR =====
// TODO-KONFIRMASI: ubah ke true bila sensor kelembapan sudah dipasang
const bool ADA_SENSOR_KELEMBAPAN = false;
// TODO-KONFIRMASI: ubah ke true bila event Blynk sudah dibuat di Console
const bool AKTIFKAN_NOTIFIKASI = false;
// TODO-KALIBRASI: ubah ke true setelah kalibrasi selesai
const bool SUDAH_KALIBRASI = false;

// ===== INTERVAL BACA & KIRIM =====
const unsigned long INTERVAL_MS = 1000;

// ===== BATAS NOTIFIKASI =====
// TODO-KONFIRMASI: perkiraan awal, konfirmasi ke dosen/penyuluh
const float PH_MIN = 5.5;
const float PH_MAX = 7.5;
const float SOIL_MIN = 35.0;
const float SOIL_MAX = 85.0;

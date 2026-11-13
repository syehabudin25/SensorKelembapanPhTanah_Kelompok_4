#ifndef CONFIG_H
#define CONFIG_H

// ================= PIN HARDWARE ESP32 =================
#define PH_SENSOR_PIN       34
#define MOISTURE_SENSOR_PIN 35

// Pin dan alamat LCD I2C
#define LCD_ADDRESS 0x27
#define LCD_SDA 21
#define LCD_SCL 22

// ================= VIRTUAL PIN BLYNK =================
// Sesuai dashboard Blynk yang sudah digunakan
#define VPIN_PH               V0
#define VPIN_MOISTURE         V1
#define VPIN_STATUS           V2
#define VPIN_MOISTURE_STATUS  V3

// ================= PENGATURAN SENSOR =================
#define JUMLAH_SAMPEL 10
#define JUMLAH_SAMPEL_MOISTURE 20
#define INTERVAL_SENSOR 1500L
#define INTERVAL_LCD 3000UL

#endif

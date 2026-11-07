#ifndef CONFIG_H
#define CONFIG_H

// Pin sensor pH
#define PH_SENSOR_PIN 34

// Pin LCD I2C
#define LCD_ADDRESS 0x27
#define LCD_SDA 21
#define LCD_SCL 22

// Virtual Pin Blynk
#define VPIN_PH V0
#define VPIN_VOLT V1
#define VPIN_STATUS V2

// Pengaturan pembacaan sensor
#define JUMLAH_SAMPEL 10
#define INTERVAL_SENSOR 1000L

#endif
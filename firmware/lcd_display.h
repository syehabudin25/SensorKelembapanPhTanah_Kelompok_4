#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "config.h"

LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);

void printLCDLine(int row, String text) {

    if (text.length() > 16) {
        text = text.substring(0, 16);
    }

    lcd.setCursor(0, row);
    lcd.print(text);

    for (int i = text.length(); i < 16; i++) {
        lcd.print(" ");
    }
}

void lcdMulai() {

    Wire.begin(LCD_SDA, LCD_SCL);
    lcd.init();
    lcd.backlight();
    lcd.clear();

    printLCDLine(0, "MONITORING TANAH");
    printLCDLine(1, "ESP32 STARTING");
}

void lcdStatus(String baris1, String baris2) {

    lcd.clear();
    printLCDLine(0, baris1);
    printLCDLine(1, baris2);
}

// Menampilkan 3 halaman: pH, kelembapan, dan ADC.
void lcdTampilMonitoring(
    float ph,
    float volt,
    String statusPH,
    float kelembapan,
    String statusKelembapan,
    float adcPH,
    int adcMoisture
) {
    static unsigned long lastLCDUpdate = 0;
    static int halamanLCD = 0;

    unsigned long sekarang = millis();

    if (sekarang - lastLCDUpdate >= INTERVAL_LCD) {
        lastLCDUpdate = sekarang;
        halamanLCD = (halamanLCD + 1) % 3;
    }

    if (halamanLCD == 0) {
        printLCDLine(0, "pH:" + String(ph, 2) + " " + String(volt, 2) + "V");
        printLCDLine(1, "Status: " + statusPH);
    }
    else if (halamanLCD == 1) {
        printLCDLine(0, "Moisture:" + String(kelembapan, 1) + "%");
        printLCDLine(1, "Status: " + statusKelembapan);
    }
    else {
        printLCDLine(0, "ADC pH:" + String(adcPH, 0));
        printLCDLine(1, "ADC Air:" + String(adcMoisture));
    }
}

#endif

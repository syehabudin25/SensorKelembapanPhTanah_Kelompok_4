#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "config.h"

// Membuat objek LCD
LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);

// Inisialisasi LCD
void lcdMulai() {

    Wire.begin(LCD_SDA, LCD_SCL);

    lcd.init();
    lcd.backlight();

    lcd.setCursor(0, 0);
    lcd.print("pH Sensor Ready");

    lcd.setCursor(0, 1);
    lcd.print("Connecting...");
}

// Menampilkan status koneksi
void lcdStatus(String baris1, String baris2) {

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print(baris1);

    lcd.setCursor(0, 1);
    lcd.print(baris2);
}

// Menampilkan nilai pH dan kesimpulan
void lcdTampilPH(float ph, String status) {

    lcd.setCursor(0, 0);
    lcd.print("pH: ");
    lcd.print(ph, 2);
    lcd.print("          ");

    lcd.setCursor(0, 1);
    lcd.print(status);
    lcd.print("                ");
}

#endif
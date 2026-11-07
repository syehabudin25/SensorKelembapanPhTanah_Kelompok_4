#define BLYNK_PRINT Serial

#include <Arduino.h>
#include <WiFi.h>

#include "config.h"
#include "secrets.h"
#include "sensor_ph.h"
#include "evaluasi.h"
#include "lcd_display.h"
#include "cloud.h"

BlynkTimer timer;

// =====================================
// PEMBACAAN SENSOR
// =====================================

void sendSensor() {

    // Membaca sensor pH
    HasilPH hasil = bacaSensorPH();

    // Menentukan kondisi tanah
    String statusTanah = klasifikasiTanah(hasil.ph);

    // =================================
    // SERIAL MONITOR
    // =================================

    Serial.println();
    Serial.println("_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-");
    Serial.println("==== KELOMPOK 04 | SISTEM MONITORING PH & KELEMBABAN TANAH ====");
    Serial.println("_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-");

    Serial.print("ADC Average : ");
    Serial.println(hasil.adc, 2);

    Serial.print("Voltage     : ");
    Serial.print(hasil.volt, 3);
    Serial.println(" V");

    Serial.print("pH Value    : ");
    Serial.println(hasil.ph, 2);

    Serial.print("Status Tanah: ");
    Serial.println(statusTanah);

    Serial.println("--------------------------------");

    // =================================
    // LCD DISPLAY
    // =================================

    lcdTampilPH(hasil.ph, statusTanah);

    // =================================
    // WIFI STATUS
    // =================================

    Serial.print("WiFi Status  : ");

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Connected");
    }
    else {
        Serial.println("Disconnected");
    }

    // =================================
    // BLYNK
    // =================================

    Serial.print("Blynk Status : ");

    if (Blynk.connected()) {

        Serial.println("Connected");

        cloudKirim(
            hasil.ph,
            hasil.volt,
            statusTanah
        );

        Serial.println("Data berhasil dikirim ke Blynk!");

    }
    else {

        Serial.println("Disconnected");

    }

    Serial.println("================================");

}

// =====================================
// SETUP
// =====================================

void setup() {

    Serial.begin(115200);
    delay(1500);

    Serial.println();
    Serial.println("==============================");
    Serial.println("SISTEM MONITORING SENSOR pH");
    Serial.println("==============================");

    // Konfigurasi ADC
    analogReadResolution(12);

    pinMode(PH_SENSOR_PIN, INPUT);

    // Inisialisasi LCD
    lcdMulai();

    // =================================
    // WIFI CONNECTION
    // =================================

    Serial.println("Menghubungkan WiFi...");

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);

    int timeout = 0;

    while (WiFi.status() != WL_CONNECTED && timeout < 20) {

        delay(500);
        Serial.print(".");

        timeout++;

    }

    Serial.println();

    if (WiFi.status() == WL_CONNECTED) {

        Serial.println("WiFi Connected!");

        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());

        lcdStatus("WiFi Connected", "Connecting Blynk");

        // =================================
        // BLYNK CONNECTION
        // =================================

        Serial.println("Menghubungkan Blynk...");

        cloudMulai();

        if (Blynk.connect(5000)) {

            Serial.println("Blynk Connected!");

            lcdStatus("WiFi Connected", "Blynk Connected");

        }
        else {

            Serial.println("Blynk Connection Failed!");

            lcdStatus("WiFi Connected", "Blynk Failed");

        }

    }
    else {

        Serial.println("WiFi Connection Failed!");

        lcdStatus("WiFi Failed", "Check Connection");

    }

    delay(1500);
    lcd.clear();

    // =================================
    // TIMER
    // =================================

    timer.setInterval(INTERVAL_SENSOR, sendSensor);

    Serial.println("==============================");
    Serial.println("SETUP SELESAI");
    Serial.println("Monitoring dimulai...");
    Serial.println("==============================");

}

// =====================================
// LOOP
// =====================================

void loop() {

    Blynk.run();

    timer.run();

    // =================================
    // RECONNECT BLYNK SETIAP 5 DETIK
    // =================================

    static unsigned long lastReconnect = 0;

    if (WiFi.status() == WL_CONNECTED &&
        !Blynk.connected()) {

        if (millis() - lastReconnect >= 5000) {

            lastReconnect = millis();

            Serial.println("Mencoba menghubungkan Blynk...");

            Blynk.connect(1000);

        }

    }

    // =================================
    // RECONNECT WIFI SETIAP 10 DETIK
    // =================================

    static unsigned long lastWiFiReconnect = 0;

    if (WiFi.status() != WL_CONNECTED) {

        if (millis() - lastWiFiReconnect >= 10000) {

            lastWiFiReconnect = millis();

            Serial.println("Mencoba menghubungkan WiFi...");

            WiFi.reconnect();

        }

    }

}
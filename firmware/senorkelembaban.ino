#define BLYNK_PRINT Serial

#include <Arduino.h>
#include <WiFi.h>

#include "config.h"
#include "secrets.h"
#include "sensor_ph.h"
#include "sensor_kelembapan.h"
#include "evaluasi.h"
#include "lcd_display.h"
#include "cloud.h"

BlynkTimer timer;

// =====================================
// PEMBACAAN KEDUA SENSOR
// =====================================

void sendSensor() {

    // Membaca sensor pH
    HasilPH hasilPH = bacaSensorPH();

    // Membaca sensor kelembapan
    HasilKelembapan hasilKelembapan = bacaSensorKelembapan();

    // Menentukan status kedua sensor
    String statusTanah = klasifikasiTanah(hasilPH.ph);
    String statusKelembapan = klasifikasiKelembapan(hasilKelembapan.persen);

    // =================================
    // SERIAL MONITOR
    // =================================

    Serial.println();
    Serial.println("========================================");
    Serial.println("MONITORING pH DAN KELEMBAPAN TANAH");
    Serial.println("========================================");

    Serial.println("========== SENSOR pH ==========");
    Serial.print("ADC Average : ");
    Serial.println(hasilPH.adc, 2);

    Serial.print("Voltage     : ");
    Serial.print(hasilPH.volt, 3);
    Serial.println(" V");

    Serial.print("pH Value    : ");
    Serial.println(hasilPH.ph, 2);

    Serial.print("Status pH   : ");
    Serial.println(statusTanah);

    Serial.println();
    Serial.println("====== SENSOR KELEMBAPAN ======");
    Serial.print("ADC Moisture: ");
    Serial.println(hasilKelembapan.adc);

    Serial.print("Kelembapan  : ");
    Serial.print(hasilKelembapan.persen, 2);
    Serial.println(" %");

    Serial.print("Status      : ");
    Serial.println(statusKelembapan);

    Serial.print("ADC Kering  : ");
    Serial.println(NILAI_KERING);

    Serial.print("ADC Basah   : ");
    Serial.println(NILAI_BASAH);

    // =================================
    // LCD DISPLAY
    // =================================

    lcdTampilMonitoring(
        hasilPH.ph,
        hasilPH.volt,
        statusTanah,
        hasilKelembapan.persen,
        statusKelembapan,
        hasilPH.adc,
        hasilKelembapan.adc
    );

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
            hasilPH.ph,
            hasilKelembapan.persen,
            statusTanah,
            statusKelembapan
        );

        Serial.println("Data berhasil dikirim ke Blynk!");
    }
    else {
        Serial.println("Disconnected");
    }

    Serial.println("========================================");
}

// =====================================
// SETUP
// =====================================

void setup() {

    Serial.begin(115200);
    delay(1000);

    Serial.println();
    Serial.println("========================================");
    Serial.println("SISTEM MONITORING pH DAN KELEMBAPAN");
    Serial.println("========================================");

    // Konfigurasi ADC ESP32
    analogReadResolution(12);

    analogSetPinAttenuation(PH_SENSOR_PIN, ADC_11db);
    analogSetPinAttenuation(MOISTURE_SENSOR_PIN, ADC_11db);

    pinMode(PH_SENSOR_PIN, INPUT);
    pinMode(MOISTURE_SENSOR_PIN, INPUT);

    // Inisialisasi LCD
    lcdMulai();

    // =================================
    // WIFI CONNECTION
    // =================================

    lcdStatus("Connecting WiFi", "Please Wait...");
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
            lcdStatus("Blynk Failed", "Local Monitoring");
        }
    }
    else {
        Serial.println("WiFi Connection Failed!");
        lcdStatus("WiFi Failed", "Offline Mode");
    }

    delay(2000);
    lcd.clear();

    // =================================
    // TIMER
    // =================================

    timer.setInterval(INTERVAL_SENSOR, sendSensor);

    Serial.println("========================================");
    Serial.println("SETUP SELESAI");
    Serial.println("Monitoring dimulai...");
    Serial.println("========================================");
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

    if (WiFi.status() == WL_CONNECTED && !Blynk.connected()) {

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

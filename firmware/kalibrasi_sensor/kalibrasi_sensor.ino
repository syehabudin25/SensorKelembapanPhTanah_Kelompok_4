// Sketch bantu kalibrasi (tanpa WiFi/Blynk). Upload dulu sebelum kode utama.
// Buka Serial Monitor 115200.
#define PH_SENSOR_PIN   34
#define SOIL_SENSOR_PIN 35

// Setelah dapat tegangan di buffer, isi dua angka ini lalu upload ulang.
// Sketch akan menghitung PH_SLOPE dan PH_OFFSET otomatis.
const float V_BUFFER_7 = 0.0;   // volt saat probe di buffer pH 7.00
const float V_BUFFER_4 = 0.0;   // volt saat probe di buffer pH 4.01

float rataADC(int pin, int n = 50) {
  long s = 0;
  for (int i = 0; i < n; i++) { s += analogRead(pin); delay(5); }
  return (float)s / n;
}

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
}

void loop() {
  float ph   = rataADC(PH_SENSOR_PIN);
  float soil = rataADC(SOIL_SENSOR_PIN);
  Serial.printf("pH ADC: %.1f (%.3f V) | Tanah ADC: %.1f\n", ph, ph * 3.3 / 4095.0, soil);

  if (V_BUFFER_7 > 0 && V_BUFFER_4 > 0 && V_BUFFER_7 != V_BUFFER_4) {
    float slope  = (7.00 - 4.01) / (V_BUFFER_7 - V_BUFFER_4);
    float offset = 7.00 - slope * V_BUFFER_7;
    Serial.printf("  -> PH_SLOPE = %.3f | PH_OFFSET = %.3f\n", slope, offset);
  }
  delay(1000);
}

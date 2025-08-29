/*
  Ultrasonic Radar with 1D Kalman Filter (Tinkercad-ready)
  - Servo scans 20°..160° and back.
  - HC-SR04 range is filtered by a tiny Kalman to reduce jitter.
  - Serial Plotter prints "angle,filtered_cm,raw_cm".
  - Optional LEDs: STATUS on D12 (blinks), ALERT on D11 (lights when close).
  Wiring:
    Servo: SIG D3, +5V, GND
    HC-SR04: TRIG D9, ECHO D8, Vcc 5V, GND
*/
#include <Servo.h>

Servo s;
const int PIN_SERVO = 3;
const int TRIG = 9, ECHO = 8;
const int LED_STATUS = 12;   // optional
const int LED_ALERT  = 11;   // optional

// ---- Kalman filter scalars for 1D range ----
float x = 100.0f;   // state (cm), initial guess
float P = 50.0f;    // estimate covariance
float Q = 2.0f;     // process noise (tune ↑ for faster response)
float Rm = 30.0f;   // measurement noise (tune ↑ for heavier smoothing)

// Read ultrasonic in microseconds (timeout ~25 ms => ~4 m)
long readEchoUS() {
  digitalWrite(TRIG, LOW); delayMicroseconds(2);
  digitalWrite(TRIG, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  return pulseIn(ECHO, HIGH, 25000UL);
}

// Convert to centimeters, cap to 400 cm (sensor’s rough max)
float readDistanceCM() {
  long t = readEchoUS();
  if (t == 0) return 400.0f;
  return (t * 0.0343f) / 2.0f;
}

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LED_STATUS, OUTPUT);
  pinMode(LED_ALERT, OUTPUT);
  s.attach(PIN_SERVO);
  s.write(90);
  Serial.begin(115200);
  Serial.println("angle,filtered_cm,raw_cm"); // header for CSV-style plotting
}

// Apply one Kalman update given measurement z
float kalman(float z) {
  // Predict (x = x, P = P + Q) since we assume constant distance during tiny step
  P += Q;
  // Update
  float K = P / (P + Rm);
  x = x + K * (z - x);
  P = (1.0f - K) * P;
  return x;
}

void loop() {
  // Sweep forward
  for (int a = 20; a <= 160; a += 2) {
    s.write(a);
    delay(25); // give servo time to settle & reduce echo cross-talk
    float raw = readDistanceCM();
    float filt = kalman(raw);

    // Optional UI: blink status, alert if closer than 25 cm
    digitalWrite(LED_STATUS, (millis() / 250) % 2);
    digitalWrite(LED_ALERT, filt < 25.0f);

    // Plot angle vs distances (Serial Plotter: choose “Plotter”)
    Serial.print(a); Serial.print(",");
    Serial.print(filt, 1); Serial.print(",");
    Serial.println(raw, 1);
  }
  // Sweep backward
  for (int a = 160; a >= 20; a -= 2) {
    s.write(a);
    delay(25);
    float raw = readDistanceCM();
    float filt = kalman(raw);
    digitalWrite(LED_STATUS, (millis() / 250) % 2);
    digitalWrite(LED_ALERT, filt < 25.0f);
    Serial.print(a); Serial.print(",");
    Serial.print(filt, 1); Serial.print(",");
    Serial.println(raw, 1);
  }
}
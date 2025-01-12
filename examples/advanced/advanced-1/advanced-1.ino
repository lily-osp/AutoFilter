#include <AutoFilter.h>

AutoFilter filter;

float prevEstimate = 0.0;      // Initial estimate
float errorCovariance = 1.0;   // Initial error covariance
float processNoise = 0.1;      // Process noise
float measurementNoise = 2.0;  // Measurement noise

void setup() {
    Serial.begin(9600);
}

void loop() {
    float currentMeasurement = analogRead(A0); // Simulated noisy sensor data
    float filteredValue = filter.kalmanFilter(currentMeasurement, prevEstimate, errorCovariance, processNoise, measurementNoise);

    Serial.print("Raw Measurement: ");
    Serial.print(currentMeasurement);
    Serial.print("\tFiltered Value: ");
    Serial.println(filteredValue);

    delay(50);
}

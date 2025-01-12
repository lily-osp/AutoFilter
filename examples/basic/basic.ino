#include <AutoFilter.h>

AutoFilter filter;

float prevOutput = 0.0; // Previous output value
float alpha = 0.2;      // Smoothing factor (0.0 - 1.0)

void setup() {
    Serial.begin(9600);
}

void loop() {
    float currentInput = analogRead(A0); // Simulated noisy input
    float smoothedOutput = filter.lowPassFilter(currentInput, prevOutput, alpha);
    prevOutput = smoothedOutput; // Update previous output

    Serial.print("Smoothed Output: ");
    Serial.println(smoothedOutput);

    delay(50);
}

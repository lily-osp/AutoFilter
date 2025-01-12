#include <AutoFilter.h>

AutoFilter filter;

void setup() {
    Serial.begin(9600);
}

void loop() {
    // Example usage of filters
    float currentInput = analogRead(A0);
    float prevInput = 0.0;
    float prevOutput = 0.0;
    float alpha = 0.1;

    float lowPassed = filter.lowPassFilter(currentInput, prevOutput, alpha);
    float highPassed = filter.highPassFilter(currentInput, prevInput, prevOutput, alpha);

    // Example usage of modulation
    float carrier = 1000.0;
    float signal = 0.5;
    float modulatedSignal = filter.amplitudeModulation(carrier, signal);

    // Print results
    Serial.print("Low Pass Output: ");
    Serial.println(lowPassed);
    Serial.print("High Pass Output: ");
    Serial.println(highPassed);
    Serial.print("Amplitude Modulated Signal: ");
    Serial.println(modulatedSignal);

    delay(100);
}

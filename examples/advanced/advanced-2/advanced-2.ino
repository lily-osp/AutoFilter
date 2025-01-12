#include <AutoFilter.h>

AutoFilter filter;

const int signalSize = 16;          // Number of samples
float inputSignal[signalSize];      // Input signal array
float outputReal[signalSize];       // Real part of DFT
float outputImag[signalSize];       // Imaginary part of DFT

void setup() {
    Serial.begin(9600);

    // Generate a simple sine wave as input signal
    for (int i = 0; i < signalSize; i++) {
        inputSignal[i] = sin(2 * PI * i / signalSize);
    }

    // Perform DFT
    filter.discreteFourierTransform(inputSignal, outputReal, outputImag, signalSize);

    // Print frequency components
    for (int i = 0; i < signalSize; i++) {
        Serial.print("Frequency bin ");
        Serial.print(i);
        Serial.print(": ");
        Serial.print(outputReal[i]);
        Serial.print(" + j");
        Serial.println(outputImag[i]);
    }
}

void loop() {
    // No action needed in loop
}

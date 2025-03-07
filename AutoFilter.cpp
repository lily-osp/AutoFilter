#include "AutoFilter.h"

// Constructor
AutoFilter::AutoFilter() {
    pwmPin = -1;
    pwmFrequency = 1000; // Default frequency
}

// Modulation Methods

float AutoFilter::amplitudeModulation(float carrier, float signal) {
    return carrier * (1.0 + signal);
}

float AutoFilter::frequencyModulation(float carrier, float modulator, float sensitivity) {
    float deltaFreq = sensitivity * modulator;
    return carrier * sin(deltaFreq);
}

float AutoFilter::phaseModulation(float carrier, float modulator, float sensitivity) {
    float phaseShift = sensitivity * modulator;
    return carrier * sin(phaseShift);
}

float AutoFilter::quadratureAmplitudeModulation(float iSignal, float qSignal, float carrier) {
    return (iSignal * cos(carrier) - qSignal * sin(carrier));
}

// Pulse Width Modulation (PWM)
void AutoFilter::pulseWidthModulation(int pin, float dutyCycle, int pwmFrequency) {
    dutyCycle = constrain(dutyCycle, 0.0, 1.0); // Ensure duty cycle is between 0 and 1

    #if defined(ESP32)
    // ESP32-specific PWM setup
    int channel = 0; // Use channel 0
    ledcSetup(channel, pwmFrequency, 8); // Set frequency and 8-bit resolution
    ledcAttachPin(pin, channel);
    ledcWrite(channel, (int)(dutyCycle * 255)); // Set duty cycle (0-255)
    #elif defined(TEENSYDUINO)
    // Teensy-specific PWM setup
    analogWriteFrequency(pin, pwmFrequency);
    analogWrite(pin, (int)(dutyCycle * 255)); // Set duty cycle
    #else
    // Boards without frequency control
    Serial.println("Warning: Custom PWM frequency not supported on this board.");
    analogWrite(pin, (int)(dutyCycle * 255)); // Default analogWrite behavior
    #endif
}

void AutoFilter::dualPulseWidthModulation(int pin1, int pin2, float dutyCycle, int frequency, int phaseShift) {
    // Phase-shifted PWM signals
    pulseWidthModulation(pin1, dutyCycle, frequency);
    delayMicroseconds(phaseShift);  // Adjust phase delay
    pulseWidthModulation(pin2, dutyCycle, frequency);
}

// Filtering Methods

float AutoFilter::lowPassFilter(float currentInput, float prevOutput, float alpha) {
    return alpha * currentInput + (1.0 - alpha) * prevOutput;
}

float AutoFilter::highPassFilter(float currentInput, float prevInput, float prevOutput, float alpha) {
    return alpha * (prevOutput + currentInput - prevInput);
}

float AutoFilter::movingAverageFilter(float input, float *buffer, int bufferSize, int &index) {
    buffer[index] = input;
    index = (index + 1) % bufferSize;

    float sum = 0.0;
    for (int i = 0; i < bufferSize; i++) {
        sum += buffer[i];
    }
    return sum / bufferSize;
}

float AutoFilter::exponentialMovingAverage(float currentInput, float prevOutput, float alpha) {
    return alpha * currentInput + (1.0 - alpha) * prevOutput;
}

float AutoFilter::kalmanFilter(float currentMeasurement, float &prevEstimate, float &errorCovariance, float processNoise, float measurementNoise) {
    float kalmanGain = errorCovariance / (errorCovariance + measurementNoise);
    float currentEstimate = prevEstimate + kalmanGain * (currentMeasurement - prevEstimate);
    errorCovariance = (1 - kalmanGain) * errorCovariance + fabs(prevEstimate - currentEstimate) * processNoise;
    prevEstimate = currentEstimate;
    return currentEstimate;
}

// Utility Functions

float AutoFilter::normalize(float input, float inputMin, float inputMax, float outputMin, float outputMax) {
    return (input - inputMin) * (outputMax - outputMin) / (inputMax - inputMin) + outputMin;
}

void AutoFilter::discreteFourierTransform(float *input, float *outputReal, float *outputImag, int size) {
    for (int k = 0; k < size; k++) {
        outputReal[k] = 0;
        outputImag[k] = 0;
        for (int n = 0; n < size; n++) {
            float angle = -2 * M_PI * k * n / size;
            outputReal[k] += input[n] * cos(angle);
            outputImag[k] += input[n] * sin(angle);
        }
    }
}

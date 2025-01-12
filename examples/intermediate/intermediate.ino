#include <AutoFilter.h>

AutoFilter filter;

int pin1 = 9; // First PWM pin
int pin2 = 10; // Second PWM pin
float dutyCycle = 0.5; // 50% duty cycle
int frequency = 1000;  // 1 kHz frequency
int phaseShift = 500;  // Phase shift in microseconds

void setup() {
    filter.dualPulseWidthModulation(pin1, pin2, dutyCycle, frequency, phaseShift);
}

void loop() {
    // PWM signals are continuously generated in the background
}

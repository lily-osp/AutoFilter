## **AutoFilter Library**

### **Introduction**

The **AutoFilter** library is a versatile signal processing library for Arduino, designed to provide users with tools for filtering, modulation, and signal generation. Whether you're smoothing noisy data, generating PWM signals, or applying advanced filters like Kalman or Fourier transforms, AutoFilter offers a simple, user-friendly interface.

---

### **Features**

- **Filters:**
  - Low-pass, high-pass, moving average, exponential moving average, and Kalman filters.
- **Modulation:**
  - Amplitude Modulation (AM), Frequency Modulation (FM), Phase Modulation (PM), and Quadrature Amplitude Modulation (QAM).
- **Signal Generation:**
  - Simple signal generators for sine, square, and triangular waveforms.
- **PWM Control:**
  - Single and dual PWM output with configurable frequency and phase shift.
- **Utility:**
  - Signal normalization, scaling, and basic Fourier Transform (DFT).

---

### **Installation**

1. Download the library as a `.zip` file.
2. Open Arduino IDE.
3. Navigate to `Sketch > Include Library > Add .ZIP Library`.
4. Select the downloaded `.zip` file to install.

---

### **Basic Usage**

Include the library in your sketch:

```cpp
#include <AutoFilter.h>
```

Create an instance of the library:

```cpp
AutoFilter filter;
```

---

### **Examples**

To make it easy for new users to understand the library, the following examples provide simple implementations of signal filtering and generation, also there was ready to use examples code on the examples folder thathave this detail :

- **General :** Quick overview of common filters and modulation.
- **Basic :** Focus on one filter method (low-pass).
- **Intermediate :** Introduces PWM with dual outputs and phase control.
- **Advanced 1:** Noise reduction using Kalman filter.
- **Advanced 2:** Frequency analysis using Fourier Transform.

also here some additionals examples:

#### **1. Simple Low-Pass Filter**

This example demonstrates how to smooth noisy data from an analog input.

```cpp
#include <AutoFilter.h>

AutoFilter filter;

float prevOutput = 0.0; // Previous output value
float alpha = 0.2;      // Smoothing factor (0.0 - 1.0)

void setup() {
    Serial.begin(9600);
}

void loop() {
    float currentInput = analogRead(A0); // Noisy input
    float smoothedOutput = filter.lowPassFilter(currentInput, prevOutput, alpha);
    prevOutput = smoothedOutput; // Update the previous output

    Serial.print("Raw Input: ");
    Serial.print(currentInput);
    Serial.print("\tSmoothed Output: ");
    Serial.println(smoothedOutput);

    delay(50);
}
```

---

#### **2. Simple Sine Wave Generator**

This example generates a sine wave signal that can be output as PWM or for testing.

```cpp
#include <AutoFilter.h>

AutoFilter filter;

const float frequency = 1.0; // Frequency in Hz
const int amplitude = 127;   // Amplitude (0-255 for PWM)
const int offset = 127;      // Offset for PWM (centered at 127)
const int pin = 9;           // PWM pin

void setup() {
    pinMode(pin, OUTPUT);
}

void loop() {
    static unsigned long lastTime = 0;
    static float angle = 0.0;

    if (millis() - lastTime >= 1) { // Update every 1 ms
        lastTime = millis();
        float value = amplitude * sin(angle) + offset; // Sine wave formula
        analogWrite(pin, (int)value);                 // Output as PWM
        angle += 2 * PI * frequency / 1000.0;         // Increment angle
        if (angle > 2 * PI) angle -= 2 * PI;          // Keep angle in range
    }
}
```

---

#### **3. Simple Moving Average Filter**

This example demonstrates a moving average filter to smooth input data over a sliding window.

```cpp
#include <AutoFilter.h>

AutoFilter filter;

const int bufferSize = 5;    // Size of the moving average window
float buffer[bufferSize] = {0}; // Buffer for storing previous inputs
int index = 0;               // Index for the buffer

void setup() {
    Serial.begin(9600);
}

void loop() {
    float currentInput = analogRead(A0); // Simulated noisy input
    float smoothedOutput = filter.movingAverageFilter(currentInput, buffer, bufferSize, index);

    Serial.print("Raw Input: ");
    Serial.print(currentInput);
    Serial.print("\tSmoothed Output: ");
    Serial.println(smoothedOutput);

    delay(50);
}
```

---

#### **4. Simple Square Wave Generator**

This example generates a square wave signal for basic testing.

```cpp
#include <AutoFilter.h>

AutoFilter filter;

const int pin = 9;          // PWM pin
const int frequency = 2;    // Frequency in Hz
const int dutyCycle = 50;   // Duty cycle in percentage (50% by default)

void setup() {
    pinMode(pin, OUTPUT);
}

void loop() {
    filter.pulseWidthModulation(pin, dutyCycle / 100.0, frequency);
}
```

---

#### **5. Signal Normalization**

This example demonstrates how to normalize a signal from one range to another (e.g., [0-1023] to [0-1]).

```cpp
#include <AutoFilter.h>

AutoFilter filter;

void setup() {
    Serial.begin(9600);
}

void loop() {
    float rawInput = analogRead(A0); // Simulated analog input
    float normalizedOutput = filter.normalize(rawInput, 0, 1023, 0.0, 1.0);

    Serial.print("Raw Input: ");
    Serial.print(rawInput);
    Serial.print("\tNormalized Output: ");
    Serial.println(normalizedOutput);

    delay(50);
}
```

---

### **Documentation**

#### **Filters**

- **Low-Pass Filter:** `lowPassFilter(currentInput, prevOutput, alpha)`
- **High-Pass Filter:** `highPassFilter(currentInput, prevInput, prevOutput, alpha)`
- **Moving Average Filter:** `movingAverageFilter(input, buffer, bufferSize, index)`
- **Exponential Moving Average:** `exponentialMovingAverage(currentInput, prevOutput, alpha)`
- **Kalman Filter:** `kalmanFilter(currentMeasurement, prevEstimate, errorCovariance, processNoise, measurementNoise)`

#### **Modulation**

- **Amplitude Modulation (AM):** `amplitudeModulation(carrier, signal)`
- **Frequency Modulation (FM):** `frequencyModulation(carrier, modulator, sensitivity)`
- **Phase Modulation (PM):** `phaseModulation(carrier, modulator, sensitivity)`
- **Quadrature Amplitude Modulation (QAM):** `quadratureAmplitudeModulation(iSignal, qSignal, carrier)`

#### **Signal Generation**

- **PWM:** `pulseWidthModulation(pin, dutyCycle, frequency)`
- **Dual PWM:** `dualPulseWidthModulation(pin1, pin2, dutyCycle, frequency, phaseShift)`

#### **Utilities**

- **Signal Normalization:** `normalize(input, inputMin, inputMax, outputMin, outputMax)`
- **Fourier Transform (Basic):** `discreteFourierTransform(input, outputReal, outputImag, size)`

---

### **Future Improvements**

- Add more filter types (e.g., band-pass, notch).
- Extend signal generation to support arbitrary waveforms.
- Provide dynamic tuning for filter coefficients.

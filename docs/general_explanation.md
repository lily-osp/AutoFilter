# General Explanation of Algorithms and Techniques Used in AutoFilter Library

The **AutoFilter** library is a versatile Arduino library designed for signal processing, modulation, and utility operations. It combines commonly used algorithms and techniques from control systems, signal processing, and digital modulation to offer a robust and flexible solution for various applications. This document provides a detailed explanation of the algorithms and techniques implemented in the library.

---

## 1. **Filtering Techniques**

Filters are essential in signal processing for reducing noise, extracting useful information, or shaping the frequency spectrum of a signal. The AutoFilter library provides several filtering methods, including:

### 1.1 **Low-Pass Filter**

- **Purpose:** Allows low-frequency signals to pass while attenuating higher-frequency components.

- **Algorithm:**
  
  - The low-pass filter is implemented using a simple exponential smoothing formula:
    
    $y[n] = \alpha \cdot x[n] + (1 - \alpha) \cdot y[n-1]$
    
    Where:
    
    - \($ y[n]$ \) is the current filtered value.
    - \( $x[n]$ \) is the current input value.
    - \( $\alpha$ \) is the smoothing factor (0 < \( $\alpha$ \) < 1).
  
  - This formula balances the trade-off between smoothness and responsiveness.

### 1.2 **High-Pass Filter**

- **Purpose:** Allows high-frequency signals to pass while attenuating lower-frequency components.

- **Algorithm:**
  
  - The high-pass filter is implemented as:
    
    $y[n] = \alpha \cdot (y[n-1] + x[n] - x[n-1])$
    
    Where \( $\alpha$ \) controls the filter's responsiveness.

### 1.3 **Moving Average Filter**

- **Purpose:** Smooths data by averaging input values over a sliding window.

- **Algorithm:**
  
  - The moving average is calculated as:
    
    $y[n] = \frac{1}{N} \sum_{i=0}^{N-1} x[n-i]$
    
    Where \( $N$ \) is the window size.

- **Usage:** Ideal for removing random noise while retaining signal trends.

### 1.4 **Exponential Moving Average**

- **Purpose:** Similar to the moving average filter but gives more weight to recent data points.

- **Algorithm:**
  
  - Uses the same formula as the low-pass filter:
    
    $y[n] = \alpha \cdot x[n] + (1 - \alpha) \cdot y[n-1]$

- **Advantages:** Provides a balance between noise reduction and signal lag.

### 1.5 **Kalman Filter**

- **Purpose:** Estimates the true value of a signal by minimizing the mean of squared errors.

- **Algorithm:**
  
  - The Kalman filter uses a prediction-correction model:
    
    1. **Prediction:** Predict the next state using the previous state.
    2. **Correction:** Adjust the prediction based on the measurement.
    
    $\text{Estimate} = \text{Prediction} + \text{Kalman Gain} \cdot (\text{Measurement} - \text{Prediction})$

- **Applications:** Ideal for dynamic systems and noisy environments.

---

## 2. **Modulation Techniques**

Modulation involves altering a carrier signal based on an input signal to encode information. The library supports several modulation methods:

### 2.1 **Amplitude Modulation (AM)**

- **Purpose:** Modulates the amplitude of a carrier signal based on the input signal.

- **Algorithm:**
  
  - The modulated signal is computed as:
    
    $y(t) = [1 + m \cdot x(t)] \cdot \cos(2 \pi f_c t)$
    
    Where:
    
    - \( $m$ \) is the modulation index.
    - \( $f_c$ \) is the carrier frequency.

### 2.2 **Frequency Modulation (FM)**

- **Purpose:** Modulates the frequency of a carrier signal based on the input signal.

- **Algorithm:**
  
  - The modulated signal is computed as:
    
    $y(t) = \cos\left(2 \pi f_c t + m \int x(t) dt\right)$
    
    Where \( $m$ \) is the frequency sensitivity.

### 2.3 **Phase Modulation (PM)**

- **Purpose:** Modulates the phase of a carrier signal based on the input signal.

- **Algorithm:**
  
  - The modulated signal is computed as:
    
    $y(t) = \cos\left(2 \pi f_c t + m \cdot x(t)\right)$

### 2.4 **Quadrature Amplitude Modulation (QAM)**

- **Purpose:** Combines amplitude modulation of two carrier signals in quadrature (90-degree phase difference).

- **Algorithm:**
  
  - The modulated signal is:
    
    $y(t) = A_I \cdot \cos(2 \pi f_c t) + A_Q \cdot \sin(2 \pi f_c t)$
    
    Where \( $A_I$ \) and \( $A_Q$ \) are the amplitudes of the in-phase and quadrature components.

---

## 3. **Signal Generation Techniques**

Signal generation is essential for testing and control. The library provides waveform generators for:

### 3.1 **Sine Wave**

- **Purpose:** Generates a smooth, periodic signal.

- **Algorithm:**
  
  - The sine wave is computed as:
    
    $y(t) = A \cdot \sin(2 \pi f t + \phi)$
    
    Where \( $A$ \) is the amplitude, \( $f$ \) is the frequency, and \( $\phi$ \) is the phase.

### 3.2 **Square Wave**

- **Purpose:** Generates a digital signal alternating between two levels.

- **Algorithm:**
  
  - The square wave alternates based on time and frequency:
    
    $y(t) = \begin{cases}
    A & \text{if } \sin(2 \pi f t) \geq 0 \\
    -A & \text{if } \sin(2 \pi f t) < 0
    \end{cases}$

### 3.3 **Triangular Wave**

- **Purpose:** Generates a linear periodic signal with a triangular shape.
- **Algorithm:**
  - The triangular wave uses piecewise linear functions based on time intervals.

---

## 4. **Utility Functions**

Utility functions provide additional operations to enhance signal processing:

### 4.1 **Normalization**

- **Purpose:** Maps a signal from one range to another (e.g., [0, 1023] to [0, 1]).

- **Algorithm:**
  
  - The normalized signal is:
    
    $y = \frac{(x - x_{\text{min}})}{(x_{\text{max}} - x_{\text{min}})} \cdot (y_{\text{max}} - y_{\text{min}}) + y_{\text{min}}$

### 4.2 **Fourier Transform**

- **Purpose:** Analyzes a signal in the frequency domain.

- **Algorithm:**
  
  - The Discrete Fourier Transform (DFT) is computed as:
    
    $X[k] = \sum_{n=0}^{N-1} x[n] \cdot e^{-j 2 \pi k n / N}$
    
    Where \( $N$ \) is the number of samples.

### 4.3 **Signal Scaling**

- **Purpose:** Adjusts a signal's range based on a scaling factor.

- **Algorithm:**
  
  - The scaled signal is computed as:
    
    $y = x \cdot \text{scaleFactor}$

---

## 5. **PWM Control**

Pulse Width Modulation (PWM) controls the average voltage by modulating the duty cycle of a digital signal:

- **Single PWM:** Outputs a PWM signal on a single pin.
- **Dual PWM:** Generates two PWM signals with a specified phase shift.

---

This library integrates these algorithms and techniques to provide a comprehensive signal processing toolkit

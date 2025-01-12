---
config:
  theme: neo
  layout: elk
---
flowchart TD
    Filtering["Filtering Functions"] -- "Low-Pass" --> LowPassFilter["Low-Pass Filter"]
    Filtering -- "High-Pass" --> HighPassFilter["High-Pass Filter"]
    Filtering -- Moving Average --> MovingAvgFilter["Moving Average Filter"]
    Filtering -- Exponential Moving Avg --> ExpMovingAvg["Exponential Moving Average"]
    Filtering -- Kalman --> KalmanFilter["Kalman Filter"]
    Modulation["Modulation Functions"] -- AM --> AmMod["Amplitude Modulation"]
    Modulation -- FM --> FmMod["Frequency Modulation"]
    Modulation -- PM --> PmMod["Phase Modulation"]
    Modulation -- QAM --> QamMod["Quadrature Amplitude Modulation"]
    SignalGen["Signal Generation Functions"] -- PWM --> PwmGen["PWM Generator"]
    SignalGen -- Dual PWM --> DualPwmGen["Dual PWM Generator"]
    SignalGen -- Sine Wave --> SineGen["Sine Wave Generator"]
    SignalGen -- Square Wave --> SquareGen["Square Wave Generator"]
    SignalGen -- Triangular Wave --> TriangleGen["Triangular Wave Generator"]
    Utilities["Utility Functions"] -- Normalize --> NormalizeFn["Normalize Signal"]
    Utilities -- Fourier Transform --> FourierFn["Discrete Fourier Transform"]
    Utilities -- Signal Scaling --> ScalingFn["Signal Scaling"]
    LowPassFilter --> FilterOutput1["Filtered Signal Output"]
    HighPassFilter --> FilterOutput2["Filtered Signal Output"]
    MovingAvgFilter --> FilterOutput3["Filtered Signal Output"]
    ExpMovingAvg --> FilterOutput4["Filtered Signal Output"]
    KalmanFilter --> FilterOutput5["Filtered Signal Output"]
    AmMod --> ModulatedOutput1["Modulated Signal Output"]
    FmMod --> ModulatedOutput2["Modulated Signal Output"]
    PmMod --> ModulatedOutput3["Modulated Signal Output"]
    QamMod --> ModulatedOutput4["Modulated Signal Output"]
    PwmGen --> PwmOutput1["PWM Signal Output"]
    DualPwmGen --> PwmOutput2["Dual PWM Signal Output"]
    SineGen --> SignalOutput1["Generated Sine Wave"]
    SquareGen --> SignalOutput2["Generated Square Wave"]
    TriangleGen --> SignalOutput3["Generated Triangular Wave"]
    NormalizeFn --> UtilityOutput1["Normalized Signal"]
    FourierFn --> UtilityOutput2["Frequency Components"]
    ScalingFn --> UtilityOutput3["Scaled Signal"]
    Start(["Start"]) --> InitLibrary(["Initialize Library"])
    InitLibrary --> InputData(["Input Signal Data"])
    InputData --> ChooseFunction{"Choose Functionality"}
    ChooseFunction --> Filtering & Modulation & SignalGen & Utilities
    FilterOutput1 --> End(["End"])
    FilterOutput2 --> End
    FilterOutput3 --> End
    FilterOutput4 --> End
    FilterOutput5 --> End
    ModulatedOutput1 --> End
    ModulatedOutput2 --> End
    ModulatedOutput3 --> End
    ModulatedOutput4 --> End
    PwmOutput1 --> End
    PwmOutput2 --> End
    SignalOutput1 --> End
    SignalOutput2 --> End
    SignalOutput3 --> End
    UtilityOutput1 --> End
    UtilityOutput2 --> End
    UtilityOutput3 --> End

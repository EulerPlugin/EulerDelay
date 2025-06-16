## 4. Filter

### 🔷 Overview

This module shapes the tone of the feedback signal using a high-pass and a low-pass filter. 
It is placed inside the feedback loop to prevent excessive low-end buildup and high-frequency ringing, ensuring a cleaner and more controlled delay tail.

<br>

🔧 Implementation

![image](https://github.com/user-attachments/assets/1233fddd-f2be-416d-b099-6fa7133dc35d)

The filter module is implemented using juce::dsp::StateVariableTPTFilter<float>, which is a zero-delay feedback (ZDF) state variable filter offering superior stability and real-time control compared to traditional biquad filters(IIR, FIR).

Two separate filters are used:

mFilterLowCut: High-pass filter to remove low-frequency rumble
mFilterHighCut: Low-pass filter to tame harsh high frequencies
~~~cpp
mFilterLowCut.setType(juce::dsp::StateVariableTPTFilterType::highpass);
mFilterHighCut.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
~~~

<br>

### 🔁 Traditional IIR Structure (Biquad):

\[
y[n] = b_0x[n] + b_1x[n-1] + b_2x[n-2] - a_1y[n-1] - a_2y[n-2]
\]

- This relies on **delayed samples** (`x[n-1]`, `y[n-1]`, etc.)
- Real-time changes to **cutoff** or **Q** require coefficient recalculation
- Causes **clicks**, **zipper noise**, or **instability**, especially at high resonance

<br>

### ✅ ZDF Advantage:

- Feedback is resolved **instantly**, with **no delay buffers**
- **Smooth, stable** response to parameter changes
- **High-Q operation** remains artifact-free and numerically stable

<br>

🔧 Optimization Note

To reduce CPU load, the filter’s cutoff frequency is updated only when the value changes, avoiding expensive recalculations every sample.

~~~cpp
if (inCutoff != mFilterLowCut.getCutoffFrequency())
    mFilterLowCut.setCutoffFrequency(inCutoff);

if (inCutoff != mFilterHighCut.getCutoffFrequency())
    mFilterHighCut.setCutoffFrequency(inCutoff);
~~~
This keeps performance efficient while maintaining smooth, stable filtering.

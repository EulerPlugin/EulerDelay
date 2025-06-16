## 4. Filter

### 🔷 Overview

This module shapes the tone of the feedback signal using a high-pass and a low-pass filter. 
It is placed inside the feedback loop to prevent excessive low-end buildup and high-frequency ringing, ensuring a cleaner and more controlled delay tail.

<br>

🔧 Implementation

The filter module is implemented using juce::dsp::StateVariableTPTFilter<float>, which is a zero-delay feedback (ZDF) state variable filter offering superior stability and real-time control compared to traditional biquad filters.

Two separate filters are used:

mFilterLowCut: High-pass filter to remove low-frequency rumble
mFilterHighCut: Low-pass filter to tame harsh high frequencies
Both are configured and processed per channel using processSample():

~~~cpp
mFilterLowCut.setType(juce::dsp::StateVariableTPTFilterType::highpass);
mFilterHighCut.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
~~~

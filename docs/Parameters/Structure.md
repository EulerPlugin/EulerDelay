### 2. Parameter Initialization & Structure

<br>

🎯 Design Objective

All parameters are initialized through AudioProcessorValueTreeState (APVTS) using a single layout definition.
Within the MyParameters class, each parameter is explicitly cast and stored as a pointer for efficient access.
This architecture enables **real-time safety, modular separation, and high-performance parameter updates.**

<br>

🔹 1) Parameter Creation – initparameterLayout()

- All parameters are created via **std::make_unique <<juce::AudioParameter*>>**
- UI display formatting (e.g., dB, %, ms, Hz) is abstracted using **withStringFromValueFunction()** and related methods:

~~~cpp
layout.add(std::make_unique<juce::AudioParameterFloat>(
    MyParamId::Output::Gain, "Gain",
    juce::NormalisableRange<float>(-24.0f, 24.0f, 0.1f),
    0.0f,
    juce::AudioParameterFloatAttributes()
        .withStringFromValueFunction(stringFromDecibels)));
~~~

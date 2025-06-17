### 2. Parameter Initialization & Structure

<br>
<br>

🎯 Design Objective

All parameters are initialized through AudioProcessorValueTreeState (APVTS) using a single layout definition.
Within the MyParameters class, each parameter is explicitly cast and stored as a pointer for efficient access.
This architecture enables **real-time safety, modular separation, and high-performance parameter updates.**

<br>
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

✅ Advantages
- Unit formatting is preprocessed at construction time → **no runtime conversion overhead**
- UI-friendly display is separated from internal floating-point logic

<br>
<br>

🔹 2) Parameter Referencing – castParameter()

~~~cpp
template <typename T>
static void castParameter(juce::AudioProcessorValueTreeState& inApvts,
                          const juce::ParameterID& inParamId, T& inDestination)
{
    inDestination = dynamic_cast<T>(inApvts.getParameter(inParamId.getParamID()));
    jassert(inDestination);
}
~~~
- During class construction, each parameter is cast using its ID and stored in a member pointer (e.g., mParamGain, mParamTime[2]).

✅ Advantages

- jassert guards against invalid casts or missing parameters.
- Avoids repeated getParameter() calls in real-time code → **direct pointer access is faster**


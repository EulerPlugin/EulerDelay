## 2. Parameter Initialization & Structure

<br>

### 🎯 Design Objective

All parameters are initialized through AudioProcessorValueTreeState (APVTS) using a single layout definition.
Within the MyParameters class, each parameter is explicitly cast and stored as a pointer for efficient access.
This architecture enables **real-time safety, modular separation, and high-performance parameter updates.**

<br>
<br>

### 🔹 1) Parameter Creation – initparameterLayout()

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

### ✅ Advantages
- Unit formatting is preprocessed at construction time → **no runtime conversion overhead**
- UI-friendly display is separated from internal floating-point logic

<br>
<br>

### 🔹 2) Parameter Referencing – castParameter()

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

### ✅ Advantages

- jassert guards against invalid casts or missing parameters.
- Avoids repeated getParameter() calls in real-time code → **direct pointer access is faster**

<br>
<br>

### 🔹 3) Structural Benefits & Encapsulation

✅ Centralized parameter access
- All parameter logic is encapsulated within MyParameters.
- GUI, DSP, and preset systems access parameters only through this class → **single entry point**

  
✅ Real-time optimized access
- Conventional access via getParameter("id")->get() incurs lookup overhead
- With pre-stored pointers (e.g., mParamGain->get()), access is **constant time** and **cache-friendly**
  
✅ Decoupling from GUI logic
- GUI controls use AudioProcessorValueTreeState for automatic binding (SliderAttachment, etc.)
- MyParameters handles only internal parameter logic, enabling **clear separation of concerns**

<br>
<br>

### 🔹 4) Additional Architectural Notes

📌 ID Abstraction
- Parameter IDs are managed through symbolic constants (e.g., MyParamId::Output::Gain)
- Prevents hardcoded strings and reduces risk during refactoring

  
📌 CPU Cache Optimization
- Parameter pointers are stored as inline members, improving **memory locality**
- In tight update loops, this layout helps reduce **cache misses**

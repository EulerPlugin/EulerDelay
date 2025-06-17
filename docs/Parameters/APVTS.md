## 1. Why AudioProcessorValueTreeState

This plugin uses JUCE’s AudioProcessorValueTreeState (APVTS) to manage parameters.
This is not a trivial choice, but a deliberate design decision based on real-time safety, structural clarity, and long-term maintainability.

<br>

🔹 1) Real-Time Automation & Host Synchronization

**Reason:**

In modern DAWs, automation curves modify parameters continuously during playback.
If the audio thread reads a parameter while the UI or host is writing to it, it can cause race conditions, glitches, or crashes.

**Solution:**

APVTS exposes parameters as **std::atomic<float>** internally. Combined with SmoothedValue, this enables thread-safe reading in the audio callback.

~~~cpp
mValueHighCut.setTargetValue(mParamHighCut->get());  // set from UI/host (thread-safe)
float current = mValueHighCut.getCurrentValue();      // read in audio thread
~~~

<br>
<br>

🔹 2) Consistent State Save/Recall

**Reason:**

Presets, session recall, and version compatibility require saving and restoring all parameters reliably.

**Solution:**

APVTS serializes all parameters into a **ValueTree** object, which can be easily converted to/from XML.

~~~cpp
juce::ValueTree state = mApvts.copyState();     // saving
mApvts.replaceState(state);                     // loading
~~~

<br>
<br>

🔹 3) Efficient GUI Binding

**Reason:**

Linking GUI controls (e.g., sliders) to parameters manually is tedious and error-prone.
Redundant redraws can also hurt performance.

**Solution:**

APVTS supports SliderAttachment, ButtonAttachment, etc., which auto-bind parameters to controls and only trigger redraws when necessary.

~~~cpp
castParameter(mApvts, MyParamId::Output::Gain, mParamGain);
// Later used with SliderAttachment in the GUI layer
~~~

<br>
<br>

🔹 4) Custom String Representation

**Reason:**

Users expect readable values like “500ms”, “-6dB”, or “80%” in the UI, while the DSP requires raw float values.

**Solution:**

APVTS supports .withStringFromValueFunction() and .withValueFromStringFunction() to define two-way conversions.

~~~cpp
.withStringFromValueFunction(stringFromMilliseconds)
.withValueFromStringFunction(milliSecondsFromString)

static juce::String stringFromMilliseconds(float inValue, int)
{
    return (inValue < 1000.0f)
        ? juce::String(inValue, 1) + "ms"
        : juce::String(inValue * 0.001f, 4) + "s";
}
~~~

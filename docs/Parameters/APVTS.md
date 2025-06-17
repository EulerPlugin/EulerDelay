### 1. Why AudioProcessorValueTreeState

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

## Plugin State Management

<br>

### **📌 Overview**

The functions ```getStateInformation()``` and ```setStateInformation()``` are used by the host (DAW)
to save and restore a plugin’s internal state during project saves and loads.

This implementation goes beyond just saving parameter values — it captures both:

- the **parameter state** (via APVTS)
- the **preset metadata** (e.g., selected preset name)
All this is serialized into a single **hierarchical** ```ValueTree``` **structure** for maximum clarity, extensibility, and reliability.

<br>
<br>

### 🌳 ValueTree Structure (Hierarchy Overview)

~~~cpp
Root: ValueTree("EulerDelay")      ← JucePlugin_Name
├── Child 1: ValueTree("Parameters") ← mApvts.copyState()
├── Child 2: ValueTree("Preset")     ← mPresetManager.getState()
~~~

Everything is encapsulated under a single root node (```JucePlugin_Name```),
ensuring the plugin's state is self-contained and organized.

<br>

-----

<br>

### 1️⃣ Saving Plugin State

~~~cpp
void EulerDelayAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    juce::ValueTree statePlugin(JucePlugin_Name);  // Root: "EulerDelay"

    // 1. Save parameter state
    const juce::ValueTree stateParameter = mApvts.copyState();
    statePlugin.appendChild(stateParameter, nullptr);

    // 2. Save preset metadata (e.g., current preset name)
    const juce::ValueTree statePreset = mPresetManager.getState();
    statePlugin.appendChild(statePreset, nullptr);

    // 3. Convert to XML and serialize
    std::unique_ptr<juce::XmlElement> xmlState = statePlugin.createXml();
    if (xmlState)
    {
        copyXmlToBinary(*xmlState, destData);
    }
}
~~~

✅ Both parameter values and preset name are saved as distinct child nodes inside the same root tree.


<br>
<br>

## 2️⃣ Restoring Plugin State

~~~cpp
void EulerDelayAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml = getXmlFromBinary(data, sizeInBytes);
    if (!xml) return;

    juce::ValueTree statePlugin = juce::ValueTree::fromXml(*xml);
    if (!statePlugin.isValid() || statePlugin.getType().toString() != JucePlugin_Name)
        return;

    // 1. Restore preset name
    const auto statePreset = statePlugin.getChildWithName(mPresetManager.getIdState());
    if (statePreset.isValid())
        mPresetManager.setByState(statePreset);

    // 2. Restore parameters
    const auto stateParameter = statePlugin.getChildWithName(mApvts.state.getType());
    if (stateParameter.isValid())
        mApvts.replaceState(stateParameter);
}
~~~

✅ The ValueTree structure enables selective and modular restoration.
Each part of the plugin (preset, parameters) is restored independently but within one consistent structure.


<br>
<br>

### 3️⃣ Preset Metadata Node

~~~cpp
juce::ValueTree MyPresetManager::getState() const noexcept
{
    juce::ValueTree state(getIdState());  // Type: "Preset"
    state.setProperty("name", getXmlPresetCurrent(), nullptr);
    return state;
}
~~~

- Returns a ValueTree node of type "Preset"
- Stores the currently selected XML preset name
- Added as a child node to the root during state save

<br>
<br>

### 4️⃣ Preset Restoration

~~~cpp
void MyPresetManager::setByState(const juce::ValueTree& inState) noexcept
{
    if (inState.isValid() && inState.getType() == getIdState())
    {
        const juce::String namePreset = inState.getProperty("name");
        setXmlPresetCurrnet(namePreset);  // Update ComboBox display
    }
}
~~~

- This restores the selected preset name from the saved state
- It does not affect parameter values — it’s for UI consistency and user context restoration

<br>
<br>

### ✅ Practical Advantages of This Structure

**🔹 1. Beyond parameters**

Stores preset names, UI states, and metadata — not just knob values.

**🔹 2. Clear hierarchy**

Named tree nodes prevent conflicts and support version-safe loading.

**🔹 3. Modular architecture**

APVTS handles parameters, PresetManager handles metadata → easy to maintain and test.

**🔹 4. Debug & verify**

State can be saved as XML for inspection or manual editing.

**🔹 5. Easy to extend**

Add new features (e.g., recent presets) by appending child nodes — no rewrites needed.

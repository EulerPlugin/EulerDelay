## Factory Preset System

<br>

### 📌 **Introduction**

The Factory Preset system provides a set of hardcoded parameter values directly 
embedded into the plugin.Users can select from these presets using a combo box, instantly applying them to 
the processor without relying on any external files.
It’s ideal for testing, resetting, or providing reliable default states.

<br>
<br>

### **⚙️ Architecture & Flow**

**1. Component Hierarchy (Top-Down)**

~~~cpp
EulerDelayAudioProcessorEditor
└── mPanelControl
    └── MyPresetComboBox
~~~

<br>

**2. Execution Flow (Bottom-Up)**

~~~cpp
User clicks ComboBox
  ↓
MyPresetComboBox → MyPresetManager → MyParameters → APVTS
~~~

<br>
<br>

### **🔁 Runtime Flow**

**1. User selects a preset from ComboBox**

~~~cpp
// MyPresetComboBox::MyPresetComboBox()
onChange = [this]()
{
    const int id = getSelectedId();
    if (id == 0) return;

    mPresetManager.setFactoryPreset(id - 1);  // 🔥 Triggers preset application
};
~~~

✅ The selected index is passed to the preset manager.
```id - 1``` maps the ComboBox item to the correct internal preset array index.
This line is critical — without it, nothing is applied.


<br>

**2. PresetManager applies the preset**

~~~cpp
// MyPresetManager::setFactoryPreset()
void MyPresetManager::setFactoryPreset(int inIndex) noexcept
{
    mFactoryPresetCurrent = inIndex;
    mParameters.setParamsByFactoryPreset(mArrayFactoryPreset[inIndex]);
}
~~~

✅ The selected preset is retrieved from the array and passed to ```MyParameters``` for application.
PresetManager itself doesn’t touch parameter values — it delegates.

<br>

**3. Parameters are directly updated**

~~~cpp
// MyParameters::setParamsByFactoryPreset()
void MyParameters::setParamsByFactoryPreset(const FactoryPreset& inPreset) noexcept
{
    for (int i = 0; i < 2; ++i)
        *mParamTime[i] = inPreset.mTime[i];

    *mParamAmount = inPreset.mFeedback;
    *mParamMix    = inPreset.mMix;
    *mParamGain   = inPreset.mGain;
}
~~~

✅ The values from the selected preset are directly assigned to AudioProcessorValueTreeState parameters.
This happens immediately with no smoothing or delay.
All key parameters (Delay Time L/R, Feedback, Mix, Gain) are included.

<br>

**4. Preset definitions are hardcoded**

~~~cpp
// MyPresetManager::resetFactoryPreset()
void MyPresetManager::resetFactoryPreset()
{
    mArrayFactoryPreset.clear();

    mArrayFactoryPreset.add({ "Preset1", {111.0f, 111.0f}, 50.0f, 35.0f, -10.0f });
    mArrayFactoryPreset.add({ "Preset2", {222.0f, 222.0f}, 50.0f, 35.0f, -10.0f });
}
~~~

✅ This is executed once when the plugin starts.
The hardcoded presets are registered into memory.
These become the visible choices in the ComboBox.


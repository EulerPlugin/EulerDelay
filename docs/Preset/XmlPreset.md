## XML Preset System

<br>

### **📌 Introduction**

The XML Preset system allows users to **save and load parameter states 
as XML files.**
Unlike Factory Presets (which are hardcoded), 
XML Presets are **user-defined, persistent,** and editable outside the plugin.

<br>
<br>

### **⚙️ System Architecture**

**1. UI Hierarchy (Top-Down)**

~~~cpp
EulerDelayAudioProcessorEditor
└── mPanelDelay
    └── MyPresetComboBox
~~~

<br>

**2. Execution Flow (Bottom-Up**

~~~cpp
User selects "Save" or "Load" in ComboBox
  ↓
MyPresetComboBox → juce::FileChooser (asynchronous)
  ↓
MyPresetManager::saveXmlPreset() or loadXmlPreset()
  ↓
MyParameters ↔ juce::ValueTree ↔ APVTS
~~~

<br>
<br>

### **🔁 Runtime Flow**

**1. ComboBox triggers file dialog and action**

~~~cpp
// MyPresetComboBox::MyPresetComboBox()
onChange = [this]()
{
    const int id = getSelectedId();
    if (id == 0) return; // No valid selection

    // Create FileChooser instance
    mFileChooser = std::make_unique<juce::FileChooser>(
        id == IdComboBoxPreset::Save ? "Save Preset" : "Load Preset",
        mPresetManager.getDirPreset(),  // default path
        "*.xml",
        false
    );

    // Set file dialog flags
    int flag = juce::FileBrowserComponent::canSelectFiles;
    flag |= (id == IdComboBoxPreset::Save)
            ? juce::FileBrowserComponent::saveMode
            : juce::FileBrowserComponent::openMode;

    // Define async callback when file is selected
    auto callback = [this, id](const juce::FileChooser& chooser)
    {
        const juce::File file = chooser.getResult();
        if (!file.getFileName().isEmpty())
        {
            if (id == IdComboBoxPreset::Save)
                mPresetManager.saveXmlPreset(file.withFileExtension("xml")); // save
            else
                mPresetManager.loadXmlPreset(file); // load
        }

        resetByXmlPreset(); // Update display name in ComboBox
    };

    // Launch file dialog
    mFileChooser->launchAsync(flag, callback);
};
~~~

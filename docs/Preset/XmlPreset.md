## XML Preset System


###  Introduction

The XML Preset system allows users to **save and load parameter states 
as XML files.**
Unlike Factory Presets (which are hardcoded), 
XML Presets are **user-defined, persistent,** and editable outside the plugin.

<br>

###  System Architecture

**1. UI Hierarchy (Top-Down)**

~~~cpp
EulerDelayAudioProcessorEditor
└── mPanelControl
    └── MyPresetComboBox
~~~

<br>

**2. Execution Flow (Bottom-Up)**

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

-----

<br>

###  Runtime Flow

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

Selecting “Save” or “Load” triggers a file dialog.
Once the file is selected, the corresponding function (```saveXmlPreset``` or ```loadXmlPreset```) is executed.

<br>
<br>

**2. Saving current state to XML**

~~~cpp
// MyPresetManager::saveXmlPreset()
void MyPresetManager::saveXmlPreset(const juce::File& inFileXml) noexcept
{
    // Copy current APVTS state
    const juce::ValueTree stateCopied = mParameters.getStateCopied();

    // Convert to XML
    std::unique_ptr<juce::XmlElement> xml = stateCopied.createXml();

    // Validate and write
    if (!xml || !xml->writeTo(inFileXml) || inFileXml.create().failed())
        return;

    // Store preset name for display
    setXmlPresetCurrnet(inFileXml.getFileNameWithoutExtension());
}
~~~

 The plugin’s parameter state is copied as a ```ValueTree```, converted to XML, and written to disk.
The name is updated so the ComboBox reflects the most recent preset.


<br>
<br>

**3. Loading state from XML file**

~~~cpp
// MyPresetManager::loadXmlPreset()
void MyPresetManager::loadXmlPreset(const juce::File& inFileXml) noexcept
{
    // Parse XML file
    std::unique_ptr<juce::XmlElement> xml = juce::XmlDocument::parse(inFileXml);
    if (!xml) return;

    // Convert XML to ValueTree
    juce::ValueTree presetState = juce::ValueTree::fromXml(*xml);
    if (!presetState.isValid()) return;

    // Apply preset if valid
    if (mParameters.setParamsByValueTree(presetState))
        setXmlPresetCurrnet(inFileXml.getFileNameWithoutExtension());
}
~~~

 If the loaded XML is valid, it’s converted back to a ValueTree and replaces the current parameter state.

<br>

-----

<br>


###  Parameter ↔ State Helpers

~~~cpp
// MyParameters::getStateCopied()
juce::ValueTree MyParameters::getStateCopied() const noexcept
{
    return mApvts.copyState();  // Return snapshot of all parameters
}

// MyParameters::setParamsByValueTree()
bool MyParameters::setParamsByValueTree(const juce::ValueTree& inState) noexcept
{
    if (inState.getType() == mApvts.state.getType())
    {
        mApvts.replaceState(inState);  // Replace entire APVTS tree
        return true;
    }
    return false;
}
~~~

 These helper methods are the bridge between JUCE’s APVTS and your serialized preset format (XML).
They ensure structural integrity and type safety during import/export.

<br>

-----

<br>


###  Advantages of This Structure

**1. Persistent, user-defined presets**
- Users can save their own parameter configurations to .xml
- Useful for backup, sharing, or long-term recall

**2. Built entirely on JUCE-native structures**
- Uses ValueTree and XmlElement, no custom serialization
- Integrates smoothly with plugin state (getStateInformation / setStateInformation)

**3. Modular, maintainable architecture**
- File I/O is handled only inside MyPresetManager
- GUI (ComboBox) only triggers actions, not logic-heavy

**4. Easy to extend**
- Add preset folder browsing, recent files, overwrite warnings, or preset banks
- Easily adaptable to host save/load mechanisms

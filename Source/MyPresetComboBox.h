/*
  ==============================================================================

    MyPresetComboBox.h
    Created: 12 Mar 2025 10:54:07am
    Author:  sanghoonyou

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MyPresetManager.h"

//==============================================================================
/*
*/
class MyPresetComboBox  : public juce::ComboBox
{
public:
    MyPresetComboBox(MyPresetManager& inPresetManager);
    ~MyPresetComboBox() override;
    
private:
    MyPresetManager& mPresetManager;
    void resetByFactoryPreset() noexcept;
    
    std::unique_ptr<juce::FileChooser> mFileChooser;
    void resetByXmlPreset() noexcept;
    
    enum IdComboBoxPreset
    {
        Save=1,
        Load
    };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyPresetComboBox)
};

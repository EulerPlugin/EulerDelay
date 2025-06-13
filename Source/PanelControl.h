/*
  ==============================================================================

    PanelControl.h
    Created: 12 Mar 2025 10:42:28am
    Author:  sanghoonyou

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PanelBase.h"
#include "MyPresetComboBox.h"
#include "MyParamToggleButton.h"

//==============================================================================
/*
*/
class PanelControl  : public PanelBase
{
public:
    PanelControl(const juce::String& inTitle,
                 EulerDelayAudioProcessor& inAudioprocessor);
    ~PanelControl() override;

    void resized() override;
    
    juce::Button& getButtonTempo() noexcept;
    juce::Button& getButtonPingPong() noexcept;

private:
    juce::Label mLabelPreset;
    MyPresetComboBox mPresetComboBox;
    
    juce::Label mLabelTempo;
    MyParamToggleButton mButtonTempo;
    
    juce::Label mLabelLink;
    MyParamToggleButton mButtonLink;
    
    juce::Label mLabelPingPong;
    MyParamToggleButton mButtonPingPong;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PanelControl)
};

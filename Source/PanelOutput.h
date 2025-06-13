/*
  ==============================================================================

    PanelOutput.h
    Created: 25 Feb 2025 4:31:43pm
    Author:  sanghoonyou

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PanelBase.h"
#include "MyRotaryKnob.h"

//==============================================================================
/*
*/
class PanelOutput  : public PanelBase
{
public:
    PanelOutput(const juce::String& inTitle,
               EulerDelayAudioProcessor& inAudioprocessor);
    ~PanelOutput() override;

    void resized() override;

private:
    juce::Label mLabelMix;
    MyRotaryKnob mKnobMix;
    
    juce::Label mLabelGain;
    MyRotaryKnob mKnobGain;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PanelOutput)
};

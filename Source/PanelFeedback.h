/*
  ==============================================================================

    PanelFeedback.h
    Created: 6 Mar 2025 10:59:53am
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
class PanelFeedback  : public PanelBase
{
public:
    PanelFeedback(const juce::String& inTitle,
                  EulerDelayAudioProcessor& inAudioprocessor);
    ~PanelFeedback() override;

    void resized() override;

private:
    juce::Label mLabelAmount;
    MyRotaryKnob mKnobAmount;
    
    juce::Label mLabelLowCut;
    MyRotaryKnob mKnobLowCut;
    
    juce::Label mLabelHighCut;
    MyRotaryKnob mKnobHighCut;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PanelFeedback)
};

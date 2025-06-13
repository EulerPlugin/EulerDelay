/*
  ==============================================================================

    PanelPingPong.h
    Created: 23 May 2025 2:42:20pm
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
class PanelPingPong  : public PanelBase
{
public:
    PanelPingPong(const juce::String& inTitle,
                  EulerDelayAudioProcessor& inAudioprocessor);
    ~PanelPingPong() override;

    void resized() override;

private:
    juce::Label mLabelWidth;
    MyRotaryKnob mKnobWidth;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PanelPingPong)
};

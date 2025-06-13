/*
  ==============================================================================

    PanelDelay.h
    Created: 25 Feb 2025 4:27:04pm
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
class PanelDelay  : public PanelBase,
                    private juce::Button::Listener
{
public:
    PanelDelay(const juce::String& inTitle,
               EulerDelayAudioProcessor& inAudioprocessor,
               juce::Button& inButtonTempo,
               juce::Button& inButtonPingPong);
               
    ~PanelDelay() override;

    void resized() override;

private:
    juce::Label mLabelTime[2];
    MyRotaryKnob mKnobTime[2];
    
    juce::Label mLabelNote[2];
    MyRotaryKnob mKnobNote[2];
    
    juce::Button& mButtonTempo;
    juce::Button& mButtonPingPong;
    
    void buttonClicked(juce::Button* inButton) override;
    void setVisibleLaveAndKnobs(const bool inTempo, const bool inPingPong) noexcept;
    void setTextLabels(const bool inPingPong) noexcept;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PanelDelay)
};

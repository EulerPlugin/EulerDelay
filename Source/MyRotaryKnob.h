/*
  ==============================================================================

    MyRotaryKnob.h
    Created: 23 Feb 2025 5:35:50pm
    Author:  sanghoonyou

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class MyRotaryKnob  : public juce::Slider
{
    public:
        MyRotaryKnob(juce::AudioProcessorValueTreeState& inApvts,
                     const juce::String& inParamId,
                     const bool inDrawFromMiddle = false );
        ~MyRotaryKnob() override;

    private:
        // SliderAttatchment
        juce::AudioProcessorValueTreeState::SliderAttachment mAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyRotaryKnob)
};

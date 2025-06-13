/*
  ==============================================================================

    MyParamToggleButton.h
    Created: 7 Apr 2025 3:09:48pm
    Author:  sanghoonyou

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*

*/

class MyParamToggleButton  : public juce::TextButton
{
    public:
        MyParamToggleButton(juce::AudioProcessorValueTreeState& inApvts,
                            const juce::String& inParamId,
                            const int inCmdId);
                            
        ~MyParamToggleButton() override;

    private:
        juce::AudioProcessorValueTreeState::ButtonAttachment mAttatchment;
        void updateButtonText() noexcept;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyParamToggleButton)
};

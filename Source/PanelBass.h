/*
  ==============================================================================

    PanelBass.h
    Created: 23 Feb 2025 6:19:28pm
    Author:  sanghoonyou

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class PanelBass  : public juce::GroupComponent
{
    public:
        PanelBass(const juce::String& inTitle,
                  EulerDelayAudioProcessor& inAudioprocessor);
        ~PanelBass() override;
        
    protected:
        EulerDelayAudioProcessor& mAudioprocessor;

    private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PanelBass)
};

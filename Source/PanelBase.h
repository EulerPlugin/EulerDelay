/*
  ==============================================================================

    PanelBase.h
    Created: 23 Feb 2025 6:29:42pm
    Author:  sanghoonyou

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class PanelBase  : public juce::GroupComponent
{
    public:
        PanelBase(const juce::String& inTitle,
                  EulerDelayAudioProcessor& inAudioprocessor);
        ~PanelBase() override;
        
    protected:
        EulerDelayAudioProcessor& mAudioprocessor;
        
    private:
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PanelBase)
};
    

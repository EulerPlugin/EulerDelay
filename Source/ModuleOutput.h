/*
  ==============================================================================

    ModuleOutput.h
    Created: 10 Feb 2025 4:25:04pm
    Author:  sanghoonyou

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ModuleOutput
{
    public:
        ModuleOutput();
        ~ModuleOutput();
        
        float process(const float inSampleDry,const float inSampleWet,
                      const float inMix, const float inGain) const noexcept;
        
    private:
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModuleOutput)
};


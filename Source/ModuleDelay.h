/*
  ==============================================================================

    ModuleDelay.h
    Created: 10 Feb 2025 4:09:14pm
    Author:  sanghoonyou

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "MyDelay.h"

class ModuleDelay
{
    public:
        ModuleDelay();
        ~ModuleDelay();
        
        void prepare(const double inSampleRate) noexcept;
        void reset() noexcept;
        void process(const float inSampleL,const float inSampleR,
                     float& outSampleL, float& outSampleR,
                     const float inDelayL, const float inDelayR) noexcept;
        
    
    private:
        MyDelay mDelayL,mDelayR;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModuleDelay)
};

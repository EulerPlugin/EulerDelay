/*
  ==============================================================================

    ModulePingPong.h
    Created: 21 May 2025 11:44:13am
    Author:  sanghoonyou

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "MyPanning.h"

class ModulePingPong
{
    public:
        ModulePingPong();
        ~ModulePingPong();
        
        void process(const float inSampleL, const float inSampleR,
                     const float inFeedbackL, const float inFeedbackR,
                     float& outSampleL, float& outSampleR,
                     const bool inPingPong, const float inWidth) noexcept;
        
    private:
        MyPanning mPanning;
    
   JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModulePingPong)
};

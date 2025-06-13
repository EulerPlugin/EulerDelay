/*
  ==============================================================================

    ModuleFeedback.h
    Created: 5 Mar 2025 2:09:01pm
    Author:  sanghoonyou

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "MyFeedback.h"
#include "MyFilters.h"

class ModuleFeedback
{
    public:
        ModuleFeedback();
        ~ModuleFeedback();
        
        void prepare(const juce::dsp::ProcessSpec& inSpec) noexcept;
        void reeset() noexcept;
        
        void processPush(const float inSampleL,
                         const float inSampleR,
                         const float inFeedbackAmount,
                         const float inLowCut,
                         const float inHighCut) noexcept;
                         
        void processPop(float& outSampleL, float& outSampleR) const noexcept;
        
    private:
        MyFeedback mFeedbackL, mFeedbackR;
        MyFilters mFilter;
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModuleFeedback)
};

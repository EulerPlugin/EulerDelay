/*
  ==============================================================================

    MyFilters.h
    Created: 30 May 2025 8:35:34am
    Author:  sanghoonyou

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class MyFilters
{
    public:
        MyFilters();
        ~MyFilters();
        
        void prepare (const juce::dsp::ProcessSpec& inSpec) noexcept;
        
        void reset() noexcept;
        
        float processLowCut(const int inChannel,
                            const float inSample,
                            const float inCutoff) noexcept;
                     
        float processHighCut(const int inChannel,
                            const float inSample,
                            const float inCutoff) noexcept;
    private:
        juce::dsp::StateVariableTPTFilter<float> mFilterLowCut;
        juce::dsp::StateVariableTPTFilter<float> mFilterHighCut;
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyFilters)
};

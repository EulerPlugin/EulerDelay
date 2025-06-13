/*
  ==============================================================================

    MyPanning.h
    Created: 21 May 2025 11:25:20am
    Author:  sanghoonyou

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class MyPanning
{
    public:
        MyPanning();
        ~MyPanning();

        void process(const float inSampleL, const float inSampleR,
                     float& outSampleL, float& outSampleR,
                     const bool inPanning, const float inWidth) noexcept;
        
    private:
        static constexpr float kQuarterpi = juce::MathConstants<float>::halfPi * 0.5f;

        float mWidth;
        float mPanL;
        float mPanR;
        
        void updatePanning(const float inWidth) noexcept;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyPanning)
};

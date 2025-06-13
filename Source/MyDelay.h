/*
  ==============================================================================

    MyDelay.h
    Created: 4 Feb 2025 1:01:41pm
    Author:  sanghoonyou

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class MyDelay
{
    public:
        MyDelay();
        ~MyDelay();
        
        void prepare(const double inSampleRate) noexcept;
        void reset() noexcept;
        float process(const float inSample,const float inDelay) noexcept;
        
    private:
        juce::Array<float> mBuffer;
        int mSizeBuffer;
        int mIndexWriting;
        
        float popSample(const float inDelay) const noexcept;
        float getSampleByLerp(const float inIndexReading) const noexcept;
        float getSampleByHermit(const float inIndexReading) const noexcept;
        
JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyDelay)
};

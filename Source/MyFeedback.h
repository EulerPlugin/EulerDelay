/*
  ==============================================================================

    MyFeedback.h
    Created: 5 Mar 2025 12:56:41pm
    Author:  sanghoonyou

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
class MyFeedback
{
    public:
        MyFeedback();
        ~MyFeedback();
        
        void prepare() noexcept;
        void reset() noexcept;
        
        void pushSample(const float inSample, const float inAmount = 1.0f) noexcept;
        float popSample()const noexcept;
        
    private:
        float mSampleFeedback;
    
    
JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyFeedback)
};

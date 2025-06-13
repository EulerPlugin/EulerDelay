/*
  ==============================================================================

    MySmoother.h
    Created: 4 Feb 2025 2:36:01pm
    Author:  sanghoonyou

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class MySmoother
{
    public:
        MySmoother();
        ~MySmoother();
        
        void reset(const double inRateGz,const double inTimeSec) noexcept;
        void smoothen() noexcept;
        
        void setTarget(const double inValue) noexcept;
        void setCurrent(const double inValue) noexcept;
        
        double getTarget() const noexcept;
        double getCurrent() const noexcept;
    
    private:
        double mCoefficient;
        double mTarget;
        double mCurrent;
        
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MySmoother)
};


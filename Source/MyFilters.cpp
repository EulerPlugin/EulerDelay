/*
  ==============================================================================

    MyFilters.cpp
    Created: 30 May 2025 8:35:34am
    Author:  sanghoonyou

  ==============================================================================
*/

#include "MyFilters.h"

MyFilters::MyFilters()
{
    mFilterLowCut.setType(juce::dsp::StateVariableTPTFilterType::highpass);
    mFilterHighCut.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
}

MyFilters::~MyFilters()
{
    
}

void MyFilters::prepare(const juce::dsp::ProcessSpec& inSpec) noexcept
{
    mFilterLowCut.prepare(inSpec);
    mFilterHighCut.prepare(inSpec);
}

void MyFilters::reset() noexcept
{
    mFilterLowCut.reset();
    mFilterHighCut.reset();
}

float MyFilters::processLowCut(const int inChannel,
                         const float inSample,
                         const float inCutoff) noexcept
{
    mFilterLowCut.setCutoffFrequency(inCutoff);
    return mFilterLowCut.processSample(inChannel, inSample);
}

float MyFilters::processHighCut(const int inChannel,
                               const float inSample,
                               const float inCutoff) noexcept
{
    if (inCutoff != mFilterHighCut.getCutoffFrequency())
    {
        mFilterHighCut.setCutoffFrequency(inCutoff);
    }
    return mFilterHighCut.processSample(inChannel, inSample);
}

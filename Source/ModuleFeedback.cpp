/*
  ==============================================================================

    ModuleFeedback.cpp
    Created: 5 Mar 2025 2:09:01pm
    Author:  sanghoonyou

  ==============================================================================
*/

#include "ModuleFeedback.h"

ModuleFeedback::ModuleFeedback()
{

}

ModuleFeedback::~ModuleFeedback()
{

}

void ModuleFeedback::prepare(const juce::dsp::ProcessSpec& inSpec) noexcept
{
    mFeedbackL.prepare();
    mFeedbackR.prepare();
    
    mFilter.prepare(inSpec);
}

void ModuleFeedback::reeset() noexcept
{
    mFeedbackL.reset();
    mFeedbackR.reset();
    
    mFilter.reset();
}

void ModuleFeedback::processPush(const float inSampleL,
                                 const float inSampleR,
                                 const float inFeedbackAmount,
                                 const float inLowCut,
                                 const float inHighCut) noexcept
{
    const float outfeedbackL = inSampleL * inFeedbackAmount;
    const float outfeedbackR = inSampleR * inFeedbackAmount;

    const float outLowCutL = mFilter.processLowCut(0, outfeedbackL, inLowCut);
    const float outLowCutR = mFilter.processLowCut(1, outfeedbackR, inLowCut);
    
    const float outHighCutL = mFilter.processHighCut(0, outLowCutL, inHighCut);
    const float outHighCutR = mFilter.processHighCut(1, outLowCutR, inHighCut);
    
    mFeedbackL.pushSample(outHighCutL);
    mFeedbackR.pushSample(outHighCutR);
}
                 
void ModuleFeedback::processPop(float& outSampleL, float& outSampleR) const noexcept
{
   outSampleL = mFeedbackL.popSample();
   outSampleR = mFeedbackR.popSample();
   
}

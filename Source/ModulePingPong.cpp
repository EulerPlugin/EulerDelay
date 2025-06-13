/*
  ==============================================================================

    ModulePingPong.cpp
    Created: 21 May 2025 11:44:13am
    Author:  sanghoonyou

  ==============================================================================
*/

#include "ModulePingPong.h"

ModulePingPong::ModulePingPong()
{

}

ModulePingPong::~ModulePingPong()
{

}

void ModulePingPong::process(const float inSampleL, const float inSampleR,
                             const float inFeedbackL, const float inFeedbackR,
                             float& outSampleL, float& outSampleR,
                             const bool inPingPong, const float inWidth) noexcept
 {
    float outPanL = 0.0f;
    float outPanR = 0.0f;
    
    mPanning.process(inSampleL, inSampleR, outPanL, outPanR, inPingPong, inWidth);
    
    outSampleL = inPingPong ? (outPanL + inFeedbackR) : (outPanL + inFeedbackL);
    outSampleR = inPingPong ? (outPanR + inFeedbackL) : (outPanR + inFeedbackR);
 }

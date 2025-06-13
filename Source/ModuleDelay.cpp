/*
  ==============================================================================

    ModuleDelay.cpp
    Created: 10 Feb 2025 4:09:14pm
    Author:  sanghoonyou

  ==============================================================================
*/

#include "ModuleDelay.h"


ModuleDelay::ModuleDelay()
{

}
ModuleDelay::~ModuleDelay()
{

}

void ModuleDelay::prepare(const double inSampleRate) noexcept
{
    mDelayL.prepare(inSampleRate);
    mDelayR.prepare(inSampleRate);
}

void ModuleDelay::reset() noexcept
{
    mDelayL.reset();
    mDelayR.reset();
}

void ModuleDelay::process(const float inSampleL,const float inSampleR,
                          float& outSampleL, float& outSampleR,
                          const float inDelayL, const float inDelayR) noexcept
{
    outSampleL = mDelayL.process(inSampleL, inDelayL);
    outSampleR = mDelayR.process(inSampleR, inDelayR);
}

    

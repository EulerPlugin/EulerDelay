/*
  ==============================================================================

    ModuleOutput.cpp
    Created: 10 Feb 2025 4:25:04pm
    Author:  sanghoonyou

  ==============================================================================
*/

#include "ModuleOutput.h"


ModuleOutput::ModuleOutput()
{

}
ModuleOutput::~ModuleOutput()
{

}

float ModuleOutput::process(const float inSampleDry,const float inSampleWet,
                            const float inMix, const float inGain) const noexcept
{
    //Mix
    
    const float outMix = inSampleDry + (inSampleWet * inMix);
    
    return outMix * inGain;
}

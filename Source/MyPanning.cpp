/*
  ==============================================================================

    MyPanning.cpp
    Created: 21 May 2025 11:25:20am
    Author:  sanghoonyou

  ==============================================================================
*/

#include "MyPanning.h"
MyPanning::MyPanning()
:mWidth(0.0f),
mPanL(std::cos(kQuarterpi)),
mPanR(std::sin(kQuarterpi))
{
    
}

MyPanning::~MyPanning()
{

}

void MyPanning::process(const float inSampleL, const float inSampleR,
                        float& outSampleL, float& outSampleR,
                        const bool inPanning, const float inWidth) noexcept
{
    if (inPanning == true)
    {
        updatePanning(inWidth);
        
        const float mono = ( inSampleL + inSampleR ) * 0.5f;
        
        outSampleL = mono * mPanL;
        outSampleR = mono * mPanR;
    }
    else
    {
        outSampleL = inSampleL;
        outSampleR = inSampleR;
    }
}
                     
void MyPanning::updatePanning(const float inWidth) noexcept
{
    if (inWidth == mWidth)
    {
        return;
    }
    
    mWidth = inWidth;
    const float x = kQuarterpi * ( inWidth + 1 );
    mPanL = std::cos(x);
    mPanR = std::sin(x);
    
}

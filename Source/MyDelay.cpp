/*
  ==============================================================================

    MyDelay.cpp
    Created: 4 Feb 2025 1:01:41pm
    Author:  sanghoonyou

  ==============================================================================
*/

#include "MyDelay.h"
#include "MyParameters.h"
MyDelay::MyDelay()
:mIndexWriting(0)
{
    
}
MyDelay::~MyDelay()
{
    
}

void MyDelay::prepare(const double inSampleRate) noexcept
{
    mBuffer.clear();
    
    const double maxDelayTimeSec = MyParameters::kTimeMax * 0.001f;
    mSizeBuffer = inSampleRate * maxDelayTimeSec + 1 ;
    mBuffer.resize(mSizeBuffer);
    
    reset();
}

void MyDelay::reset() noexcept
{
    mBuffer.fill(0.0f);
}

float MyDelay::process(const float inSample,const float inDelay) noexcept
{
    //write,push
    mBuffer.set(mIndexWriting,inSample);
    
    //read,pop
    const float sampleDelayed = popSample(inDelay);
    
    mIndexWriting++;
    
    if(mIndexWriting > mSizeBuffer)
    {
        mIndexWriting = 0;
    }
    
    return sampleDelayed;
}

float MyDelay::popSample(const float inDelay) const noexcept
{
    float indexReading = mIndexWriting - inDelay;
    
    
    if(indexReading < 0.0f)
    {
        indexReading += (float)mSizeBuffer;
    }
                    
    //return mBuffer[(int)indexReading];    //소수점 인덱스 날리는 방식
    //return getSampleByLerp(indexReading);   //리니어 인터폴레이션
    return getSampleByHermit(indexReading); //허미트 인터폴레이션
}


float MyDelay::getSampleByLerp(const float inIndexReading) const noexcept
{
    const int iA = (int)inIndexReading;
    
    const float fraction = inIndexReading - (float)iA;
    
    int iB = iA + 1;
    
    if(iB > mSizeBuffer)
    {
        iB = 0;
    }
    //return (1.0f - fraction) * mBuffer[iA]  + (fraction * mBuffer[iB]);
    return mBuffer[iA] + (fraction * (mBuffer[iB]- mBuffer[iA]));
}

float MyDelay::getSampleByHermit(const float inIndexReading) const noexcept
{
        const int iB = (int)inIndexReading;
        
        int iA = iB + 1;
        if (iA >= mSizeBuffer)
        {
            iA = 0;
        }
        
        int iC = iB - 1;
        int iD = iC - 1;
        
        if (iD < 0)
        {
            iD += mSizeBuffer;
            if (iC < 0)
            {
                iC += mSizeBuffer;
            }
        }
        
        const float fraction = inIndexReading - (float)iB;
        const float slope0 = (mBuffer[iC] - mBuffer[iA]) * 0.5f;
        const float slope1 = (mBuffer[iD] - mBuffer[iB]) * 0.5f;
        const float v = mBuffer[iB] - mBuffer[iC];
        const float w = slope0 + v;
        const float a = w + v + slope1;
        const float b = w + a;
        const float stage1 = (a * fraction) - b;
        const float stage2 = (stage1 * fraction) + slope0;
        
        return ((stage2 * fraction) + mBuffer[iB]);
}

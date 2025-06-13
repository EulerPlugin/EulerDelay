/*
  ==============================================================================

    MyFeedback.cpp
    Created: 5 Mar 2025 12:56:41pm
    Author:  sanghoonyou

  ==============================================================================
*/

#include "MyFeedback.h"

MyFeedback::MyFeedback()
{

}

MyFeedback::~MyFeedback()
{

}

void MyFeedback::prepare() noexcept
{
    reset();
}

void MyFeedback::reset() noexcept
{
    mSampleFeedback = 0.0f;
}

void MyFeedback::pushSample(const float inSample, const float inAmount) noexcept
{
    mSampleFeedback = (inSample * inAmount);
}

float MyFeedback::popSample()const noexcept
{
    return mSampleFeedback;
}

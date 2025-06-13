/*
  ==============================================================================

    MySmoother.cpp
    Created: 4 Feb 2025 2:36:01pm
    Author:  sanghoonyou

  ==============================================================================
*/

#include "MySmoother.h"


MySmoother::MySmoother()
:mCoefficient(0.0),mTarget(0.0),mCurrent(0.0)
{

}

MySmoother::~MySmoother()
{

}

void MySmoother::reset(const double inRateGz,const double inTimeSec) noexcept
{
    mCoefficient = 1.0 - std::exp(-1.0 / (inTimeSec * inRateGz));
}
void MySmoother::smoothen() noexcept
{
    mCurrent += (mTarget - mCurrent) * mCoefficient;
}

void MySmoother::setTarget(const double inValue) noexcept
{
    mTarget = inValue;
}
void MySmoother::setCurrent(const double inValue) noexcept
{
    mCurrent = inValue;
}

double MySmoother::getTarget() const noexcept
{
    return mTarget;
}
double MySmoother::getCurrent() const noexcept
{
    return mCurrent;
}

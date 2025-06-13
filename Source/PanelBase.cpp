/*
  ==============================================================================

    PanelBase.cpp
    Created: 23 Feb 2025 6:29:42pm
    Author:  sanghoonyou

  ==============================================================================
*/
#include <JuceHeader.h>
#include "PanelBase.h"

//==============================================================================
PanelBase::PanelBase(const juce::String& inTitle, EulerDelayAudioProcessor& inAudioprocessor)
: //Bass Class
    juce::GroupComponent(inTitle,inTitle),
    mAudioprocessor(inAudioprocessor)
{
    //그룹 컴포넌트의 타이틀이 상단 정중앙에 위치하도록 설정
    setTextLabelPosition(juce::Justification::horizontallyCentred);
}

PanelBase::~PanelBase()
{
}

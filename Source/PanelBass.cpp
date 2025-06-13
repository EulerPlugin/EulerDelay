/*
  ==============================================================================

    PanelBass.cpp
    Created: 23 Feb 2025 6:19:28pm
    Author:  sanghoonyou

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PanelBass.h"

//==============================================================================
PanelBass::PanelBass(const juce::String& inTitle,
                     EulerDelayAudioProcessor& inAudioprocessor)
:juce::GroupComponent(inTitle,inTitle),
 mAudioprocessor(inAudioprocessor)
{
    //그룹 컴포넌트의 타이틀이 상단 중앙에 위치하도록 설정
    setTextLabelPosition(juce::Justification::horizontallyCentred);
}

PanelBass::~PanelBass()
{


}



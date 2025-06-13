/*
  ==============================================================================

    MyParamToggleButton.cpp
    Created: 7 Apr 2025 3:09:48pm
    Author:  sanghoonyou

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MyParamToggleButton.h"

//==============================================================================
MyParamToggleButton::MyParamToggleButton(juce::AudioProcessorValueTreeState& inApvts,
                                         const juce::String& inParamId,
                                         const int inCmdId)
:mAttatchment(inApvts, inParamId, *this)
{
    setClickingTogglesState(true);  // 토글 기능 활성화
    
    updateButtonText();
    
    setCommandToTrigger(nullptr, inCmdId, false);
    
    onClick = [this]()
    {
        updateButtonText();
        
        //랜덤 넘버 슛
    };
    
}

MyParamToggleButton::~MyParamToggleButton()
{

}

void MyParamToggleButton::updateButtonText() noexcept
{
    setButtonText(getToggleState() ? "ON" : "OFF");
}

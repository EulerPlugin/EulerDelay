/*
  ==============================================================================

    PanelPingPong.cpp
    Created: 23 May 2025 2:42:20pm
    Author:  sanghoonyou

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PanelPingPong.h"
#include "MySize.h"

//==============================================================================
PanelPingPong::PanelPingPong(const juce::String& inTitle,
                             EulerDelayAudioProcessor& inAudioprocessor)
://Base Class
 PanelBase(inTitle, inAudioprocessor),
 // RotaryKnob
 mKnobWidth(mAudioprocessor.getmApvts(),
            MyParamId::PingPong::Width.getParamID(),
            true)
{
    mLabelWidth.setText("Width", juce::NotificationType::dontSendNotification);
    mLabelWidth.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(mLabelWidth);
    addAndMakeVisible(mKnobWidth);
}

PanelPingPong::~PanelPingPong()
{

}


void PanelPingPong::resized()
{
    // Size
    mLabelWidth.setSize(MySize::RotaryKnob::Width, MySize::Label::Height);
    mKnobWidth.setSize(MySize::RotaryKnob::Width, MySize::RotaryKnob::Height);
    
    // Position
    const juce::Rectangle<int> boundlocal = getLocalBounds();
    
    const int xLabelWidth = boundlocal.getX() + MySize::Padding::Width;
    const int yLabelWidth = boundlocal.getY() + MySize::Padding::Top::Height;
    
    mLabelWidth.setTopLeftPosition(xLabelWidth, yLabelWidth);
    mKnobWidth.setTopLeftPosition(mLabelWidth.getX(), mLabelWidth.getBottom());
}

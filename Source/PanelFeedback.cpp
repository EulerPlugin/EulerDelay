/*
  ==============================================================================

    PanelFeedback.cpp
    Created: 6 Mar 2025 10:59:53am
    Author:  sanghoonyou

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PanelFeedback.h"
#include "MySize.h"

//==============================================================================
PanelFeedback::PanelFeedback(const juce::String& inTitle,
                             EulerDelayAudioProcessor& inAudioprocessor)
:PanelBase(inTitle, inAudioprocessor),
 mKnobAmount(mAudioprocessor.getmApvts(),MyParamId::FeedBack::Amount.getParamID(),true),
 mKnobLowCut(mAudioprocessor.getmApvts(), MyParamId::FeedBack::LowCut.getParamID()),
 mKnobHighCut(mAudioprocessor.getmApvts(), MyParamId::FeedBack::HighCut.getParamID())
{
    mLabelAmount.setText("Amount", juce::NotificationType::dontSendNotification);
    mLabelAmount.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(mLabelAmount);
    addAndMakeVisible(mKnobAmount);
    
    mLabelLowCut.setText("LowCut", juce::NotificationType::dontSendNotification);
    mLabelLowCut.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(mLabelLowCut);
    addAndMakeVisible(mKnobLowCut);
    
    mLabelHighCut.setText("HighCut", juce::NotificationType::dontSendNotification);
    mLabelHighCut.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(mLabelHighCut);
    addAndMakeVisible(mKnobHighCut);
}

PanelFeedback::~PanelFeedback()
{

}


void PanelFeedback::resized()
{
    //Size
    mLabelAmount.setSize(MySize::RotaryKnob::Width, MySize::Label::Height);
    mKnobAmount.setSize(MySize::RotaryKnob::Width, MySize::RotaryKnob::Height);
    
    mLabelLowCut.setSize(MySize::RotaryKnob::Width, MySize::Label::Height);
    mKnobLowCut.setSize(MySize::RotaryKnob::Width, MySize::RotaryKnob::Height);
    
    mLabelHighCut.setSize(MySize::RotaryKnob::Width, MySize::Label::Height);
    mKnobHighCut.setSize(MySize::RotaryKnob::Width, MySize::RotaryKnob::Height);
    
    //Location
    juce::Rectangle<int>  boundlocal = getLocalBounds();
    
    const int xLabelAmount = boundlocal.getX() + MySize::Padding::Width;
    const int yLabelAmount = boundlocal.getY() + MySize::Padding::Top::Height;
    mLabelAmount.setTopLeftPosition(xLabelAmount, yLabelAmount);
    mKnobAmount.setTopLeftPosition(mLabelAmount.getX(), mLabelAmount.getBottom());
    
    const int xLabelLowCut = mLabelAmount.getRight() + MySize::Padding::Width;
    mLabelLowCut.setTopLeftPosition(xLabelLowCut, mLabelAmount.getY());
    mKnobLowCut.setTopLeftPosition(mLabelLowCut.getX(), mLabelLowCut.getBottom());
    
    const int xLabelHighCut = mLabelLowCut.getRight() + MySize::Padding::Width;
    mLabelHighCut.setTopLeftPosition(xLabelHighCut, mLabelLowCut.getY());
    mKnobHighCut.setTopLeftPosition(mLabelHighCut.getX(), mLabelHighCut.getBottom());
    
}

/*
  ==============================================================================

    PanelDelay.cpp
    Created: 25 Feb 2025 4:27:04pm
    Author:  sanghoonyou

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PanelDelay.h"
#include "MySize.h"
#include "MyHelper.h"

//==============================================================================
PanelDelay::PanelDelay(const juce::String& inTitle,
                       EulerDelayAudioProcessor& inAudioprocessor,
                       juce::Button& inButtonTempo,
                       juce::Button& inButtonPingPong)
://base class
 PanelBase(inTitle, inAudioprocessor),
 
 mKnobTime{ { mAudioprocessor.getmApvts(),MyParamId::Delay::Time[0].getParamID()},
            { mAudioprocessor.getmApvts(),MyParamId::Delay::Time[1].getParamID()}},
            
 mKnobNote{ { mAudioprocessor.getmApvts(),MyParamId::Delay::Note[0].getParamID()},
            { mAudioprocessor.getmApvts(),MyParamId::Delay::Note[1].getParamID()}},
            
 mButtonTempo(inButtonTempo),
 
 mButtonPingPong(inButtonPingPong)
{
    setTextLabels(inButtonPingPong.getToggleState());
    mLabelTime[1].setText("Time R", juce::NotificationType::dontSendNotification);
    mLabelNote[1].setText("Note R", juce::NotificationType::dontSendNotification);
    
    for(int i=0;i<2;++i)
    {
//      const juce::String labelTime = (i==0) ? "TimeL" : "TimeR" ;
//      mLabelTime[i].setText(labelTime, juce::NotificationType::dontSendNotification);
        mLabelTime[i].setJustificationType(juce::Justification::centred);
        addChildComponent(mLabelTime[i]);
        addChildComponent(mKnobTime[i]);
        
//      const juce::String labelNote = (i==0) ? "Note L" : "Note R";
//      mLabelNote[i].setText(labelNote, juce::NotificationType::dontSendNotification);
        mLabelNote[i].setJustificationType(juce::Justification::centred);
        addChildComponent(mLabelNote[i]);
        addChildComponent(mKnobNote[i]);
    }
    
    mButtonTempo.addListener(this);
    mButtonPingPong.addListener(this);
    
    setVisibleLaveAndKnobs(mButtonTempo.getToggleState(), mButtonPingPong.getToggleState());
}

PanelDelay::~PanelDelay()
{
    mButtonTempo.removeListener(this);
    mButtonPingPong.removeListener(this);
}

void PanelDelay::resized()
{
    for(int i=0;i<2;++i)
    {
        mLabelTime[i].setSize(MySize::RotaryKnob::Width, MySize::Label::Height);
        mKnobTime[i].setSize(MySize::RotaryKnob::Width, MySize::RotaryKnob::Height);
        
        mLabelNote[i].setSize(MySize::RotaryKnob::Width, MySize::Label::Height);
        mKnobNote[i].setSize(MySize::RotaryKnob::Width, MySize::RotaryKnob::Height);
    }
    
    const juce::Rectangle<int> boundlocal = this->getLocalBounds();
    
    for(int i=0;i<2;++i)
    {
        const int xLabelTime =  boundlocal.getX() + MySize::Padding::Width;
        const int yLabelTime =  (i==0) ?  boundlocal.getY() + MySize::Padding::Top::Height
                                 : mKnobTime[0].getBottom() + MySize::Padding::Mid::Height;
        
        mLabelTime[i].setTopLeftPosition(xLabelTime, yLabelTime);
        mKnobTime[i].setTopLeftPosition(mLabelTime[i].getX(), mLabelTime[i].getBottom());
        
        mLabelNote[i].setTopLeftPosition(mLabelTime[i].getPosition());
        mKnobNote[i].setTopLeftPosition(mKnobTime[i].getPosition());
    }
    
}

void PanelDelay::buttonClicked(juce::Button* inButton)
{
    //DBG(inButton->getCommandID());
    switch(inButton->getCommandID())
    {
        case MyHelper::CmdIdButtons::Tempo:
        {
            setVisibleLaveAndKnobs(inButton->getToggleState(), mButtonPingPong.getToggleState());
            break;
        }
        case MyHelper::CmdIdButtons::PingPong:
        {
            setTextLabels(inButton -> getToggleState());
            setVisibleLaveAndKnobs(mButtonTempo.getToggleState(), inButton -> getToggleState());
            break;
        }
        default: break;
    }
}

void PanelDelay::setVisibleLaveAndKnobs(const bool inTempo, const bool inPingPong) noexcept
{
            for(int i=0;i<2 ; ++i)
            {
                mLabelTime[i].setVisible(i == 0 ? !inTempo : !inTempo && !inPingPong);
                mKnobTime[i].setVisible(i == 0 ? !inTempo : !inTempo && !inPingPong);
                
                mLabelNote[i].setVisible(i == 0 ? inTempo : inTempo && !inPingPong);
                mKnobNote[i].setVisible(i == 0 ? inTempo : inTempo && !inPingPong);
            }
}


void PanelDelay::setTextLabels(const bool inPingPong) noexcept
{
    mLabelTime[0].setText(inPingPong ? "Time" : "Time L", juce::NotificationType::dontSendNotification);
    mLabelNote[0].setText(inPingPong ? "Note" : "Note L", juce::NotificationType::dontSendNotification);
}

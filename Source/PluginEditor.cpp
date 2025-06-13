/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "MySize.h"
#include "MyHelper.h"

//Component (요소)
//Parent - Chile : Child는 Parent에 속한다

//==============================================================================
EulerDelayAudioProcessorEditor::EulerDelayAudioProcessorEditor (EulerDelayAudioProcessor& p)
: AudioProcessorEditor (&p), // base class 여기서 &p는 레퍼런스가 아니고 주소이다
  audioProcessor (p),        // 멤버 초기화
  
  //Panels
  mPanelControl("Control", audioProcessor),
  mPanelDelay("Delay", audioProcessor,
  mPanelControl.getButtonTempo(),
  mPanelControl.getButtonPingPong()),
  mPanelFeedback("FeedBack", audioProcessor),
  mPanelOutput("Output", audioProcessor),
  mPanelPingPong("PingPong", audioProcessor),
  
  //PingPong
  mButtonPingPong(mPanelControl.getButtonPingPong())
{
    setSize (MySize::GUI::Width, MySize::GUI::Height);
    
    addAndMakeVisible(mPanelControl);
    addAndMakeVisible(mPanelDelay);
    addAndMakeVisible(mPanelFeedback);
    addAndMakeVisible(mPanelOutput);
    addChildComponent(mPanelPingPong);
    mPanelPingPong.setVisible(mButtonPingPong.getToggleState());
    
    setLookAndFeel(&mLookAndFeel);
    
    mButtonPingPong.addListener(this);
}

EulerDelayAudioProcessorEditor::~EulerDelayAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
    mButtonPingPong.removeListener(this);
}

//==============================================================================
void EulerDelayAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    //g.setColour (juce::Colours::white);
    //g.setFont (juce::FontOptions (15.0f));
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void EulerDelayAudioProcessorEditor::resized()
{
    //사이즈
    mPanelControl.setSize(MySize::Panel::Control::Width, MySize::Panel::Control::Height);
    mPanelDelay.setSize(MySize::Panel::Delay::Width,
                        mButtonPingPong.getToggleState() ?  MySize::Panel::Delay::Height / 2:
                                                            MySize::Panel::Delay::Height );
    mPanelFeedback.setSize(MySize::Panel::Feedback::Width, MySize::Panel::Feedback::Height);
    mPanelOutput.setSize(MySize::Panel::Output::Width, MySize::Panel::Output::Height);
    mPanelPingPong.setSize(MySize::Panel::PingPong::Width, MySize::Panel::PingPong::Height);
    
    //위치
    mPanelControl.setTopLeftPosition(0, MySize::GUI::Header::Height);
    mPanelDelay.setTopLeftPosition(mPanelControl.getRight(),mPanelControl.getY() );
    mPanelFeedback.setTopLeftPosition(mPanelDelay.getRight(), MySize::GUI::Header::Height);
    mPanelOutput.setTopLeftPosition(mPanelFeedback.getRight(), MySize::GUI::Header::Height);
    //const int yPanelPingPong = mPanelDelay.getY() + mPanelDelay.getHeight() / 2 ;
    mPanelPingPong.setTopLeftPosition(mPanelDelay.getX(), mPanelDelay.getBottom());
}


void EulerDelayAudioProcessorEditor::buttonClicked(juce::Button* inButton)
{
    switch (inButton -> getCommandID())
    {
        case MyHelper::CmdIdButtons::PingPong:
        {
            mPanelDelay.setSize(MySize::Panel::Delay::Width,
                                inButton -> getToggleState() ?  MySize::Panel::Delay::Height / 2:
                                                                MySize::Panel::Delay::Height );
            resized();
            
            mPanelPingPong.setVisible(mButtonPingPong.getToggleState());
            break;
        }
        
        default: break;
    }
}

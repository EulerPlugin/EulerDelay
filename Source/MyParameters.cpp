/*
  ==============================================================================

    MyParameters.cpp
    Created: 18 Jan 2025 2:33:05pm
    Author:  sanghoonyou

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MyParameters.h"

//==============================================================================
template <typename T>
static void castParameter(juce::AudioProcessorValueTreeState& inApvts,
                          const juce::ParameterID& inParamId,T& inDestination)
{
    inDestination = dynamic_cast<T>(inApvts.getParameter(inParamId.getParamID()));
    jassert(inDestination);
}

static juce::String stringFromDecibels(float inValue,int)
{
    return juce::String(inValue,1) + "dB";
}

static juce::String stringFromMilliseconds(float inValue,int)
{
    if(inValue<1000.0f)
    {
        return juce::String(inValue,1) + "ms";

    }
    else
    {
        return juce::String(inValue * 0.001 , 4) + "s";
    }
}

static float milliSecondsFromString(const juce::String& inText)
{
    const float value = inText.getFloatValue();
    if(inText.endsWithIgnoreCase("ms") == false) //ms로 끝내지 않았을 경우, ignorecase는 대소문자 구분 없이
    {
        if(value < MyParameters::kTimeMin || inText.endsWithIgnoreCase("s"))
        {
            //5보다 낮은 걸로 했을 경우나
            //뒤에 's'를 붙였거나
            return value * 1000.0f;
        }
    }
    return value;
}

static juce::String stringFromPercent(float inValue,int)
{
    return juce::String((int)inValue) + "%";
}

static juce::String stringFromHz(float inHz, int)
{
    return juce::String(inHz) + "Hz";
}

static float hzFromString(const juce::String& inText)
{
    const float Hz = inText.getFloatValue();
    if (Hz < 20)
    {
        return Hz * 1000.0f;
    }
    else
    {
        return Hz;
    }
}

MyParameters::MyParameters(juce::AudioProcessorValueTreeState& inApvts)
:mApvts(inApvts),
 mChannelMaster(0),
 mFlagLinking(false)
{
    castParameter(mApvts, MyParamId::Output::Gain, mParamGain);
    
    castParameter(mApvts, MyParamId::Test, mParamTest);

    for(int i=0;i<2;++i)
    {
        castParameter(mApvts, MyParamId::Delay::Time[i], mParamTime[i]);
    }
    
    castParameter(mApvts, MyParamId::Output::Mix, mParamMix);
    
    castParameter(mApvts, MyParamId::FeedBack::Amount, mParamAmount);
    
    castParameter(mApvts, MyParamId::Control::Tempo, mParamTemopo);
    
    for(int i=0 ; i<2; ++i)
    {
        castParameter(mApvts, MyParamId::Delay::Note[i], mParamNote[i]);
    }
    
    castParameter(mApvts, MyParamId::Control::Link.getParamID(), mParamLink);
    
    mApvts.addParameterListener(MyParamId::Control::Link.getParamID(), this);
    
    //PingPong
    castParameter(mApvts, MyParamId::PingPong::Width, mParamWidth);
    castParameter(mApvts, MyParamId::Control::PingPong, mParamPingPong);
    
    // LowCut
    castParameter(mApvts, MyParamId::FeedBack::LowCut, mParamLowCut);
    
    //HighCut
    castParameter(mApvts, MyParamId::FeedBack::HighCut, mParamHighCut);
}

MyParameters::~MyParameters()
{
    mApvts.removeParameterListener(MyParamId::Control::Link.getParamID(), this);
}

const float MyParameters::kTimeMin2 = 2.0f;

float MyParameters::getValueGain() const noexcept
{
    return mValueGain.getCurrentValue();
}

float MyParameters::getValueTest() const noexcept
{
    return (float)mValueTest.getCurrent();
}

float MyParameters::getValueTime(const int inChannel) const noexcept
{
    return (float)mValueTime[inChannel].getCurrent();
}

float MyParameters::getValueMix() const noexcept
{
    return mValueMix.getCurrentValue();
}

float MyParameters::getValueAmount() const noexcept
{
    return mValueAmount.getCurrentValue();
}

float MyParameters::getValueWidth() const noexcept
{
    return mValueWidth.getCurrentValue();
}

bool MyParameters::getValuePingPong() const noexcept
{
    return mValuePingPong;
}

float MyParameters::getValueLowCut() const noexcept
{
    return mValueLowCut.getCurrentValue();
}

float MyParameters::getValueHighCut() const noexcept
{
    return mValueHighCut.getCurrentValue();
}

void MyParameters::setParamsByFactoryPreset(const FactoryPreset& inPreset) noexcept
{
    for(int i=0;i<2;++i)
    {
        *mParamTime[i] = inPreset.mTime[i];
    }
    *mParamAmount = inPreset.mFeedback;
    *mParamMix =  inPreset.mMix;
    *mParamGain = inPreset.mGain;
}

bool MyParameters::setParamsByValueTree(const juce::ValueTree& inState) noexcept
{
    if(inState.getType() == mApvts.state.getType())
    {
        mApvts.replaceState(inState);
        return true;
    }
    return false;
}

double MyParameters::getTimeByNote(const double inBpm,const int inNote) const noexcept
{
    static constexpr double scalars[] = { 0.25 * 2.0 / 3.0,  // SixteenthTriplet,
                                          0.125 * 1.5,       // ThirtySecondDotted,
                                          0.25,              // Sixteenth,
                                          0.5 * 2.0 / 3.0,   // EighthTriplet
                                          0.25 * 1.5,        // SixteenthDotted,
                                          0.5,               // Eighth,
                                          1.0 * 2.0 / 3.0,   // QuarterTriplet,
                                          0.5 * 1.5,         // EighthDotted,
                                          1.0,               // Quarter,
                                          2.0 * 2.0 / 3.0,   // HalfTriplet,
                                          1.0 * 1.5,         // QuarterDotted,
                                          2.0,               // Half,
                                          4.0 * 2.0 / 3.0,   // Triplet,
                                          2.0 * 1.5 };       // HalfDotted,
    

    // beat bet minute : 1분의 몇개의 비트냐
    // const double minutePerBeat = 1.0/ inBpm;    // 1비트의 몇 분이냐
    // const double secondPerBeat = 60.0 * minutePerBeat;
    const double secondPerBeat = 60.0 / inBpm;
    
    return  secondPerBeat * scalars[inNote];
    /*
    enum Notes
    {
        SixteenthTriplet,    // 1/16 triplet
        ThirtySecondsDotted,
        Sixteenth,           // 1/16
        EighthTriplet,
        SixteenthDotted,
        Eighth,              // 1/8
        QuarerTriplet,
        EighthDotted,
        Quarter,              // 1/4
        HalfTriplet,
        QuarterDootted,
        Half,               // 1/2
        Triplet,
        HalfDotted
    };
        
    switch(inNote)
    {
        case Notes::Sixteenth:  return secondPerBeat * 0.25;
        case Notes::Eighth:     return secondPerBeat * 0.5;
        case Notes::Quarter:    return secondPerBeat;
        case Notes::Half:       return secondPerBeat * 2.0;
        
        case Notes::SixteenthTriplet:  return secondPerBeat * (2.0)/(3.0) * 0.25;
        case Notes::EighthTriplet:     return secondPerBeat * (2.0)/(3.0) * 0.5;
        case Notes::QuarerTriplet:    return secondPerBeat * (2.0)/(3.0);
        case Notes::HalfTriplet:       return secondPerBeat * (2.0)/(3.0) * 2.0;
        case Notes::Triplet:       return secondPerBeat * (2.0)/(3.0) * 4.0;
        
        case Notes::ThirtySecondsDotted:  return secondPerBeat * 1.5 * 0.125;
        case Notes::SixteenthDotted:     return secondPerBeat * 1.5 * 0.25;
        case Notes::EighthDotted:    return secondPerBeat * 1.5 * 0.5;
        case Notes::QuarterDootted:       return secondPerBeat * 1.5 ;
        case Notes::HalfDotted:       return secondPerBeat * 3 ;
        
        default: return secondPerBeat;
    };
    */
    
        //triplet 은 2/3
        
}

juce::ValueTree MyParameters::getStateCopied() const noexcept
{
    return mApvts.copyState();
}


void MyParameters::prepare(const double inSampleRate) noexcept
{
    //mValueTest = mParamTest->get();
    mSampleRate = inSampleRate;
    
    const double timeLinearSmoothing = 0.05;
    
    mValueGain.reset(mSampleRate, timeLinearSmoothing);
    
    mValueTest.reset(mSampleRate, timeLinearSmoothing);
    
    for(int i=0;i<2;++i)
    {
        mValueTime[i].reset(mSampleRate, timeLinearSmoothing);
    }
    
    mValueMix.reset(mSampleRate,timeLinearSmoothing);
    mValueAmount.reset(mSampleRate, timeLinearSmoothing);
    
    // PingPong
    mValueWidth.reset(mSampleRate, timeLinearSmoothing);
    
    // LowCut
    mValueLowCut.reset(mSampleRate, timeLinearSmoothing);
    
    // HighCut
    mValueHighCut.reset(mSampleRate, timeLinearSmoothing);
    
    update();
    reset();

}

void MyParameters::smoothen() noexcept
{
    mValueGain.getNextValue();
    mValueTest.smoothen();
    
    for(int i=0;i<2;++i)
    {
        mValueTime[i].smoothen();
    }
    mValueMix.getNextValue();
    mValueAmount.getNextValue();
    mValueWidth.getNextValue();
    
    // LowCut
    mValueLowCut.getNextValue();
    
    // HighCut
    mValueHighCut.getNextValue();
}

void MyParameters::update(const double inBpm) noexcept
{
    mValueTest.setTarget(mParamTest->get());
    
    const float gain = juce::Decibels::decibelsToGain(mParamGain->get());
    mValueGain.setTargetValue(gain);
    
    const bool tempo = mParamTemopo->get();
    
    for(int i=0;i<2;++i)
    {
        const int ch = mValuePingPong ? 0 : i;
        const double timeSec =  tempo ? getTimeByNote(inBpm, mParamNote[ch]->getIndex()) :
                                        mParamTime[ch]->get() * 0.001f;
                                        
        mValueTime[i].setTarget(timeSec * mSampleRate);
    }
    
    //Mix
    const float mix = mParamMix->get() * 0.01f;
    mValueMix.setTargetValue(mix);
    
    //FeedBack
    const float amount = mParamAmount->get() * 0.01f;
    mValueAmount.setTargetValue(amount);
    
    //PingPong
    const float width = mParamWidth -> get() * 0.01f;
    mValueWidth.setTargetValue(width);
    mValuePingPong = mParamPingPong -> get();
    
    //LowCut
    mValueLowCut.setTargetValue(mParamLowCut -> get());
    
    //HighCut
    mValueHighCut.setTargetValue(mParamHighCut -> get());
}



void MyParameters::reset() noexcept
{
    mValueGain.setCurrentAndTargetValue(mValueGain.getTargetValue());
    mValueTest.setCurrent(mValueTest.getTarget());
    
    for(int i=0;i<2;++i)
    {
        mValueTime[i].setCurrent(mValueTime[i].getTarget());
    }
    
    //Mix
    mValueMix.setCurrentAndTargetValue(mValueMix.getTargetValue());
    
    //Amount
    mValueAmount.setCurrentAndTargetValue(mValueAmount.getTargetValue());
    
    //PingPong
    mValueWidth.setCurrentAndTargetValue(mValueWidth.getTargetValue());
    
    //LowCut
    mValueLowCut.setCurrentAndTargetValue(mValueLowCut.getTargetValue());
    
    //HighCut
    mValueHighCut.setCurrentAndTargetValue(mValueHighCut.getTargetValue());
}


juce::AudioProcessorValueTreeState::ParameterLayout MyParameters::initparameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
  
    layout.add(std::make_unique<juce::AudioParameterFloat>(MyParamId::Output::Gain,
                                                           "Gain",
                                                           juce::NormalisableRange<float>(-24.0f,24.0f,0.1f),
                                                           0.0f,
                                                           juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromDecibels)));
    
    layout.add(std::make_unique<juce::AudioParameterFloat>(MyParamId::Test,
                                                           "Test",
                                                           juce::NormalisableRange<float>(0.0f,1.0f,0.1f),
                                                           0.0f));
    for(int i=0;i<2;++i)
    {
        const juce::String name = (i==0) ? "Delay TimeL" : "Delay TimeR";
        layout.add(std::make_unique<juce::AudioParameterFloat>(MyParamId::Delay::Time[i],
                                                               name,
                                                               juce::NormalisableRange<float>(kTimeMin,kTimeMax,0.1f),
                                                               1000.0f,
                                                               juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromMilliseconds)
                                                                                                    .withValueFromStringFunction(milliSecondsFromString)));
    }
    
    layout.add(std::make_unique<juce::AudioParameterFloat>(MyParamId::Output::Mix,
                                                       "Mix",
                                                       juce::NormalisableRange<float>(0.0f,100.0f,1.0f),
                                                       50.0f,
                                                       juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromPercent)));
             
     layout.add(std::make_unique<juce::AudioParameterFloat>(MyParamId::FeedBack::Amount,
                                                       "Amount",
                                                       juce::NormalisableRange<float>(-95.0f,95.0f,1.0f),
                                                       20.0f,
                                                       juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromPercent)));
                                                       
    layout.add(std::make_unique<juce::AudioParameterBool>(MyParamId::Control::Tempo,"Tempo",false));
    
    const juce::StringArray notes = {"1/16 triplet",
                                     "1/32 dotted",
                                     "1/16",
                                     "1/8 triplet",
                                     "1/16 dotted",
                                     "1/8",
                                     "1/4 triplet",
                                     "1/8 dotted",
                                     "1/4",
                                     "1/2 triplet",
                                     "1/4 dotted",
                                     "1/2",
                                     "1/1 triplet",
                                     "1/2 dotted"   };
    
    for(int i=0; i<2 ; ++i)
    {
        const juce::String nameNote = (i ==0) ? "Delay Note L" : "Delay Note R";
        layout.add(std::make_unique<juce::AudioParameterChoice>(MyParamId::Delay::Note[i],
                                                                nameNote,
                                                                notes,
                                                                notes.indexOf("1/4")));
    }
    
    layout.add(std::make_unique<juce::AudioParameterBool>(MyParamId::Control::Link, "Stereo Link", false));
    
    
    layout.add(std::make_unique<juce::AudioParameterFloat>(MyParamId::PingPong::Width,
                                                            "Width",
                                                            juce::NormalisableRange<float>(-100.0f,100.0f,0.1f),
                                                            0.0f,
                                                            juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromPercent)));
    
    layout.add(std::make_unique<juce::AudioParameterBool>(MyParamId::Control::PingPong, "Ping Pong", false));
    
    layout.add(std::make_unique<juce::AudioParameterFloat>(MyParamId::FeedBack::LowCut,
                                                           "LowCut",
                                                           juce::NormalisableRange<float>(20.0f,20000.0f,1.0f),
                                                           20.0f,
                                                           juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromHz)
                                                                                                .withValueFromStringFunction(hzFromString)));
                                                                                                
    layout.add(std::make_unique<juce::AudioParameterFloat>(MyParamId::FeedBack::HighCut,
                                                           "HighCut",
                                                           juce::NormalisableRange<float>(20.0f,20000.0f,1.0f),
                                                           20000.0f,
                                                           juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromHz)
                                                                                                .withValueFromStringFunction(hzFromString)));
    
    return layout;
}


void MyParameters::parameterChanged(const juce::String& inParamID,float inValue)
{
    if(mFlagLinking.load() ==true)
    {
        return;
    }
    //지금 발생한 파라미터체인지가 gui에서 발생한 것인가, 아니면 코드에서 발생한 것인가
    //이렇게 해야지 재귀함수를 막을수 있다.
    const juce::String& idLink = MyParamId::Control::Link.getParamID();
    const juce::String& idTimeL = MyParamId::Delay::Time[0].getParamID();
    const juce::String& idTimeR = MyParamId::Delay::Time[1].getParamID();
    const juce::String& idNoteL = MyParamId::Delay::Note[0].getParamID();
    const juce::String& idNoteR = MyParamId::Delay::Note[1].getParamID();
    
    const int masterCurrnet = mChannelMaster.load();
    const int masterNew = (inParamID == idTimeR || inParamID == idNoteR) ? 1:0;
    if(masterCurrnet != masterNew)
    {
        mChannelMaster.store(masterNew);
    }
    
    // link버튼만 눌렀을 때를 포함하여 L채널을 눌렀을때는 mChannelMaster가 0이 된다
    
    //DBG("Master : " << mChannelMaster );
    
    
    if(inParamID==idLink)
    {
        if(inValue == 1.0f)     // 링크가 연결되었을때
        {
            // DBG("Stereo Link  ON");
            mApvts.addParameterListener(idTimeL, this);
            mApvts.addParameterListener(idTimeR, this);
            mApvts.addParameterListener(idNoteL, this);
            mApvts.addParameterListener(idNoteR, this);
            startTimer(30); //1초에 30번
        }
        else
        {
            stopTimer();
            // DBG("Stereo Link OFF");
            mApvts.removeParameterListener(idTimeL, this);
            mApvts.removeParameterListener(idTimeR, this);
            mApvts.removeParameterListener(idNoteL, this);
            mApvts.removeParameterListener(idNoteR, this);
            
            return;
        }
    }
    
}

void MyParameters::timerCallback()
{
    // master 채널 값으로 slave 채널을 싱크
    const int master = mChannelMaster.load();
    
    mFlagLinking.store(true);
    
    for(int i=0;i<2;++i)
    {
        if(i != master )
        {
            *(mParamTime[i]) = mParamTime[master]->get();
            *(mParamNote[i]) = mParamNote[master]->getIndex();
        }
    }
    
    mFlagLinking.store(false);
}

// 멀티 스레드
// 1.

/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "MyParameters.h"
#include "MyHelper.h"

//==============================================================================
EulerDelayAudioProcessor::EulerDelayAudioProcessor()
: AudioProcessor (BusesProperties().withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                                   .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
mApvts(*this, nullptr,"MyParameters", MyParameters::initparameterLayout()),
mParameters(mApvts),
mPresetManager(mParameters)
{
}
EulerDelayAudioProcessor::~EulerDelayAudioProcessor()
{
}

//==============================================================================
const juce::String EulerDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool EulerDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool EulerDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool EulerDelayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double EulerDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EulerDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int EulerDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void EulerDelayAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String EulerDelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void EulerDelayAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void EulerDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mParameters.prepare(sampleRate);
    mModuleDelay.prepare(sampleRate);
    
    juce::dsp::ProcessSpec spec = {sampleRate, (juce::uint32)samplesPerBlock, 2};
    mModuleFeedback.prepare(spec);
}

void EulerDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}


bool EulerDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    return layouts.getMainOutputChannelSet()==juce::AudioChannelSet::stereo();  //(6)
} // 스테레오일때만 true 가 나올거임


void EulerDelayAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    const float* bufferInputL = buffer.getReadPointer(0);
    const float* bufferInputR = buffer.getReadPointer(1);
    
    float* bufferOutputL = buffer.getWritePointer(0);
    float* bufferOutputR = buffer.getWritePointer(1);
    
    double bpm = 120.0;     // 기본 bpm
    updateBpm(bpm);
    mParameters.update(bpm);
    
    for(int i=0;i<buffer.getNumSamples();++i)
    {
       mParameters.smoothen();
       
       const float dryL = bufferInputL[i];
       const float dryR = bufferInputR[i];
       
       float feedbackL = 0.0f;
       float feedbackR = 0.0f;
       mModuleFeedback.processPop(feedbackL, feedbackR);
       
       
       float outPingPongL = 0.0f;
       float outPingPongR = 0.0f;
       
       mModulePingPong.process(dryL, dryR, feedbackL, feedbackR,
                               outPingPongL, outPingPongR,
                               mParameters.getValuePingPong(),
                               mParameters.getValueWidth());

       float wetL = 0.0f;
       float wetR = 0.0f;
       mModuleDelay.process(outPingPongL, outPingPongR,
                            wetL , wetR ,
                            mParameters.getValueTime(0),
                            mParameters.getValueTime(1));

       const float outL = mModuleOutput.process(dryL, wetL,
                                                mParameters.getValueMix(),
                                                mParameters.getValueGain());
                                                
       const float outR = mModuleOutput.process(dryR, wetR,
                                                mParameters.getValueMix(),
                                                mParameters.getValueGain());
       
       bufferOutputL[i] = outL;
       bufferOutputR[i] = outR;

       mModuleFeedback.processPush(wetL, wetR,
                                   mParameters.getValueAmount(),
                                   mParameters.getValueLowCut(),
                                   mParameters.getValueHighCut());
    
       //bufferOutputL[i] = mParameters.getValueTest();
       //bufferOutputR[i] = mParameters.getValueTest();
        
    }
    
    #if JUCE_DEBUG
    MyHelper::protectEars(buffer);
    #endif
}

//==============================================================================
bool EulerDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* EulerDelayAudioProcessor::createEditor()
{
    return new EulerDelayAudioProcessorEditor (*this);
}

//==============================================================================
void EulerDelayAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    //Parameter
    juce::ValueTree statePlugin(JucePlugin_Name);
    
    const juce::ValueTree stateParameter = mApvts.copyState();
    if(statePlugin.isValid())
    {
        statePlugin.appendChild(stateParameter, nullptr);
    }
    
    const juce::ValueTree statePreset = mPresetManager.getState();
    if(statePreset.isValid())
    {
        statePlugin.appendChild(statePreset, nullptr);
    }
    
    std::unique_ptr<juce::XmlElement> xmlState = statePlugin.createXml();
    
    if(xmlState != nullptr)
    {
        copyXmlToBinary(*xmlState, destData);
        
        const juce::File stateFile(juce::File::getSpecialLocation(juce::File::userDesktopDirectory).getChildFile("pluginState.xml"));
        xmlState->writeTo(stateFile);
        stateFile.create();
    }
}

void EulerDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlPlugin = getXmlFromBinary(data, sizeInBytes);
    
    if(xmlPlugin == nullptr)
    {
        return;
    }
    
    const juce::ValueTree statePlugin = juce::ValueTree::fromXml(*xmlPlugin);
    
    if(statePlugin.isValid() == false || statePlugin.getType().toString()!= JucePlugin_Name)
    {
         return ;
    }
    
    const juce::ValueTree statePreset = statePlugin.getChildWithName(mPresetManager.getIdState());
    if(statePreset.isValid())
    {
        mPresetManager.setByState(statePreset);
    }
    
    const juce::ValueTree stateParameter = statePlugin.getChildWithName(mApvts.state.getType());
    if(stateParameter.isValid())
    {
        mApvts.replaceState(stateParameter);
    }
}

void EulerDelayAudioProcessor::reset()
{
    mParameters.reset();
    
    mModuleDelay.reset();
    
    mModuleFeedback.reeset();
    
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EulerDelayAudioProcessor();
}


juce::AudioProcessorValueTreeState& EulerDelayAudioProcessor::getmApvts()
{
    return mApvts;
}


MyPresetManager& EulerDelayAudioProcessor::getPresetManager() noexcept
{
    return mPresetManager;
}

void EulerDelayAudioProcessor::updateBpm(double& outBpm) noexcept
{
    juce::AudioPlayHead* playHead = getPlayHead();
    if(playHead ==nullptr)
    {
        return;
    }
    
    auto positioninfo = playHead->getPosition();
    if(!positioninfo)   //optional 일때만 auto로 받아서 한다
    {
        return;
    }
    
    auto bpmFromDaw = positioninfo -> getBpm();
    if(bpmFromDaw)
    {
        outBpm = *bpmFromDaw;
    }
    
}

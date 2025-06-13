/*
  ==============================================================================

    MyPresetManager.cpp
    Created: 12 Mar 2025 11:50:46am
    Author:  sanghoonyou

  ==============================================================================
*/

#include "MyPresetManager.h"
MyPresetManager::MyPresetManager(MyParameters& inParameters)
:mParameters(inParameters),
 mFactoryPresetCurrent(-1),
 mDirPreset(juce::File::getSpecialLocation(juce::File::userDocumentsDirectory).getChildFile(JucePlugin_Name)),
 mIdstate("Preset")
{
    resetFactoryPreset();
}

MyPresetManager::~MyPresetManager()
{

}

juce::String MyPresetManager::getNametFactoryPreset(const int inIndex) const noexcept
{
    return mArrayFactoryPreset[inIndex].mName;
}

int MyPresetManager::getNumFactoryPresets() const noexcept
{
    return mArrayFactoryPreset.size();
}

int MyPresetManager::getFactoryPresetCurrent() const noexcept
{
    return mFactoryPresetCurrent;
}

void MyPresetManager::setFactoryPreset(const int inIndex) noexcept
{
    mFactoryPresetCurrent = inIndex;
    mParameters.setParamsByFactoryPreset(mArrayFactoryPreset[mFactoryPresetCurrent]);
}

void MyPresetManager::resetFactoryPreset() noexcept
{
    mArrayFactoryPreset.clear();
    
    mArrayFactoryPreset.add({ "Preset1",{111.0f,111.0f},50.0f,35.0f,-10.0f});
    mArrayFactoryPreset.add({ "Preset2",{222.0f,222.0f},50.0f,35.0f,-10.0f});
    mArrayFactoryPreset.add({ "Preset3",{333.0f,333.0f},50.0f,35.0f,-10.0f});
}

const juce::File& MyPresetManager::getDirPreset() const noexcept
{
    return mDirPreset;
}

const juce::String& MyPresetManager::getXmlPresetCurrent() const noexcept
{
    return mXmlPresetCurrent;
}

void MyPresetManager::setXmlPresetCurrnet(const juce::String& inNamePreset) noexcept
{
    mXmlPresetCurrent = inNamePreset;
}

void MyPresetManager::saveXmlPreset(const juce::File& inFileXml) noexcept
{
    //현재 파라미터 값 보관된 트리 복사
    const juce::ValueTree stateCopied = mParameters.getStateCopied();
    
    //ValueTree -> Xml
    std::unique_ptr<juce::XmlElement> xml = stateCopied.createXml();
    
    if(xml == nullptr)
    {
        return;;
    }
    
    if(xml->writeTo(inFileXml)==false)
    {
        return;
    }
    
    if(inFileXml.create().failed())
    {
        return;
    }
    
    setXmlPresetCurrnet(inFileXml.getFileNameWithoutExtension());
}

void MyPresetManager::loadXmlPreset(const juce::File& inFileXml) noexcept
{
    // file -> xml -> valuetree
    // (1) file -> xml
    std::unique_ptr<juce::XmlElement> xml = juce::XmlDocument::parse(inFileXml);
    
    if(xml == nullptr)
    {
        return;
    }
    
    // xml -> valuetree
    const juce::ValueTree presetState = juce::ValueTree::fromXml(*xml);
    
    if(presetState.isValid() ==false)
    {
        return;
    }
    
    // valuetree -> parameter
    
    if(mParameters.setParamsByValueTree(presetState) == true)
    {
        setXmlPresetCurrnet(inFileXml.getFileNameWithoutExtension());
    }
}

const juce::Identifier& MyPresetManager::getIdState() const noexcept
{
    return mIdstate;
}

juce::ValueTree MyPresetManager::getState() const noexcept
{
    juce::ValueTree state(getIdState());    //"Preset"이라는 이름을 갖은 벨류트리 새거 만듦
    state.setProperty("name", getXmlPresetCurrent(), nullptr);
    return state;
}   

void MyPresetManager::setByState(const juce::ValueTree& inState) noexcept
{
    if(inState.isValid() && inState.getType() == getIdState())
    {
        const juce::String namePreset = inState.getProperty("name");
        setXmlPresetCurrnet(namePreset);
    }
}

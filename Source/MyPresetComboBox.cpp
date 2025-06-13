/*
  ==============================================================================

    MyPresetComboBox.cpp
    Created: 12 Mar 2025 10:54:07am
    Author:  sanghoonyou

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MyPresetComboBox.h"

//==============================================================================
MyPresetComboBox::MyPresetComboBox(MyPresetManager& inPresetManager)
:mPresetManager(inPresetManager)
{
    //resetByFactoryPreset();
    resetByXmlPreset();
    
    onChange = [this]()
    {
        const int id = getSelectedId();
        const juce::String text = getText();
        
        if(id==0)
        {
            return;
        }
        //mPresetManager.setFactoryPreset(id -1);
        mFileChooser = std::make_unique<juce::FileChooser>(id==IdComboBoxPreset::Save ? "Save":"Load",
                                                           mPresetManager.getDirPreset(),
                                                           "*.xml",
                                                           false);
                                                           
        int flag = juce::FileBrowserComponent::canSelectFiles;
        flag |= (id==IdComboBoxPreset::Save) ? juce::FileBrowserComponent::saveMode :
                                               juce::FileBrowserComponent::openMode ;
                                               
        auto callback = [this,id](const juce::FileChooser& inFileChooser)
        {
            const juce::File file = inFileChooser.getResult();
            const juce::String nameFile = file.getFileName();
            
            if(nameFile.isNotEmpty())
            {
            
                switch(id)
                {
                    case IdComboBoxPreset::Save:
                    {
                        DBG("Save");
                        mPresetManager.saveXmlPreset(file.withFileExtension("xml"));
                        break;
                    }
                    case IdComboBoxPreset::Load:
                    {
                        DBG("Load");
                        mPresetManager.loadXmlPreset(file);
                        break;
                    }
                }
            }
            
            resetByXmlPreset();
        };
        
        mFileChooser->launchAsync(flag, callback);
    };
    
}

MyPresetComboBox::~MyPresetComboBox()
{
    
}

void MyPresetComboBox::resetByFactoryPreset() noexcept
{
    clear(juce::NotificationType::dontSendNotification);
    
    for(int i=0;i<mPresetManager.getNumFactoryPresets();++i)
    {
        addItem(mPresetManager.getNametFactoryPreset(i), i+1);
    }
    
    const int indexCurrent = mPresetManager.getFactoryPresetCurrent();
    
    if(indexCurrent >0)
    {
        setSelectedId(indexCurrent+1,juce::NotificationType::dontSendNotification);
    }
}

void MyPresetComboBox::resetByXmlPreset() noexcept
{
    clear(juce::NotificationType::dontSendNotification);
    addItem("Save", IdComboBoxPreset::Save);
    addItem("Load", IdComboBoxPreset::Load);
    
    
    setText(mPresetManager.getXmlPresetCurrent(),juce::NotificationType::dontSendNotification);
}

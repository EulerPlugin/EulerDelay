## ✅ [3] Parameter Binding

This plugin uses internal attachments to bind parameters to GUI components.
Each custom component manages its own connection to the ```AudioProcessorValueTreeState``` inside
its class. Additionally, button clink behavior is split between **internal visual updates** and
** external layout changes**.

<br>

**🔹 1. MyRotaryKnob : Internal Slider–Parameter Binding**

Class : ```MyrotaryKnob```

~~~cpp
MyRotaryKnob::MyRotaryKnob(juce::AudioProcessorValueTreeState& inApvts,
                           const juce::String& inParamId,
                           const bool inDrawFromMiddle)
: juce::Slider(inParamId),
  mAttachment(inApvts, inParamId, *this)
{
    ...
}
~~~

- ```mAttachment``` is a ```SliderAttachment``` that synchronizes the silder with the APVTS paramter
- The component is completely self-contained - no external binding needed
- Two-way sync is automatic


<br>
<br>


**🔹 2. MyParamToggleButton : Button Binding and Visual State**

Class : ```MyParamToggleButton```

~~~cpp
MyParamToggleButton::MyParamToggleButton(juce::AudioProcessorValueTreeState& inApvts,
                                         const juce::String& inParamId,
                                         const int inCmdId)
: mAttatchment(inApvts, inParamId, *this)
{
    setClickingTogglesState(true);

    updateButtonText(); // Set initial text ("ON"/"OFF")

    setCommandToTrigger(nullptr, inCmdId, false);

    onClick = [this]() {
        updateButtonText(); // Visually updates text only
    };
}
~~~

- ```mAttatchment``` is a ```ButtonAttachment``` that binds the toggle state to the parameter.
- ```onClick``` handles UI feedback(```"ON"```/```"OFF"```)
- The actual parameter value is updated internally through the attachment


<br>
<br>


**🔹 3. PanelDelay::buttonClicked(): Functional UI Logic**

Class : ```PanelDelay```

~~~cpp
void PanelDelay::buttonClicked(juce::Button* inButton)
{
    switch (inButton->getCommandID())
    {
        case MyHelper::CmdIdButtons::Tempo:
            setVisibleLaveAndKnobs(inButton->getToggleState(), mButtonPingPong.getToggleState());
            break;

        case MyHelper::CmdIdButtons::PingPong:
            setTextLabels(inButton->getToggleState());
            setVisibleLaveAndKnobs(mButtonTempo.getToggleState(), inButton->getToggleState());
            break;
    }
}
~~~



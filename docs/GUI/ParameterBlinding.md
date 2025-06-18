## ✅ [3] Parameter Binding

This plugin uses internal attachments to bind parameters to GUI components.
Each custom component manages its own connection to the ```AudioProcessorValueTreeState``` inside
its class. Additionally, button clink behavior is split between **internal visual updates** and
** external layout changes**.

<br>

**🔹 1. ```MyRotaryKnob``` : Internal Slider–Parameter Binding**

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


**🔹 2. ```MyParamToggleButton``` : Button Binding and Visual State**

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


**🔹 3. ```PanelDelay::buttonClicked()``` : Functional UI Logic**

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

- This function handels UI logic triggered by button toggles
- It **shows/hides** Time or Note knobs depending on mode
- It also **updates label text** to match mono/stereo mode

<br>
<br>


**🔹 4. ```setVisibleLaveAndKnobs()``` Logic**

Still in ```PanelDelay```:

~~~cpp
void PanelDelay::setVisibleLaveAndKnobs(const bool inTempo, const bool inPingPong)
{
    for (int i = 0; i < 2; ++i)
    {
        mKnobTime[i].setVisible(i == 0 ? !inTempo : !inTempo && !inPingPong);
        mKnobNote[i].setVisible(i == 0 ?  inTempo :  inTempo && !inPingPong);
    }
}
~~~

| Mode        | Left (L) Visible  | Right (R) Visible        |
| ----------- | ----------------- | ------------------------ |
| Tempo OFF   | Time L            | Time R (if not PingPong) |
| Tempo ON    | Note L            | Note R (if not PingPong) |
| PingPong ON | Only Left visible | Right hidden completely  |


<br>
<br>

**🔹 5. ```EulerDelayAudioProcessorEditor::buttonClicked()``` : Layout Changes**

Class : ```EulerDelayAudioProcessorEditor```

~~~cpp
void EulerDelayAudioProcessorEditor::buttonClicked(juce::Button* inButton)
{
    switch (inButton->getCommandID())
    {
        case MyHelper::CmdIdButtons::PingPong:
            mPanelDelay.setSize(...);
            resized();
            mPanelPingPong.setVisible(mButtonPingPong.getToggleState());
            break;
    }
}
~~~

- When PingPong is toggled, the Delay panel height is halved
- PingPong panel is shown or hidden
- ```resized()``` triggers full UI layout recalculation

<br>
<br>

![converted_output](https://github.com/user-attachments/assets/692e832c-08e5-4730-8e31-c19b02013f41)


## 4. Stereo Link Implementation

<br>

🎯 What It Does

The **Stereo Link** feature keeps Delay Time and Note parameters in sync between left and right channels. 
When the toggle is enabled, modifying one side will automatically update the other to match it.

<br>
<br>

🧱 1. Initial Setup & Listener Registration

At initialization, only the Link toggle parameter is registered as a listener:

~~~cpp
mApvts.addParameterListener(MyParamId::Control::Link.getParamID(), this);
~~~

When the user turns on the **Link** toggle, the following happens inside

- Parameter listeners for both left and right Time and Note parameters are dynamically registered
- A periodic timer is started:

~~~cpp
if (inParamID == idLink && inValue == 1.0f)
{
    mApvts.addParameterListener(idTimeL, this);
    mApvts.addParameterListener(idTimeR, this);
    mApvts.addParameterListener(idNoteL, this);
    mApvts.addParameterListener(idNoteR, this);

    startTimer(30); // Runs timerCallback ~30 times per second
}
~~~

<br>
<br>

🔁 2. Synchronization Mechanism

Once the Link is on, any change to a time or note knob (L or R) triggers ```parameterChanged()```.
We determine which side was touched and mark it as the master:

~~~cpp
const int masterNew = (inParamID == idTimeR || inParamID == idNoteR) ? 1 : 0;
mChannelMaster.store(masterNew);
~~~

Then, the timer handles syncing.
```startTimer(30)``` causes ```timerCallback()``` to be called periodically from the **GUI thread**, which forces the slave to follow the master:

~~~cpp
void MyParameters::timerCallback()
{
    mFlagLinking.store(true); // Prevent recursive callback

    const int master = mChannelMaster.load();

    for (int i = 0; i < 2; ++i)
    {
        if (i != master)
        {
            *(mParamTime[i]) = mParamTime[master]->get();
            *(mParamNote[i]) = mParamNote[master]->getIndex();
        }
    }

    mFlagLinking.store(false);
}
~~~

To prevent recursive ```parameterChanged()``` calls during this forced sync, we use a guard:

~~~cpp
if (mFlagLinking.load()) return;
~~~

<br>

--------

⛔ When Link Is Turned Off

When the user disables the Link toggle:

- The timer stops
- All temporary listeners are removed

~~~cpp
stopTimer();

mApvts.removeParameterListener(idTimeL, this);
mApvts.removeParameterListener(idTimeR, this);
mApvts.removeParameterListener(idNoteL, this);
mApvts.removeParameterListener(idNoteR, this);
~~~

<br>
<br>


🧵 Threading Considerations

- ```timerCallback()``` runs on the **GUI (message) thread**, not the audio thread.
- To safely communicate with the audio thread, we use ```std::atomic``` for shared flags like ```mChannelMaster``` and ```mFlagLinking```.

> This architecture avoids CPU spikes and glitchy behavior in the audio thread by offloading all syncing to the GUI thread.

<br>
<br>

<img src = "https://github.com/user-attachments/assets/4fa4d366-91a5-4d37-9276-3e316636f53c" width = "250"/>


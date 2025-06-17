### 4. Stereo Link Implementation

<br>

🎯 What It Does

The **Stereo Link** feature keeps Delay Time and Note parameters in sync between left and right channels. 
When the toggle is enabled, modifying one side will automatically update the other to match it.

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

🔁 2. Synchronization Mechanism

Once the Link is on, any change to a time or note knob (L or R) triggers parameterChanged().
We determine which side was touched and mark it as the master:

~~~cpp
const int masterNew = (inParamID == idTimeR || inParamID == idNoteR) ? 1 : 0;
mChannelMaster.store(masterNew);
~~~

Then, the timer handles syncing.
startTimer(30) causes timerCallback() to be called periodically from the **GUI thread**, which forces the slave to follow the master:

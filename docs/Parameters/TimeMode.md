## 5. Tempo vs Millisecond Mode


This delay plugin allows users to set delay time in two different ways:

- **Millisecond Mode**: The user manually enters time in milliseconds.
- **Tempo Sync Mode**: Time is automatically calculated based on the DAW’s BPM and selected note value.

<br>
<br>

🔹 Step 1. Tempo Parameter Definition

~~~cpp
layout.add(std::make_unique<AudioParameterBool>(
    MyParamId::Control::Tempo, "Tempo", false));
~~~

- This toggle parameter allows the user to switch between ms mode and tempo-sync mode.
- Default value: false (millisecond mode).

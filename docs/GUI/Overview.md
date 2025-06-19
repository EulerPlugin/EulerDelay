## ✅ 1. Overview : Modular GUI System

<br>

The GUI system is designed for **maximum maintainability and scalability** through **functional
modularuzation, state-based rendering,** and a **centralized LookAndFeel customization** approach.

<br>

### 🔹 1. Structural Modularity (Panel-Based Design)

THe interface is divided into independent ```Panel``` classes, each inheriting from a common ```PanelBase```.
Each panel is responsible for a specific function:

- ```PanelControl``` : Preset, Tempo, Link, PingPong control
- ```PanelDelay``` : Delay Time/Note Knobs
- ```PanelFeedback``` : Feedback amount and filtering
- ```PanelOutput``` : Mix and output gain
- ```PanelPingPong``` : PingPong width control

This modular approach enables **independent development and maintenance** of each functional block.

<img width="611" alt="image" src="https://github.com/user-attachments/assets/b239e1b2-152d-4381-a18d-7ca1020f5956" />

<br>
<br>
<br>
<br>
<br>



### 🔹 2. State-Based Rendering

Certain UI elements are shown or hidden depending on toggle states:

- When PingPong is enabled, the right-side delay knobs are hidden
- When Tempo mode is enabled, Note Knobs are shown instead of Time knobs.

![converted_output](https://github.com/user-attachments/assets/0994fc69-e5bf-4342-a118-d9cfc3051a3d)

This dynamic rendering is handeled via methods like ```buttonClicked()``` and ```setVisibleLabelAndKnobs()```

-> This allows **UI simplification without feature compromise,** enabling multiple constrol modes within a single panel.

<br>
<br>
<br>

### 🔹 3. Centralized Look & Feel Customization

All visual styling is handled through a custom ```MyLookAndFeel``` class, ensuring 
consistency across the UI:

- Color themes are defined in the ```MyColors``` namespace
- Typogtaphy and sizing are standardized via ```Mysize```
- The rotary slider is fully custom-rendered with gradients, shadows, and layered visuals.

This centralization ensures **consistent aesthetics and quick global updates** when needed.

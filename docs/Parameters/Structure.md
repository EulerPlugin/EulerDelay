### 2. Parameter Initialization & Structure

<br>

🎯 Design Objective

All parameters are initialized through AudioProcessorValueTreeState (APVTS) using a single layout definition.
Within the MyParameters class, each parameter is explicitly cast and stored as a pointer for efficient access.
This architecture enables **real-time safety, modular separation, and high-performance parameter updates.**

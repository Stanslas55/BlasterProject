# BlasterProject

This project contains the implementation of Ray Tracing in C++.

We have set up 3 demonstrations :

- A real-time rendering of a sphere with a luminous orb orbiting around it. Possibility to change the materials in real time (color, shyness, etc...).
- A complex scene which is composed of several objects. There is the possibility to save the generated scenes (/bin/output.png)
- Ability to load an .obj file (A cube, Suzanne, a teapot and a dragon). The dragon is so big that it is not recommended to launch its loading which is estimated to take several hours.

Each demo has a settings window to interact with the project.
The graphical interface has been developed with imgui using opengl (necessary to use imgui) and SDL2.

Escape' to exit.

This project is brought to you by Beasse Maxime, Beucher Maxime, Cisternas Nicolas & Deroche Victor.

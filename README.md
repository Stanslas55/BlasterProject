# BlasterProject

This project contains the implementation of Ray Tracing in C++.

We have set up 3 demonstrations :

- A real-time rendering of a sphere with a luminous orb orbiting around it. Possibility to change the materials in real time (color, shiness, etc...).
- A complex scene which is composed of several objects. There is the possibility to save the generated scenes (/bin/out.png)
- Ability to load an .obj file (A cube, Suzanne, Utah teapot, the Stanford Bunny and a dragon). The dragon is so big that it is not recommended to launch its loading which is estimated to take several hours.

Each demo has a settings window to interact with the output.
The graphical interface has been developed with imgui using opengl (necessary and only to use ImGui) and SDL2.

'Escape' to exit.

# WARNING

Please ensure .obj files under ./BlasterProject/ObjFiles/ are well downloaded. The third demo won't work if so. (This error seems to occur when download project as .zip)

# Credits

This project is brought to you by
- BEUCHER Maxime
- CISTERNAS Nicolas
- DEROCHE Victor
- BEASSE Maxime

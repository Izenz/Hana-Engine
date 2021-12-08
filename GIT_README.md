# Hana-Engine
C++ Game Engine Project for educational purpouses. Developed during Master in AAA Game Programming from UPC School.

## Team Members
[Joel Herraiz Martí](https://github.com/Izenz)

## Guide
### Main Menu Bar
Composed by:
  * File: Currently empty
  * Window: Allows to open/close the available UI windows.
  * Help: 

      * **About us**: Opens the github repo for this project in a browser window.
      * **Engine Info**: Opens a UI window with some basic info about the engine project.
   
### Controls
Camera can be controlled with the following actions:
   * **WASD**: Moves in the axis relative to the camera.
   * **Mouse Left click**: Hold down and move to rotate camera in an FPS-like fashion.
   * **Left ALT**: Toggles Orbit mode around currently loaded model.
   * **Mouse wheel**: Scroll up to zoom in. Scroll down to zoom out.
   
### Comments
Since there is still critical functionality left to be implemented, such as points 4 or 9 and some other aspects who needs a lot of improvement, such as the Orbit function, I detail here some steps in order to load the extra two models from step 3.

   * In order to display a different model, rather than *BakingHouse.fbx*: Go to *ModuleRenderExercise.cpp* > Inside *Init()* function comment/uncomment the final lines in order to change to the desired model.
   * Earth.fbx model should be displayed propperly, but Bed.fbx is considerably large, so much so that it does not fit in the initial position of the frustum. In order to visualize it propperly you only need to *scroll down* or press *S* until its visible (holding down shift will increase the camera movement speed).
   
   

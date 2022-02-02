# Hana-Engine
C++ Game Engine Project for educational purpouses. Developed during Master in AAA Game Programming from UPC School.

## Team Members
[Marius Dambean Partenia](https://github.com/ermario)
[Joel Herraiz Martí](https://github.com/Izenz)

## Guide
### Main Menu Bar
Composed by:
  * File: Functionality yet to be implemented.
  * Edit: Functionality yet to be implemented.
  * Create: The functionality needed to make the buttons in this menu work is there but unfortunately we did not have time to link it to them. We did however hardcore some initial GameObjects in order to test functionality.
  * Window: Allows to open/close the available UI windows and the ImGui Demo for quick reference during development. Not all windows are opened by default: Performance & Engine Config windows are hidden by default and they implement a little bit of functionality so feel free to check them out.
  * Help: Documentation yet to be made.
  * Development: Contains the following: 

      * **About us**: Opens the github repo for this project in a browser window.
      * **Engine Info**: Opens a UI window with some basic info about the engine project.
   
### Controls
Camera can be controlled with the following actions:
   * **WASD**: Moves in the axis relative to the camera.
   * **Mouse Right click**: Hold down and move to rotate camera in an FPS-like fashion.
   * **Left ALT**: Toggles Orbit mode around center of the axis.
   * **Mouse wheel**: Scroll up to zoom in. Scroll down to zoom out.
Objects in the **Hierarchy** panel can be selected and manipulated through the options in the **Inspector** panel, where it is possible to add components and enable or disable the currently selected game object.
   
### Comments
Theres still a lot of functionality to be implemented and unfortunately we did not have time to check memory leaks nor to use profiling tools to further optimize the
code but still it came out like this. 
There are many features that are advanced but incomplete such as Quadtree class that is yet to be integrated into the Camera with the Frustum Culling.
We will try to keep improving and we will work harder for future deliveries.
   
   

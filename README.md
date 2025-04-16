# Duck Hunt Clone with Computer Vision

## Project Overview
The goal of this project is to create a Duck Hunt clone that uses computer vision to detect hand gestures as input for gameplay. The game combines the use of the SFML library for graphics and OpenCV for gesture recognition, allowing players to control the game using their fingers.

## Features
- **Hand Gesture Controls**:
    - **1 Finger**: Shoot.
    - **2 Fingers**: Keep the gun stationary.
    - **3 Fingers**: Reload.
- **Duck Animations**: Includes flying and death animations for the duck.
- **Dog Animations**: Includes idle, celebration, and retrieval animations for the dog.
- **Graphics**: Built using SFML for rendering and animations.
- **Computer Vision**: OpenCV is used to detect hand gestures via a webcam.

## Technologies Used
- **C++**: Core programming language for the project.
- **SFML**: For rendering graphics and animations.
- **OpenCV**: For real-time hand gesture detection.
- **CMake**: For project configuration and build management.

## How to Play
1. Start the game.
2. Use your webcam to show the following gestures:
    - **1 Finger**: Shoot the duck.
    - **2 Fingers**: Keep the duck stationary.
    - **3 Fingers**: Reload your weapon.
3. Aim to shoot as many ducks as possible while managing your ammo.

## Team Members
- Isaias Hernandez
- Garima Sukla
- Nick

## Instructions
1. Ensure you have the required dependencies installed:
    - OpenCV
    - SFML
2. Build the project using CMake.
3. Run the game executable.
4. Use your webcam to interact with the game.

## Notes
- A video demonstration of the project is included in the repository.
- For troubleshooting, refer to the `troubleshoot.sh` script.
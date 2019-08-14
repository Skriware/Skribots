# Skribots
A repository containing an Arduino Library for [Skriware](skriware.com)
3D printed robots.

* 3D printed parts can be found on the
[Skrimarket](https://skrimarket.com/skribots-printlink).
* Hardware assembly instructions can be found
[here](https://skriware.com/support).

## Installation

This is an Arduino Library, so in order to use it you will need
the [Arduino IDE](https://www.arduino.cc/en/main/software).

### Library installation guide

1. Download and unzip the latest
[Skribots](https://github.com/Skriware/Skribots/releases/tag/1.2) release
2. Find your Arduino Libraries folder
  * on Mac OS: `~/Documents/Arduino/libraries/`
  * on Windows: `/ThisPC/Documents/Arduino/libraries/`
3. Copy `Skribots` folder to the above directory
4. Open Arduino IDE and go to `File` -> `Examples`.
Skribots examples should be listed at the bottom of the list
under `Examples from Custom Libraries` section.

If you still have trouble making it work, you can follow
[this tutorial](https://learn.adafruit.com/adafruit-all-about-arduino-libraries-install-use/how-to-install-a-library).

### Remote control

Robot can be controlled remotely via bluetooth. To use this feature you will
need the **Skribots** app and the
[Skribot_mobile](https://github.com/Skriware/Skribot_mobile) library.

Skribots app can be found
* on the
[Google Play](https://play.google.com/store/apps/details?id=com.daftmobile.Skribots)
* on the [AppStore](https://apps.apple.com/app/skribots/id1331957263)

## Library features

Currently supported features:
- DC motors
- Obstacles detection
- LEDs control
- Line following using IR diodes
- Grabber

Features planned for the near future:
- Temperature measurements
- Mechanical end stops
- Weight sensors
- Buzzer
- Accelerometer

## Basic Usage

```c++
#include <Skribot.h> // import header file

Skribot robot; // create robot object

void setup()
{
  robot.AddRotor(9, "Left"); // Add the left rotor and specify its pin number
  robot.AddRotor(10, "Right"); // Add the right rotor and specify its pin number
}

void loop()
{
  robot.MoveForward(2000); // Move forward for 2000 ms
  robot.FaceLeft(3000); // Rotate left for 3000 ms
}
```

## Examples Overview

We've included a few examples to show the library features and usage ideas.

1. `AvoidObstaclesAdvanced` shows more advanced algorithm avoiding deadlocks
2. `AvoidObstaclesBasic` shows simple collision avoidance algorithm
3. `Claw_Operations` shows mechanical grabber operations
4. `LED_Operations` shows how to send multicolor light signals
5. `LineFolowerXSensors` is a series of examples implementing line follower
algorithms using different number of sensors.
6. `ObstacleDetection` shows basic usage of ultrasonic distance sensor 
7. `SimpleMovement` shows basic configuration and movement


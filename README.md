# Skribots
A repository containing Arduino Library for [Skriware](skriware.com) 3D printed robots.

**Important:** 3D printed parts and hardware assembly instructions can be found [here](https://drive.google.com/open?id=0Bz6l25Zss7ghNzNVbVlyb2d4NjQ)

## Installation

This is an Arduino Library, so in order to use it you will need [Arduino IDE](https://www.arduino.cc/en/main/software).

### Library installation guide

1. Download and unzip [StandardCplusplus Library](https://github.com/maniacbug/StandardCplusplus/archive/master.zip)
2. Download and unzip [Skribots](https://github.com/Skriware/Skribots/archive/master.zip)
3. Find your Arduino Libraries folder
    - on Mac OS:  `~/Documents/Arduino/libraries/`
    - on Windows:   `/ThisPC/Documents/Arduino/libraries/`
4. Copy StandardCplusplus and Skribots folders to the above directory
5. Open Arduino IDE and go to `File` -> `Examples`. Skribots examples should be listed at the bottom of the list under `Examples from Custom Libraries` section.

### Remote control

Robot can be controlled remotely via bluetooth. To use this feature you will need Android controlled device and [ToothFairy App](https://play.google.com/store/apps/details?id=com.avrthing.toothfairyfree). The project documentation can be found [here](http://avrthing.com/toothfairy/index.php?option=com_content&view=article&id=7&Itemid=126), the basic usage is shown in the Skribots `SmartphoneControl` example.

## Library features

Currently supported features:
- Robot movements in all directions using servo rotors
- Obstacles detection
- LEDs control
- Line following using IR diods

Features planned for the near future:
- DC motors
- Temperature measurements
- Mechanical end stops
- Weight sensors
- Buzzer
- Accelerometer

## Basic Usage

```
#include <SkriBot.h> // import header file

SkriBot robot; // create robot object

setup {
  robot.AddRotor(9,"Left"); //  Add left rotor and specify PIN number
  robot.AddRotor(10,"Right"); //  Add right rotor and specify PIN number
}

loop {
  robot.MoveForward(2000); // Move forward for 2000 ms
  robot.FaceLeft(3000); // Rotate left for 3000 ms
}
```

## Examples Overview

We've included a few examples to show the library features and usage ideas.

1. `SimpleMovement` example shows basic configuration and movement
2. `SmartphoneControl` example shows bluetooth remote control using Android [ToothFairy App](https://play.google.com/store/apps/details?id=com.avrthing.toothfairyfree)
3. `ObstacleDetection` example shows basic ultrasonic distance sensor 
4. `AvoidObstaclesBasic` example shows simple collision avoidance algorithm
5. `AvoidObstaclesAdvanced` example shows more advanced algorithm with deadlocks avoidance
6. `LineFolowerXSensors` series of examples implementing line follower algorithms using different number of sensors.


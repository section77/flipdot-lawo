# flipdot-lawo

Code repository for controlling the large Lawo flipdot display of Section 77.

## Contents

Currently this repository contains the following Arduino sketches:

* testpatterns: the four test patterns (all yellow, all black, alternating yellow/black, alternating black/yellow) of the OEM controller board
* random: flips random dots in random direction
* demo-window: displays a custom section77 logo with some random actions
* countdown: displays a countdown to UNIX timestamp 1,700,000,000 

## Hardware

The sketches are written for the Wemos LOLIN32 (v1.0.0) ESP32 board and require the corresponding board to be installed in the Arduino IDE. Since the ESP32 logic levels are at 3.3V, level converters (e.g. 74HCT245) are needed.

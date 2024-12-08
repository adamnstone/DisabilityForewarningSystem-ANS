# Disability Forewarning System

## Project Overview

Tourette Syndrome is a neurodevelopmental disorder characterized by making involuntary movements and vocalizations, called tics. For individuals with severe tics, their movements and vocalizations can be misinterpreted as intoxication or aggression by law enforcement, leading to escalation.

The Disability Forewarning System is a device that drivers with Tourette's install in their cars to prevent police from misinterpreting tics at a traffic stop. The device attaches to the rear window of a car and has an ePaper display that remains out of sight until a driver presses a button housed in the cup holder. Once pressed, the ePaper display is rotated into view by a servo motor controlled over Bluetooth and displays the message "Driver Has Tourette Syndrome." By informing officers that a driver has Tourette's, a potentially dangerous situation can be defused.

## Disclaimer & Link to Code Iterations

This repo only contains the final code of my `Disability Forewarning System`. To see iterations and revisions on the code, please see my full documentation of this project on my personal website (linked below), or my [full Fab Academy documentation website](https://fabacademy.org/2023/labs/charlotte/students/adam-stone/) and [Fab Academy GitLab Repo](https://gitlab.fabcloud.org/academany/fabacademy/2023/labs/charlotte/students/adam-stone).

Display Electronics & Software: [`https://adamnstone.com/stem/disability-forewarning-system/display-electronics/`](https://adamnstone.com/stem/disability-forewarning-system/display-electronics/).

Cup Holder Electronics & Software: [`https://adamnstone.com/stem/disability-forewarning-system/cupholder-electronics/`](https://adamnstone.com/stem/disability-forewarning-system/cupholder-electronics/).

Combining Electronics & Final Code: [`https://adamnstone.com/stem/disability-forewarning-system/combining-electronics`](https://adamnstone.com/stem/disability-forewarning-system/combining-electronics)

## Repo Organization

### Raspberry Pi RP2040 Pico
- The code to be run on a [`Raspberry Pi RP2040 Pico`](https://www.raspberrypi.com/products/raspberry-pi-pico/) microcontroller (connected to an [`HM-10 BLE`](https://www.amazon.com/DSD-TECH-Bluetooth-iBeacon-Arduino/dp/B06WGZB2N4/ref=asc_df_B06WGZB2N4?mcid=03db658ff3593f9b976b32f90906adae&tag=hyprod-20&linkCode=df0&hvadid=693293191329&hvpos=&hvnetw=g&hvrand=8994359339454905976&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9191856&hvtargid=pla-350315945458&psc=1) module over UART) can be found in the [`/pico`](./pico/) directory.
    - [`pico/main.py`](./pico/main.py) contains the main logic including executing bluetooth commands recieved by the HM-10 from the [ESP32C3](#esp32c3).
    - [`pico/servo.py`](./pico/servo.py) is a servo motor library for the Pico taken from [How2Electronics](https://how2electronics.com/how-to-control-servo-motor-with-raspberry-pi-pico/).
    - [`pico/display.py`](./pico/display.py) is a WaveShare ePaper display library I slightly modified from [this repo](https://github.com/mcauser/micropython-waveshare-epaper).

### ESP32C3
- The code to be run on an [`ESP32C3`](https://wiki.seeedstudio.com/XIAO_ESP32C3_Getting_Started/) microcontroller can be found in the [`/esp32c3`](./esp32c3/) directory.
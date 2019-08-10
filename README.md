# Arduino joystick Mouse

Program for controlling your PC mouse using Arduino Leonardo with joystick connected to analog inputs and three buttons connected to digital inputs.

Is has beed tested on **Arduino Leonardo** board. For it's major functionality it is possible to use some other Arduino boards like Arduino Micro or Arduino Esplora, but be adviced that pin configuration and some parts of code (like included header files for Esplora) can be different for these boards.

# Usage

1. Upload the sketch using Arduino IDE via USB or by any other method that suits you.

2. Connect your Arduino board using its micro USB port with your PC.

3. See below for buttons and joystick description.

## Circuit

Base of the device is Arduino Leonardo board which can be easily used as mouse and keyboard controller thanks to its MCU.

All used inputs are configurable by preprocessor macros in `joystick_mouse.ino`. The values in default configuration are in order to be used with joystick shield like this one: https://www.funduinoshop.com/Joystick-Shield-V1A

### Joystick

Is connected to two analog inputs and serves for simulation of the mouse movement.

### Buttons

There are three buttons used in the device.

#### Mouse switch

Used to switch the mouse control ON/OFF so you can easily disable the mouse input. When the mouse input is ON, the onboard LED is lit. 

When the program starts the mouse is switched OFF by default.

When the mouse input is OFF, no actions from joystick or other buttons are handled.

It is recommended to switch the mouse input OFF before any attempt to write new FW to you board as the mouse communication can block uploading of new FW. For more information see this guide: 

https://www.arduino.cc/en/Guide/ArduinoLeonardoMicro#toc12


#### Left mouse button

Is it is possible to do a simple left click or hold the button and move the mouse cursor around using the joystick, so you can for example select multiple files, drag a file somewhere, etc...

#### Right mouse button

Is recognized only as a click with the right mouse button to show the context menu if available.

Stepper Motor Control
=====================

This program is designed for the Arduino Mega 2560 microcontroller board and is used to control six NEMA17 stepper motors using A4988 stepper motor drivers. The Arduino receives commands from a PC via the serial port, allowing you to specify which motor to move and in which direction.

Hardware Requirements
---------------------

-   Arduino Mega 2560 board
-   Six A4988 stepper motor drivers
-   Six NEMA17 stepper motors
-   Connections for stepper motor control (specified in the code)

Getting Started
---------------

1.  Install Arduino IDE: Make sure you have the Arduino IDE installed on your computer.

2.  Install Libraries: Ensure that you have the required libraries installed. This code uses the `AccelStepper` library for controlling the stepper motors.

3.  Connections: Connect your hardware as specified in the code. Ensure that the pins for stepper motor control and microstepping are correctly connected to the Arduino Mega 2560.

4.  Upload Code: Open the provided code in the Arduino IDE, select the correct board (Arduino Mega 2560), and upload the code to your Arduino.

Usage
-----

1.  Serial Communication: The Arduino communicates with your PC via the serial port (baud rate 9600). You can use a serial monitor in the Arduino IDE or any other serial communication software to send commands to the Arduino.

2.  Command Format: The commands sent to the Arduino consist of two characters:

    -   The first character specifies the motor to be moved (U, R, F, D, L, B).
    -   The second character specifies the direction of movement (, 1, 2).
3.  Motor Control:

    -   "U": Move the UP motor clockwise 90 degrees turn.
    -   "U1": Move the UP motor counterclockwise 90 degrees turn.
    -   "U2": Move the UP motor clockwise 180 degrees turn.
    -   Repeat the same format for other motors (R, F, D, L, B).
4.  Monitoring: The Arduino will respond with "move completed" when it receives and processes a valid command.

5.  Microstepping: You can set the microstepping level (2, 4, 8, 16, or other) by adjusting the `microstepping` variable in the code.

6.  Speed and Acceleration: Speed and acceleration parameters can be adjusted by modifying the `speed` and `acceleration` variables in the code.

Customization
-------------

Feel free to customize the code to suit your specific requirements. You can modify the pins, microstepping settings, speed, and acceleration to match your hardware and desired performance.

Troubleshooting
---------------

-   Double-check your hardware connections.
-   Ensure that you have the required libraries installed.
-   Check the serial communication settings (baud rate, port).
-   Review the code for any errors or issues.

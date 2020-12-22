# RC-Arduino-Car
A remote controlled Arduino car controlled via wireless commands.

[Watch my (bad) video of it in action](https://www.youtube.com/watch?v=XinCHzYxBoo)

## Use
There are several schematics (coming!) provided in this repository. You can either follow these, and use the stock RC_Drive sketch, or connect to your desired pins and modify the .ino file yourself. 

Once the code is uploaded to the Arduino Uno and you have connected to the HC-06 bluetooth module via a serial bluetooth terminal, use is fairly simple.

### Controls
If you play PC games, these should be familiar:

- **W**: move the car forward
- **A**: turn the car left
- **S**: move the car backward
- **D**: turn the car right

The code has been designed to allow you to concatenate actions. Simply typing in 'w' will make the car move forward, but typing in 'was' will make the car move forward, make it turn left, and make it move backward in succession.

By default, sending the arduino one of these instructions will make the car do that action for one second. If you'd like to change that, you can type in a desired duration (in milliseconds) that you'd like to replace this with. For example, typing *6000* into the terminal should change the duration of each action to 6 seconds. 

*Note: to connect to the HC-06 Bluetooth module used by this contraption, it is recommended you use a serial bluetooth terminal [such as this one for Android](https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal&hl=en&gl=US). Conventional connection methods may be troublesome.*

## Materials
To build your own compatible RC car, you will need the following components:
- x1 Arduino One board
- x1 L293D half-h driver
- x1 HC-06 bluetooth module
- x1 car frame (or building materials to create one yourself)
- x2 9v rectangle batteries (or equivalent)
- x2 motors
- x13 plug in cables (preferably long, I needed extensions for many of them)

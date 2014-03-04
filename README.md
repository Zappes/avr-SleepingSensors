SleepingSensors: Display sensor values and conserve energy
==========================================================

What Is this?
-------------
The idea behind the project is to display some kind of sensor value on an LCD screen for a short while, thereafter putting the system into sleep mode. A button press wakes the system up - the sensor readings are refreshed and displayed for a certain time before the display is switched off again and the system goes into hibernation until the next button press.

With this project, I wanted to learn/practice the following things:

* Writing code for the Arduino using standard C, the AVR libs and Eclipse instead of the oversimplified Arduino IDE.
* Reading analog input.
* Using the controller's sleep mode.
* Using interrupts.
* Using a transistor. I've never done that before and I wanted to try it. :)

The project has been created using an Arduino Mega, i.e. an ATmega2560 microcontroller. It should be portable to practically every other Arduino or plain Atmel controller, though. Actually, this will be my nect project: I want to do something similar using an ATmega328 and a temperature/humidity sensor. This project was the protoype for that plan.

Hardware
--------
A complete list of parts and the schematics can be found in the "Fritzing" directory of this repository. The most important parts are the Arduino Mega, a 16x2 LCD and some bits and pieces you probably have lying around, anyway.

If you don't have Fritzing, get it. It might be less sophisticated than Eagle, which all of the cool kids use, but it's actually _usable_ without having to spend too much time learning how the software works. You can get this nifty tool here at http://www.fritzing.org.

Software peculiarities
----------------------
I haven't really written any C code before, so bear with me if the file organization is horrible, naming conventions weren't followed and the code isn't really good. I'm still learning, and if you're interested in this repo, so are you, probably. :)

I "borrowed" some code from online tutorials, most notably the library for accessing the LCD. I found that one in a german microcontroller forum - if you can read german, you should _really_ visit that page and have a look. It's incredible what can be found there. Anyway, the tutorial I shamelessly copied can be found here:

http://www.mikrocontroller.net/articles/AVR-GCC-Tutorial/LCD-Ansteuerung

I also pasted the stuff found un util.h/util.c from the Arduino libraries. As the amount and originality of that code seems to be neglegible, I guess that's OK.

Eclipse Settings
----------------
The project should be usable in Eclipse without any changes, at least if Eclipse is set up correctly with the GCC-AVR plugin, avrdude and all that stuff. Use google to find out how that works. There are a few things you have to be careful about, though:

* It is absolutely mandatory to activate compiler optimization. Open the project properties, go to "C/C++ Build -> Settings -> Optimiziation" Make sure that the optimization level is set to "Size Optimizations (-Os)". If optimizations are disabled, the delay functions won't work, thus trashing the LCD library code.
* Make sure that you have set the proper clock frequency for your controller in "AVR -> Target Hardware". If your settings are wrong, delay won't work properly and the LCD will show only garbled characters.
* It took me some time to get the avrdude setup for programming the Arduino Mega correct. Here are some hints that helped for me:
    * The programmer hardware you want is "wiring".
    * The port is "/dev/ttyACM0", the baud rate is 115200.
    * You want to have this in the "other options" field: "-C/usr/share/arduino/hardware/tools/avrdude.conf".
    * You also want to go to the "Advanced" tab and activate the option "Auto Chip Erase Cycle (-D)".
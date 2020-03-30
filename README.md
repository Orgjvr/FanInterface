# FanInterface
This acts as an interface to a speed controlled Fan, and simulate a specific speed. I used it for a CyberPower OLS1000EC UPS which needs a fan running at about 4000 rpm and could only get a slower replacement.

## Background
After a power failure, my UPS did not stop beeping. Then I realised that it does not start up anymore. After investigating, I found that the fan failed, and as a safety feature, the UPS does not switch on. After googling a bit, I found the datasheet for the fan: a DA08025B12HF manufactured by Shenzen Huaxia Henstai Electronic Co. I also found someone else who did a similar fan change. His solution was a NE555 outputting a 137Hz square wave (See comment 15). I did not want to lose the fan failure detection functionality, so I decided to build this interface. 

## So what is this?
This interface connects between a fan controller and a fan, and lets you output a specific speed to the controller independant of the connected fan speed, while still monitoring the connected fan speed. As long as the fan speed is above a set limit, it will output the required pulses to the controller. But as soon as the fan speed drop below the limit, then it will also stop the simulated fan speed and the original fan controller can decide what to do with the failure. 

Here is a picture of the final prototype on a breadboard:
![alt text](https://github.com/Orgjvr/FanInterface/blob/master/pics/BreadboardTest.png "Picture of the final prototype on a breadboard")

Here is a picture of the top of the fan interface as well as the bottom:
![alt text](https://github.com/Orgjvr/FanInterface/blob/master/pics/ModuleTop.png "The Top of the module")
![alt text](https://github.com/Orgjvr/FanInterface/blob/master/pics/ModuleBottom.png "The Bottom of the module")

Here is the fan interface working inside the UPS:
![alt text](https://github.com/Orgjvr/FanInterface/blob/master/pics/ModuleInUPS1.png "Fan interface inside UPS")
![alt text](https://github.com/Orgjvr/FanInterface/blob/master/pics/ModuleInUPS2.png "Another fan interface inside UPS")

And last but not least, here is a picture of the broken original fan:
![alt text](https://github.com/Orgjvr/FanInterface/blob/master/pics/fan.png "Broken Original fan")

## Did I try anything else?
Initially I tried a replacement fan, but as it was outputting pulses at too slow a rate, it still did not work. Next I thought to build this solution with an ESP8266-01 as I had loads of them available, but the power supply to the fan was not stable enough to keep the ESP8266 up and running. After changing to a Arduino Pro Mini, I had a stable solution.

## How to build the Fan Interface?

### What do I need?
- An arduino Pro Mini 3.3V (Or any similar mcu)
- PSU. I used a AMS1117 based psu to convert from 12V to 3.3V: https://www.banggood.com/5V-To-3_3V-DC-DC-Step-Down-Power-Supply-Buck-Module-AMS1117-800MA-p-933674.html
- 2 x 3 Pin Male connectors
- 3 Pin Female connector
- 2 x 12 Pin Female connector (Optional) for Arduino Pro Mini.
- 2N7000 Mosfet
- 150 ohm Resistor
- 100K ohm Resistor
- 1N4148 diode

### Schematic
TODO

### Code
The code is available in the https://github.com/Orgjvr/FanInterface/blob/master/FanSimulator/src/main.cpp file. I am using the excellent PlatformIO, and I also included the platformio.ini file as well if you want to use the same mcu. Otherwise adjust it as you need.



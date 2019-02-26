# ProjectGAlarm

***DISCLAIMER***
This will get modulised, ~~UPDATED and cleaned up~~~. Put into folder etc. Thanks for the understanding

***Update 1.1***
I have now updated this into a more professional style with correct logging of all the events in the system. The system now handles everything correctly. Code has been cleaned up and structured. Next update is to modulise the files.


***TODO***
- [x] Clean up code, make it more readable.
- [x] Update logging for all events.
- [ ] Modulise and put code into neat folders for easy access and tinkering.
- [ ] Update the manuals to a correct state. 


This is my first-year entrylevel project.
The system uses serial communication between a Arduino and the computer of the user to work.
I've made this over the time of 5 days as assignment with my friend.
This was a fun experience. I hope you can find use of this simple project. As a base for your project for example. I will continue to develop this as time goes on.
This is however a working product, so I won't be adding anything in the near future.

I plan to however to get some actual motionsensors and doormagnets working with this.


A alarm system with basic functions such as:           
* Turn the alarm on and off (ofcourse)
* Logging
* SOS code
* Sensor triggers
* Siren modes
* Keypad setup
* Modes such as shell-alarm/full-alarm

# How to setup #

To setup this system with the exact same Arduino build I have you need to:
* Change the COM port on the HCentral.cpp line 19.
 (You can find this port by for example looking in the Arduino editor)
* Use the given MAKE-file.
* Run the program AlarmCentral.exe (This will run on LINUX aswell with the .exe extension)


# Schematics #
To rebuild a exacty copy of the alarm system I made
![alt text](https://raw.githubusercontent.com/C-HGP/ProjectGAlarm/master/ProjectGAlarm-master/GAlarmCode/HC/Schematic.png)

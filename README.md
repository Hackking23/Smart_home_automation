:Author: kartik-goel
:Date: 05/05/2023

= Project:  Smart Home Automation
   -Build and IoT device using Arduino IoT Cloud.
   -Built a circuit using ESP32 and Relay module.
   -Designed the project to automate lighting, heating, and security systems in home,offices.
   -Improve user experience by providing an intuitive app interface using Arduino IoT.
   -Compatible with voice assistants like Alexa,Google Home

== Step 1: Installation
   -Copy the home_automation file, edit as you like , comments were given to help.
   -thingProperties.h will automatically created when you set things and Variables in Arduino IoT Cloud.
   -Make sure that variables name in home_automation should match with that inthingProperties.h.
   -Release to the World!

== Step 2: Assemble the circuit

   -Assemble the circuit following the diagram layout.png attached to the sketch

== Step 3: Load the code

   -Upload the code contained in this sketch on to your board
   -Don't forgot to press boot button while uploading

=== Folder structure

....
  smart_home_automation     => Arduino sketch folder
  ├── home_automation.ino   => main Arduino file
  ├── thingProperties.h     => additional file containing Device name,other important functions
  └── ReadMe.md             => this file
....




=== BOM
Bill of the materials you need for this project.

|===
| Part name       | Quantity
| ESP-32          |  1  
| Relay(4-channel)|  1  
| Switch          |  4 
| Bulbs           |  4 
|===



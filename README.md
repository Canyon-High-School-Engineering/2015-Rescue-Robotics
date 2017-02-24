# 2015 Canyon High School Rescue Robotics
This code was written for the 2015 Rescue Robotics competition. The goal of the competition is to locate and record an array of buckets 
## Hardware
### Controller
- Arduino Mega or Uno
- Arduino WiFi Shield (for connection to a base station and SD card slot)
- AdaFruit VC0706 Serial Camera (for taking pictures)
- Adafruit Ultimate GPS module
Planed implementatoion for:
- Resue Robotics Manual Override cirtuit
- Pixy CMUcam5
### Airframe
This code will control almost any 3-DOF vehicle that takes PWM input as altidude, pitch, and roll. The following setup was used:
- 3DR APM 2.6 flight controller, GPS, radio link, PSU
- Really crappy aluminum chassis
- HobbyWing FlyFun Brushless ESC 30A (x4)
- MultiStar 700kv brushless motor
- Mediocre 8" x 4.5 plastic propellers
## Installation
The code was originally written and debugged in EclipseArduino. The code is essentailly Arduino-C with sprinkles of AVR-C and C++. It should complile in any AVR-C enviroment with the standard Arduino libraries avalible. The obscure libraries have been provided in the Libraries folder.

## Usage
 TODO: Write usage instructions

## History
This code was originally written with limited testing ability due to lack of avalibe working hardware. It was forked as 2015_Competition_Quadcopter_Code (in the same repo) to provide working functinaliity during competion.
## Credits
Written in whole by Seth Itow, with indispensable input from Nick Machado.
## License
Licensed under the MIT License.

#include "config.h"
#include <SPI.h>
#include <WiFi.h>
#include <SoftwareSerial.h>
#include <HardwareSerial.h>
#include <Adafruit_GPS.h>
#include <Servo.h>
#include <PID_v1.h>

#import "RelativePositionController.h"

bool usingInterrupt = true;




//Select the serial
//SoftwareSerial gpsSerial(2,3);
HardwareSerial gpsSerial = Serial1;

Adafruit_GPS GPS(&gpsSerial); //Instantiate GPS

RelativePositionController relativePosition; //Instantiate relative position controller


void setup()
{
	//set up serial debugging
	Serial.begin(9600);

	//inialize GPS
	GPS.begin(9600);
	GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
	GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);

	//set home position for relative calculations
	relativePosition.setHomePosition(GPS.latitude,GPS.longitude, GPS.altitude);


}

SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
}

void useInterrupt(boolean v) {
  if (v) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}

uint32_t timer = millis();

// The loop function is called in an endless loop
void loop()
{

// ---------- Update GPS object
	if (GPS.newNMEAreceived()) {
		if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
			return;  // we can fail to parse a sentence in which case we should just wait for another
	}
	if (timer > millis())  timer = millis();


// ---------- Update Relative position
	relativePosition.updateRelativePosition(GPS.latitude,GPS.longitude,GPS.altitude);

	//Add your repeated code here

	switch(FlightMode) {

	case "arm":

		break;

	case takeOff:

		break;

	case FlyToBucket:

		break;

	case recordPhotoAndCoordinates:

		break;

	case setNextBucket:

		break;

	case returnToCenter:

		break;

	case land:

		break;

	case disarm:

		break;

	case emergencyStop:
		//do nothing
		break;
	}

}




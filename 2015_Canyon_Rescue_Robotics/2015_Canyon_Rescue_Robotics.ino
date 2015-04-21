#include "config.h"
#include <SPI.h>
#include <WiFi.h>
#include <SoftwareSerial.h>
#include <HardwareSerial.h>
#include <Adafruit_GPS.h>
#include <Servo.h>
#include <PID_v1.h>

#import "RelativePositionController.h"
#import "FlightController.h"

bool usingInterrupt = true;




//Select the serial
//SoftwareSerial gpsSerial(2,3);
HardwareSerial gpsSerial = Serial1;

Adafruit_GPS GPS(&gpsSerial); //Instantiate GPS

RelativePositionController *relativePosition = new RelativePositionController(); //Instantiate relative position controller
FlightController *flight = new FlightController(relativePosition); //Instantiate flight controller

//state machine state enumeration
enum FlightModeEnum {WAIT_FOR_TRIGGER,
	ARM,TAKE_OFF,
	FLY_TO_BUCKET,RECORD_PHOTO_AND_COORDINATES,
	SET_NEXT_BUCKET,RETURN_TO_CENTER,
	LAND,DISARM,
	EMERGENCY_STOP};

FlightModeEnum flightMode = WAIT_FOR_TRIGGER;

//variables for bucket coordinate calculation
int bucketIndex = 0;
double bucketPolarTheta = 0;
double bucketPolarRadius = 10;
double targetBucketX;
double targetBucketY;


void setup()
{
	//instantiate and initalize state machine enum


	//set up serial debugging
	Serial.begin(9600);

	//inialize GPS
	GPS.begin(9600);
	GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
	GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);

	//set home position for relative calculations
	relativePosition->setHomePosition(GPS.latitude,GPS.longitude, GPS.altitude);


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
	relativePosition->updateRelativePosition(GPS.latitude,GPS.longitude,GPS.altitude);

	//Add your repeated code here

	switch(flightMode) {

	case WAIT_FOR_TRIGGER:
		if(digitalRead(AUTOPILOT_ACTIVE)){
			flightMode = ARM;
		}
		break;

	case ARM:
		flight->arm();

		delay(5000); //delay for 5 seconds

		flightMode = TAKE_OFF; //go to next state
		break;

	case TAKE_OFF:
		if(abs(flight->goToAltitude(3))<Z_MAX_ERROR){
			flightMode=SET_NEXT_BUCKET;
		}
		else{
			//do nothing
		}
		break;

	case SET_NEXT_BUCKET:
		//8 buckets around each ring, 45 degrees apart
		//4 rings, 10 feet apart.
		//first bucket shall be to the right

		bucketIndex++;
		bucketPolarTheta = 45 * (bucketIndex-1)%9;
		if(bucketPolarTheta==0){
			bucketPolarRadius = bucketPolarRadius+10;
		}

		if(bucketPolarRadius == 50){
			flightMode = RETURN_TO_CENTER;
			break;
		}

		targetBucketX = bucketPolarRadius * cos(bucketPolarTheta);
		targetBucketY = bucketPolarRadius * sin(bucketPolarTheta);

		flightMode = FLY_TO_BUCKET;
		break;

	case FLY_TO_BUCKET:
		if(abs(flight->goToPosition(targetBucketX,targetBucketY))<XY_MAX_ERROR){
			flightMode=RECORD_PHOTO_AND_COORDINATES;
		}
		else{
			//do nothing
		}
		break;

	case RECORD_PHOTO_AND_COORDINATES:

		//magic happnens

		flightMode = SET_NEXT_BUCKET;
		break;

	case RETURN_TO_CENTER:
		if(abs(flight->goToPosition(0,0))<XY_MAX_ERROR){
			flightMode=LAND;
		}
		else{
			//do nothing
		}
		break;

	case LAND:
		if(abs(flight->goToAltitude(0))<Z_MAX_ERROR){
			flightMode=SET_NEXT_BUCKET;
		}
		else{
			//do nothing
		}
		break;

	case DISARM:
		flight->disarm();

		delay(5000); //delay for 5 seconds

		flightMode = EMERGENCY_STOP; //go to next state
		break;

	case EMERGENCY_STOP:
		//do nothing
		break;
	}

}




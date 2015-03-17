#include "config.h"
#include <SPI.h>
#include <WiFi.h>
#include <HardwareSerial.h>
#include <Adafruit_GPS.h>

bool usingInterrupt = true;

//variable declarations
double homePositionLat;
double homePositionLon;
bool homeSet = false;

double relativeY;
double relativeX;


//funcion prototypes
void setHomePosition();
void updateRelativePosition();


//Select the serial
//SoftwareSerial gpsSerial(2,3);
HardwareSerial gpsSerial = Serial1;

Adafruit_GPS GPS(&gpsSerial);



void setup()
{


	GPS.begin(9600);
	GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
	GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);

	setHomePosition();

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

	if (GPS.newNMEAreceived()) {
		if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
			return;  // we can fail to parse a sentence in which case we should just wait for another
	}
	if (timer > millis())  timer = millis();

	updateRelativePosition();

	//Add your repeated code here
}


void setHomePosition()
{
	if (!homeSet){
  homePositionLat = GPS.latitude;
  homePositionLon = GPS.longitude;
  homeSet = true;
	}
}


void updateRelativePosition()
{

  if(homeSet){
    relativeY = (GPS.latitude - homePositionLat)*110575;
    relativeX = (GPS.longitude - homePositionLon)*111303;
  }
  else if (!homeSet){
    Serial.println("home position not set");
  }
}




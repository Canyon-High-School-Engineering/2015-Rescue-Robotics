/*
 * RelativePositionController.cpp
 *
 *  Created on: Mar 18, 2015
 *      Author: Seth Itow
 */
#include "RelativePositionController.h"

// Overloaded contstructor to allow a specific home position to be
// set. Otherwise, the home coordinates to 0,0,0
RelativePositionController::RelativePositionController() {
	homePositionLat = 0;
	homePositionLon = 0;
	homePositionAlt = 0;
	currentLat = 0;
	currentLon = 0;
	currentAlt = 0;
	relativeX = 0;
	relativeY = 0;
	relativeZ = 0;
	homeSet = false;
}

RelativePositionController::RelativePositionController(float lat, float lon, float alt) {
	homePositionLat = lat;
	homePositionLon = lon;
	homePositionAlt = alt;
	currentLat = 0;
	currentLon = 0;
	currentAlt = 0;
	relativeX = 0;
	relativeY = 0;
	relativeZ = 0;
	homeSet = true;
}

RelativePositionController::~RelativePositionController() {
	// TODO Auto-generated destructor stub
}

// Set the home position to the current position
void RelativePositionController::setHomePosition(float lat, float lon, float alt)
{
	if (!homeSet){
  homePositionLat = lat;
  homePositionLon = lon;
  homePositionAlt = alt;
  homeSet = true;
	}
}

//update the relative position based on raw GPS coordinates and pre-set home position
void RelativePositionController::updateRelativePosition(float lat, float lon, float alt)
{
	currentLat = lat;
	currentLon = lon;
	currentAlt = alt;

  if(homeSet){
    relativeY = (lat - homePositionLat)*110575; 
    relativeX = (lon - homePositionLon)*111303;
    relativeZ = alt - homePositionAlt;
  }
  else if (!homeSet){
 // Serial.println("home position not set");
  }
}


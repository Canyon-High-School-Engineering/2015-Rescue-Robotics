/*
 * RelativePositionController.cpp
 *
 *  Created on: Mar 18, 2015
 *      Author: Seth
 */
#include "config.h"
#include "RelativePositionController.h"

RelativePositionController::RelativePositionController() {
	homePositionLat = 0;
	homePositionLon = 0;
	homePositionAlt = 0;
	relativeX = 0;
	relativeY = 0;
	relativeZ = 0;
	homeSet = false;
}

RelativePositionController::RelativePositionController(float lat, float lon, float alt) {
	homePositionLat = lat;
	homePositionLon = lon;
	homePositionAlt = alt;
	relativeX = 0;
	relativeY = 0;
	relativeZ = 0;
	homeSet = true;
}

RelativePositionController::~RelativePositionController() {
	// TODO Auto-generated destructor stub
}


void RelativePositionController::setHomePosition(float lat, float lon, float alt)
{
	if (!homeSet){
  homePositionLat = lat;
  homePositionLon = lon;
  homePositionAlt = alt;
  homeSet = true;
	}
}

void RelativePositionController::updateRelativePosition(float lat, float lon, float alt)
{

  if(homeSet){
    relativeY = (lat - homePositionLat)*110575;
    relativeX = (lon - homePositionLon)*111303;
    relativeZ = alt - homePositionAlt;
  }
  else if (!homeSet){
 // Serial.println("home position not set");
  }
}

double RelativePositionController::getRelY()
{
	return relativeY;
}
double RelativePositionController::getRelX()
{
	return relativeX;
}
double RelativePositionController::getRelZ()
{
	return relativeZ;
}

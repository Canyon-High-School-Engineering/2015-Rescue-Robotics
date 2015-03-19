/*
 * RelativePositionController.cpp
 *
 *  Created on: Mar 18, 2015
 *      Author: Seth
 */

#include "RelativePositionController.h"

RelativePositionController::RelativePositionController() {
	homePositionLat = 0;
	homePositionLon = 0;
	relativeX = 0;
	relativeY = 0;
	homeSet = false;
}

RelativePositionController::RelativePositionController(float lat, float lon) {
	homePositionLat = 0;
	homePositionLon = 0;
	relativeX = 0;
	relativeY = 0;
	homeSet = false;
}

RelativePositionController::~RelativePositionController() {
	// TODO Auto-generated destructor stub
}


void RelativePositionController::setHomePosition(float lat, float lon)
{
	if (!homeSet){
  homePositionLat = lat;
  homePositionLon = lon;
  homeSet = true;
	}
}

void RelativePositionController::updateRelativePosition(float lat, float lon)
{

  if(homeSet){
    relativeY = (lat - homePositionLat)*110575;
    relativeX = (lon - homePositionLon)*111303;
  }
  else if (!homeSet){
   // Serial.println("home position not set");
  }
}

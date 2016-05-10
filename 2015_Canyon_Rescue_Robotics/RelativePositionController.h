/*
 * RelativePositionController.h
 *
 *  Created on: Mar 18, 2015
 *      Author: Seth Itow
 */

#ifndef RELATIVEPOSITIONCONTROLLER_H_
#define RELATIVEPOSITIONCONTROLLER_H_

#include "config.h"



class RelativePositionController {
	//variable declarations

private:
	double homePositionLat; //home latitude in degrees
	double homePositionLon; //home longitude in degrees
	double homePositionAlt; //home altitude in meters
	bool homeSet;			//is the home position currently set?

	double currentLat;
	double currentLon;
	double currentAlt;

	double relativeY; // y position in meters
	double relativeX; // x position in meters
	double relativeZ; // z position in meters


public:

	//Function prototypes
	RelativePositionController(); // default constructor
	RelativePositionController(float lat, float lon, float alt);
	virtual ~RelativePositionController(); //destructor

	void setHomePosition(float lat, float lon, float alt);
	void updateRelativePosition(float lat, float lon, float alt);


//getters for absolute position
	double getCurrentAlt() const {
		return currentAlt;
	}

	double getCurrentLat() const {
		return currentLat;
	}

	double getCurrentLon() const {
		return currentLon;
	}

//getters for relative position
	double getRelativeX() const {
		return relativeX;
	}

	double getRelativeY() const {
		return relativeY;
	}

	double getRelativeZ() const {
		return relativeZ;
	}
};

#endif /* RELATIVEPOSITIONCONTROLLER_H_ */

/*
 * RelativePositionController.h
 *
 *  Created on: Mar 18, 2015
 *      Author: Seth
 */

#ifndef RELATIVEPOSITIONCONTROLLER_H_
#define RELATIVEPOSITIONCONTROLLER_H_

class RelativePositionController {
	//variable declarations
	double homePositionLat; //home latitude in degrees
	double homePositionLon; //home longitude in degrees
	double homePositionAlt; //home altitude in meters
	bool homeSet = false;


public:
	//variable declarations
	double relativeY; //  y position in meters
	double relativeX; // x position in meters
	double relativeZ; // z position in meters

	//Function prototypes
	RelativePositionController(); // default constructor
	RelativePositionController(float lat, float lon, float alt);
	virtual ~RelativePositionController(); //destructor

	void setHomePosition(float lat, float lon, float alt);
	void updateRelativePosition(float lat, float lon, float alt);
};

#endif /* RELATIVEPOSITIONCONTROLLER_H_ */

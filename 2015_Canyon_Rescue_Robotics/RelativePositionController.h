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
	double homePositionLat;
	double homePositionLon;
	double homePositionAlt;
	bool homeSet = false;


public:
	//variable declarations
	double relativeY;
	double relativeX;
	double relativeZ;
	//Function prototypes

	RelativePositionController(); // default constructor
	RelativePositionController(float lat, float lon, float alt);
	virtual ~RelativePositionController(); //destructor

	void setHomePosition(float lat, float lon, float alt);
	void updateRelativePosition(float lat, float lon, float alt);
};

#endif /* RELATIVEPOSITIONCONTROLLER_H_ */

/*
 * RelativePositionController.h
 *
 *  Created on: Mar 18, 2015
 *      Author: Seth
 */

class RelativePositionController {
	//variable declarations
	double homePositionLat;
	double homePositionLon;
	bool homeSet = false;


public:
	//variable declarations
	double relativeY;
	double relativeX;
	//funcion prototypes

	RelativePositionController(); // default constructor
	RelativePositionController(float lat, float lon);
	virtual ~RelativePositionController(); //destructor

	void setHomePosition(float lat, float lon);
	void updateRelativePosition(float lat, float lon);
};

/*
 * VictimLoggerController.h
 *
 *  Created on: May 11, 2015
 *      Author: Seth
 */

#include "config.h"

#include <SPI.h>
#include <SD.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <Adafruit_VC0706.h>

#include "RelativePositionController.h"
#include "FlightController.h"

#ifndef VICTIMLOGGERCONTROLLER_H_
#define VICTIMLOGGERCONTROLLER_H_

class VictimLoggerController {

private:

	RelativePositionController * relativePosition;

	Adafruit_VC0706 * cam;

	// delcare variables
	int bucketIndex;
	  int victimIndex;
	  double relY;
	  double relX;
	  double time;
	  double lat;
	  double lon;
	  String filename;

	  void getInfoToWriteToFile();
	  void appendInfoToFile();
	  void takePicture();

	  //double to string function prototype
	  String double2string(double n, int ndec);
public:
	VictimLoggerController(RelativePositionController * RelativePosition);
	virtual ~VictimLoggerController();
};

#endif /* VICTIMLOGGERCONTROLLER_H_ */

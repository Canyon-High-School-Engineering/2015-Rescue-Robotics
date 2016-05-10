/*
 * FlightController.h
 *
 *  Created on: Apr 10, 2015
 *      Author: Seth Itow
 */
#ifndef FLIGHTCONTROLLER_H_
#define FLIGHTCONTROLLER_H_

#include <Arduino.h>
#include <PID_v1.h>
#include <Servo.h>
#include "RelativePositionController.h"
#include "config.h"

class FlightController {

private:

	RelativePositionController * relativePosition;

	//declare functions
	void pitchPower(double power);
	void rollPower(double power);
	void throttlePower(double power);

	// Instantiate Servos
	Servo yawServo;
	Servo throttleServo;
	Servo pitchServo;
	Servo rollServo;

	// Instantiate PID controllers
	PID * throttlePID;
	PID * pitchPID;
	PID * rollPID;



	//Declare PID variables
	//Each PID controller seems to want its own set of variables
	double throttleInput = 0;
	double throttleOutput = 0;
	double throttleSetpoint = 0;
	double throttleError = 0;

	double pitchInput = 0;
	double pitchOutput = 0;
	double pitchSetpoint = 0;
	double pitchError = 0;

	double rollInput = 0;
	double rollOutput = 0;
	double rollSetpoint = 0;
	double rollError = 0;

	double xyError = 0;


public:
	FlightController(RelativePositionController *RelativePosition); // constructor
	virtual ~FlightController(); //destructor

	// arm and disarm
	void arm();
	void disarm();

	void allZero();

	// go-to commands
	double goToAltitude(double targetZ);
	double goToPosition(double targetX, double targetY);



};

#endif /* FLIGHTCONTROLLER_H_ */

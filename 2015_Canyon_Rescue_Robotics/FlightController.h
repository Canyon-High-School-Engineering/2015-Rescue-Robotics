/*
 * FlightController.h
 *
 *  Created on: Apr 10, 2015
 *      Author: Seth
 */

#ifndef FLIGHTCONTROLLER_H_
#define FLIGHTCONTROLLER_H_

class FlightController {


public:
	FlightController(); // constructor
	virtual ~FlightController(); //destructor

	// arm and disarm
	void arm();
	void disarm();

	void allZero();

	// go-to commands
	double goToAltitude(double targetZ);
	double goToPosition(double targetX, double targetY);






private:

	//declare functions
	void pitchPower(double power);
	void rollPower(double power);
	void throttlePower(double power);

	// Instantiate Servos
	Servo yawServo;
	Servo throttleServo;
	Servo pitchServo;
	Servo rollServo;

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


	// Instantiate PID controllers
	PID throttlePID = new PID(&throttleInput, &throttleOutput, &throttleSetpoint,.5,.1,0, DIRECT);
	PID pitchPID = new PID(&pitchInput, &pitchOutput, &pitchSetpoint,PITCH_PID_K,PITCH_PID_I,PITCH_PID_D, DIRECT);
	PID rollPID = new PID(&rollInput, &rollOutput, &rollSetpoint,ROLL_PID_K,ROLL_PID_I,ROLL_PID_D, DIRECT);

};

#endif /* FLIGHTCONTROLLER_H_ */

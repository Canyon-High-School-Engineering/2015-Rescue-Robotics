

/*
 * FlightController.cpp
 *
 *  Created on: Apr 10, 2015
 *      Author: Seth Itow
 */

#include "FlightController.h"


FlightController::FlightController(RelativePositionController *RelativePosition) {


	relativePosition = RelativePosition; //pull instance of relative postion controller

	// TODO make this use less ram, probably by only instantiating one instance of the PID controller

	// Instantiate PID controllers
	throttlePID = new PID(&throttleInput, &throttleOutput, &throttleSetpoint,THROTTLE_PID_K,THROTTLE_PID_I,THROTTLE_PID_D, DIRECT);
	pitchPID = new PID(&pitchInput, &pitchOutput, &pitchSetpoint,PITCH_PID_K,PITCH_PID_I,PITCH_PID_D, DIRECT);
	rollPID = new PID(&rollInput, &rollOutput, &rollSetpoint,ROLL_PID_K,ROLL_PID_I,ROLL_PID_D, DIRECT);

	//set PID output limits
	throttlePID->SetOutputLimits(-100, 100);
	pitchPID->SetOutputLimits(-100, 100);
	rollPID->SetOutputLimits(-100, 100);

	//set PID mode
	throttlePID->SetMode(AUTOMATIC);
	pitchPID->SetMode(AUTOMATIC);
	rollPID->SetMode(AUTOMATIC);

	//attach servos
	yawServo.attach(YAW_PIN);
	throttleServo.attach(THROTTLE_PIN);
	pitchServo.attach(PITCH_PIN);
	rollServo.attach(ROLL_PIN);

	//zero all servos
	yawServo.writeMicroseconds(1500);
	throttleServo.writeMicroseconds(1500);
	pitchServo.writeMicroseconds(1500);
	rollServo.writeMicroseconds(1500);

}

FlightController::~FlightController() {
	// TODO Auto-generated destructor stub
}

// Arms and disarms the flight controller controller 
void FlightController::arm(){
	throttleServo.writeMicroseconds(1000);
	yawServo.writeMicroseconds(1000);
	delay(6000);
	allZero();
}

void FlightController::disarm(){
	throttleServo.writeMicroseconds(1000);
	yawServo.writeMicroseconds(2000);
	delay(6000);
	allZero();
}

//Sets all PWM outputs to the center of the throw.
//Equivalent of moving all sticks to their center position
void FlightController::allZero(){
	yawServo.writeMicroseconds(1500);
	throttleServo.writeMicroseconds(1500);
	pitchServo.writeMicroseconds(1500);
	rollServo.writeMicroseconds(1500);
}


// The goTo functions run a PID controller to move the airframe
// to a specific position. they return the error after 1 PID cycle.
// The functions should be run continuously at main loop speed until
// the error is within an acceptable range.
double FlightController::goToAltitude(double targetZ){

	throttleSetpoint = targetZ;
	throttleInput = relativePosition->getRelativeZ();
	throttlePID->Compute();
	throttlePower(throttleOutput);
	throttleError = throttleSetpoint - throttleInput;

	return throttleError;

}

double FlightController::goToPosition(double targetX, double targetY){

	rollSetpoint = targetX;
	rollInput = relativePosition->getRelativeY();
	rollPID->Compute();
	rollPower(rollOutput);
	rollError = rollSetpoint - rollInput;

	pitchSetpoint = targetY;
	pitchInput = relativePosition->getRelativeY();
	pitchPID->Compute();
	pitchPower(pitchOutput);
	pitchError = pitchSetpoint - pitchInput;

	xyError = sqrt(sq(rollError) + sq(pitchError));

	return xyError;

}

// These functions map a power value between -100 and 100 to the correct
// microsecond values to write to the PWM outputs.
void FlightController::throttlePower(double power){

	throttleServo.writeMicroseconds(map(power,-100,100,THROTTLE_MIN,THROTTLE_MAX));

}
void FlightController::pitchPower(double power){

	rollServo.writeMicroseconds(map(power,-100,100,PITCH_MIN,PITCH_MAX));
}
void FlightController::rollPower(double power){

	pitchServo.writeMicroseconds(map(power,-100,100,ROLL_MIN,ROLL_MAX));

}





#include "config.h"

#include <Servo.h>
#include <SPI.h>
#include <WiFi.h>
#include <SoftwareSerial.h>
#include <Adafruit_VC0706.h>

// ********************************************* INITIALIZE WIFI *********************************************
char ssid[] = "CanyonEngineering"; //  your network SSID (name)
char pass[] = "Comanches";    // your network password (use for WPA, or use as key for WEP)

int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

WiFiServer server(23);

boolean alreadyConnected = false; // whether or not the client was connected previously

// ********************************************* INITIALIZE SERVO OBJECTS *********************************************
	Servo yawServo;
	Servo throttleServo;
	Servo pitchServo;
	Servo rollServo;

// ********************************************* INITIALIZE CAMERA *********************************************
//SoftwareSerial cameraconnection = SoftwareSerial(CAMERA_SERIAL_RX_PIN, CAMERA_SERIAL_TX_PIN); // RX, TX
//SoftwareSerial cameraconnection = SoftwareSerial(2, 3);

// ********************************************* INITIALIZE STATE MACHINE ENUM *********************************************
enum FlightModeEnum {WAIT_FOR_TRIGGER,
	ARM,TAKE_OFF,
	FLY_TO_BUCKET,RECORD_PHOTO_AND_COORDINATES,
	SET_NEXT_BUCKET,RETURN_TO_CENTER,
	LAND,DISARM,
	EMERGENCY_STOP};

FlightModeEnum flightMode = WAIT_FOR_TRIGGER;

long now = 0;
long last = 0;
bool timeForUpdate = false;

void setup() {
  // ********************************************* CONNECT TO WIFI NETWORK *********************************************
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if ( fv != "1.1.0" )
    Serial.println("Please upgrade the firmware");

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // start the server:
  server.begin();
  // you're connected now, so print out the status:
  printWifiStatus();
  
  // ********************************************* ATTACH SERVOS *********************************************
  
  	yawServo.attach(YAW_PIN);
	throttleServo.attach(THROTTLE_PIN);
	pitchServo.attach(PITCH_PIN);
	rollServo.attach(ROLL_PIN);
  
  // ********************************************* INITIALIZE GPS *********************************************
  
  
  
  
  sendLineToConsole("Quadcopter begin");
}


void loop() {
  

  
  
  
  // ********************************************* HANDLE WIFI CLIENTS *********************************************
  // wait for a new client:
  WiFiClient client = server.available();

  // when the client sends the first byte, say hello:
  if (client) {
    if (!alreadyConnected) {
      // clead out the input buffer:
      client.flush();
      Serial.println("We have a new client");
      client.println("Welcome new client");
      alreadyConnected = true;
    }
  }
  
  
  
  // ********************************************* MAIN STATE MACHINE *********************************************
    now = millis();
    if(now - last > 1500) {
      timeForUpdate = true;
      last = now;
    }
    else timeForUpdate = false;
  
  switch(flightMode) {

	case WAIT_FOR_TRIGGER:
if(timeForUpdate) sendLineToConsole("waiting for trigger");
		if(!digitalRead(AUTOPILOT_ACTIVE_PIN)){
  sendLineToConsole("trigger received");
			flightMode = ARM;
sendLineToConsole("switching to arm");
		}
		break;

	case ARM:
sendLineToConsole("arming");
	         throttleServo.writeMicroseconds(1000);
	         yawServo.writeMicroseconds(2000);
	         delay(6000);
sendLineToConsole("armed");
sendLineToConsole("spinning up rotors");
                FlightallZero();
		delay(5000); //delay for 5 seconds

sendLineToConsole("switching to takeoff");
		flightMode = TAKE_OFF; //go to next state
		break;

	case TAKE_OFF:

sendLineToConsole("in take off mode");
sendLineToConsole("increasing throttle");
throttleServo.writeMicroseconds(2000);
delay(5000);
sendLineToConsole("zeroing throttle");
throttleServo.writeMicroseconds(1000);
delay(1000);

flightMode = LAND;


		break;

	case SET_NEXT_BUCKET:
sendLineToConsole("case set next bucket");
		//8 buckets around each ring, 45 degrees apart
		//4 rings, 10 feet apart.
		//first bucket shall be to the right

//		bucketIndex++;
//		bucketPolarTheta = 45 * (bucketIndex-1)%9;
//		if(bucketPolarTheta==0){
//			bucketPolarRadius = bucketPolarRadius+10;
//		}
//
//		if(bucketPolarRadius == 50){
//			flightMode = RETURN_TO_CENTER;
//			break;
//		}
//
//		targetBucketX = bucketPolarRadius * cos(bucketPolarTheta);
//		targetBucketY = bucketPolarRadius * sin(bucketPolarTheta);

		flightMode = FLY_TO_BUCKET;
		break;

	case FLY_TO_BUCKET:
sendLineToConsole("case: fly to bucket");
//		if(abs(flight.goToPosition(targetBucketX,targetBucketY))<XY_MAX_ERROR){
//			flightMode=RECORD_PHOTO_AND_COORDINATES;
//		}
//		else{
//			//do nothing
//		}

		break;

	case RECORD_PHOTO_AND_COORDINATES:

		//magic happnens

		flightMode = SET_NEXT_BUCKET;
		break;

	case RETURN_TO_CENTER:
// do nothing

		break;

	case LAND:

sendLineToConsole("in land mode");
sendLineToConsole("decreasing throttle");
throttleServo.writeMicroseconds(1200);
delay(10000);
sendLineToConsole("zeroing throttle");
throttleServo.writeMicroseconds(1000);
delay(1000);

		break;

	case DISARM:
		
	throttleServo.writeMicroseconds(1000);
	yawServo.writeMicroseconds(1000);
	delay(6000);
	FlightallZero();
		delay(5000); //delay for 5 seconds
throttleServo.writeMicroseconds(1000);

		flightMode = EMERGENCY_STOP; //go to next state
		break;

	case EMERGENCY_STOP:
		//do nothing
		break;
	}
  

  
}

void FlightallZero(){
	//zero all servos
	yawServo.writeMicroseconds(1500);
	throttleServo.writeMicroseconds(1500);
	pitchServo.writeMicroseconds(1500);
	rollServo.writeMicroseconds(1500);
}



void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}


void sendLineToConsole(String theMessage) {
#ifdef WiFiDEBUGGING
server.println(theMessage);
#else
Serial.println(theMessage);
#endif
}


void sendToConsole(String theMessage) {
#ifdef WiFiDEBUGGING
server.print(theMessage);
#else
Serial.print(theMessage);
#endif
}

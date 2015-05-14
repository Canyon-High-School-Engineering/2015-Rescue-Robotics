/*
 * VictimLoggerController.cpp
 *
 *  Created on: May 11, 2015
 *      Author: Seth
 */

#include "VictimLoggerController.h"

VictimLoggerController::VictimLoggerController(RelativePositionController * RelativePosition) {

// create relativePosition from passed pointer
	relativePosition = RelativePosition;

// initalize variables
	getInfoToWriteToFile();

//initialize SD card
	  Serial.print("Initializing SD card...");
	  // make sure that the default chip select pin is set to
	  // output, even if you don't use it:
	  pinMode(10, OUTPUT);

	  // see if the card is present and can be initialized:
	  if (!SD.begin(SD_CARD_CS_PIN)) {
	    Serial.println("Card failed, or not present");
	    // don't do anything more:
	    return;
	  }
	  Serial.println("card initialized.");

// initialize camera
	  SoftwareSerial cameraConnection = SoftwareSerial(CAMERA_SERIAL_RX_PIN, CAMERA_SERIAL_TX_PIN); //Rx pin, Tx pin
	  cam = new Adafruit_VC0706(&cameraConnection);
	  //Adafruit_VC0706 cam =

	  if (cam->begin()) {
	      Serial.println("Camera Found");
	    } else {
	      Serial.println("No camera found?");
	      return;
	    }

	  cam->setImageSize(VC0706_640x480);

}

VictimLoggerController::~VictimLoggerController() {
	// TODO Auto-generated destructor stub
}


void VictimLoggerController::getInfoToWriteToFile() {

	  victimIndex = bucketIndex;
	  relY = relativePosition->getRelativeY();
	  relX = relativePosition->getRelativeX();
	  time = millis()/60000;
	  lat = relativePosition->getCurrentLat();
	  lon = relativePosition->getCurrentLon();
	  filename = "placeholder.txt";
}

void VictimLoggerController::takePicture()
{

if (! cam->takePicture())
    Serial.println("Failed to snap!");
  else
    Serial.println("Picture taken!");

  // Create an image with the name IMAGExx.JPG
  char filename[13];
  strcpy(filename, "IMAGE00.JPG");
  for (int i = 0; i < 100; i++) {
    filename[5] = '0' + i/10;
    filename[6] = '0' + i%10;
    // create if does not exist, do not open existing, write, sync after write
    if (! SD.exists(filename)) {
      break;
    }
  }

  File imgFile = SD.open(filename, FILE_WRITE);

    // Get the size of the image (frame) taken
    uint16_t jpglen = cam->frameLength();
    Serial.print("Storing ");
    Serial.print(jpglen, DEC);
    Serial.print(" byte image.");

    int32_t time = millis();
    pinMode(8, OUTPUT);
    // Read all the data up to # bytes!
    byte wCount = 0; // For counting # of writes
    while (jpglen > 0) {
      // read 32 bytes at a time;
      uint8_t *buffer;
      uint8_t bytesToRead = min(32, jpglen); // change 32 to 64 for a speedup but may not work with all setups!
      buffer = cam->readPicture(bytesToRead);
      imgFile.write(buffer, bytesToRead);
      if(++wCount >= 64) { // Every 2K, give a little feedback so it doesn't appear locked up
        Serial.print('.');
        wCount = 0;
      }
      //Serial.print("Read ");  Serial.print(bytesToRead, DEC); Serial.println(" bytes");
      jpglen -= bytesToRead;
    }
    imgFile.close();

    Serial.println("done!");

  }

void VictimLoggerController::appendInfoToFile() {
// Creating data for strings to pull for displayed information.
String dataString0 = "***** Victim" + String(victimIndex) + " *****";
String dataString1 = "victim identified" + double2string(time,0) + "seconds into flight.";
String dataString2 = "relative coordinates" + double2string(relX,2) + "," + double2string(relY,2);
String dataString3 = "GPS Coordinates :" + double2string(lat,5) + "," + double2string(lon,5);
String dataString4 = "Photo:" + filename;
String dataString5 = "********* END **********";

// Logging all data together for us to see after we look at SD card.
// open the file. note that only one file can be open at a time,
// so you have to close this one before opening another.
File dataFile = SD.open("victims.txt", FILE_WRITE);

// if the file is available, write to it:
if (dataFile) {
  dataFile.println(dataString0);
  dataFile.println(dataString1);
  dataFile.println(dataString2);
  dataFile.println(dataString3);
  dataFile.println(dataString4);
  dataFile.println(dataString5);
  dataFile.println();
  dataFile.close();
  // print to the serial port too:
  Serial.println(dataString0);
  Serial.println(dataString1);
  Serial.println(dataString2);
  Serial.println(dataString3);
  Serial.println(dataString4);
  Serial.println(dataString5);
  Serial.println();
}
// if the file isn't open, pop up an error:
else {
  Serial.println("error opening victims.txt");
}
}


String VictimLoggerController::double2string(double n, int ndec) {
    String r = "";

    int v = n;
    r += n;     // whole number part
    r += '.';   // decimal point
    int i;
    for (i=0;i<ndec;i++) {
        // iterate through each decimal digit for 0..ndec
        n -= v;
        n *= 10;
        v = n;
        r += v;
    }

    return r;
}

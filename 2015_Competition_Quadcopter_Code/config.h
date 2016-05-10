
// comment out to switch to serial debugging
#define WiFiDEBUGGING



// PPM out pins for servo attach
#define YAW_PIN 8
#define THROTTLE_PIN 9
#define PITCH_PIN 6
#define ROLL_PIN 5

// Autopilot active trigger
#define AUTOPILOT_ACTIVE_PIN 42

// Slave Select Pins
#define SD_CARD_CS_PIN 4 //use pin 4 for wifi shield
#define WIFI_CS_PIN 10 //use pin ?? for wifi shield

// Soft Serial Pins
#define CAMERA_SERIAL_TX_PIN 14
#define CAMERA_SERIAL_RX_PIN 15
#define GPS_SERIAL_TX_PIN 2
#define GPS_SERIAL_RX_PIN 3

// flight parameters
#define SEARCH_ALTITUDE 3 // cruise altitude in meters

// throttle PID constants
#define THROTTLE_PID_K .5
#define THROTTLE_PID_I .1
#define THROTTLE_PID_D 0

// pitch PID constants
#define PITCH_PID_K .5
#define PITCH_PID_I .1
#define PITCH_PID_D 0

// roll PID constants
#define ROLL_PID_K .5
#define ROLL_PID_I .1
#define ROLL_PID_D 0


//PID max error

#define Z_MAX_ERROR .2 //error in meters
#define XY_MAX_ERROR .282 // error in meters


// min/max servo ms values
#define THROTTLE_MIN 1000
#define THROTTLE_MAX 2000

#define PITCH_MIN 1000
#define PITCH_MAX 2000

#define ROLL_MIN 1000
#define ROLL_MAX 2000

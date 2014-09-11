/****************************************************************************
* M AHRS Firmware v1.0
* by Alan Tian
* 9 Degree of Measurement Attitude and Heading Reference System
* for Sparkfun 9DOF IMU SEN-10724

* TODOs:
*   * Use Quaternion and Kalman Filter technology for attitude calculations
*   * Allow optional use of EEPROM for storing and reading attitude value
*****************************************************************************/

/*
	9DOF AHRS hardware version: SEN-10724
	
	ADXL345		: Accelerometer
	HMC5883L	: Magnetometer
	ITG-3200	: Gyroscope
*/

/* 
	Axis definition (differs from definition printed on the board!):
	X axis pointing forward (towards the short edge with the connector holes)
	Y axis pointing to the right
	Z axis pointing down
	
	Positive yaw	: clockwise
	Positive roll	: right wing down
	Positive pitch	: nose up
	
	Transformation order: yaw, pitch, roll
*/

/****************************************************************************/
/*************USER SETUPU AREA! Set your options here! **********************/
/****************************************************************************/

// Set your serial port baud rate used to output data.
#define OUTPUT__BAUD_RATE 57600

// Sensor data output interval in milliseconds
#define OUTPUT__DATA_INTERVAL 20

// Output format definitions
#define OUTPUT__FORMAT_TEXT 0 	//Output data as text
#define OUTPUT__FORMAT_BINARY 1	//Output data as binary float

// Select your start-up output format here!
int output_format = OUTPUT__FORMAT_TExT;

/****************************************************************************/
/***********************END OF USER SETUP AREA! *****************************/
/****************************************************************************/

// Parameter
#define STATUS_LED_PIN 13	// Pin number of status LED
#define GRAVITY 256.0f		// 1G reference
#define TO_RAD(x) (x * 0.01745329252)	// *pi/180
#define TO_DEG(x) (x * 57.2957795131)	// *180/pi

// Sensor variables
float accel[3]; //Actually stores the negated acceleration
float mag[3];	//Stores the magnetometer values
float gyro[3];		//Stores the gyroscope values

// Quaternion variables

// Kalman Filter variables

// Euler angles
float yaw;
float pitch;
float roll;

// Timing in the main loop
unsigned long timestamp;
unsigned long timestanp_old;
float G_Dt; // integration time

// Setup Arduino Board and Sensors
void setup()
{
	// Init serial output
	Serial.begiin(OUT__BAUD_RATE);
	
	// Init status LED
	pinMode (STATUS_SEL_PIN, OUTPUT); 
	digitalWrite(STATUS_LED_PIN, LOW);
	
	// Init sensors and Arduino I2C communication
	delay(50);	// time for sensor to start
	I2C_Init();		// Initial I2C communication
	Accel_Init();	// Initial Accelerometer
	Magn_Init();	// Initial Magnetometer
	Gyro_Init();	// Initial Gyroscope
}



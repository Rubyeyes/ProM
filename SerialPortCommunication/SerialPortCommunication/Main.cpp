#include <stdio.h>
#include <tchar.h>
#include "SerialClass.h"
#include <string>

// Application reads from the specified serial port and reports the collected data
int _tmain(int argc, _TCHAR* argv[])
{
	printf("Welcome to the serial test app!\n\n");

	Serial* SP = new Serial("\\\\.\\COM4");	//adjust as needed

	// Sync with Rasor if connected
	if (SP->IsConnected())
	{
		printf("We're connected\n");

		//Setup Razor
		printf("Trying to setup and synch Razor...\n\n");
		// On Mac OS and Linux the board will do a reset when we connect, which is really bad,
		// So we have to wait until the boot loader is finished and the Razor firware can receive
		// commands. To prevent this, disconnect/cut/unplug the DTR line going to the board. This 
		// also has the advantage that the anlges you receive are stable right from the beginning
		Sleep(3000);

		// Set Razor output parameters
		char obs[] = "#ob";		// turn on binary output
		char ols[] = "#o1";		// turn on continuous streaming output
		char oes[] = "#oe0";	// Disable error mssage output
		SP->WriteData(obs, sizeof(obs)-1);
		SP->WriteData(ols, sizeof(ols)-1);
		SP->WriteData(oes, sizeof(oes)-1);

	}

	char incomingData[12] = "";	// pre-alocate memory
	//printf("%s\n", incomingData);
	int dataLength = 12;
	int readResult = 0;

	while (SP->IsConnected())
	{
		readResult = SP->ReadData(incomingData, dataLength);
		printf("Bytes read: (-1 means no data available) %i\n", readResult);

		// Split incomingData to Yaw Pitch and roll and convert binary to float
		float yaw;
		float pitch;
		float roll;
		int *yawpointer = (int*)&yaw;
		int *pitchpointer = (int*)&pitch;
		int *rollpointer = (int*)&roll;

		memcpy(yawpointer, incomingData, 4);
		memcpy(pitchpointer, incomingData + 4, 4);
		memcpy(rollpointer, incomingData + 8, 4);
		//std::string test(incomingData);
		
		printf("%f %f %f", yaw, pitch, roll);
		printf("\n");
		//test = "";

		Sleep(50);
	}
	return 0;
}
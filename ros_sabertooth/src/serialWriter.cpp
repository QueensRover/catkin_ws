#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <iostream>
#include <time.h>
#include <stdint.h>

#include "serialWriter.h"

using namespace std;

serialWriter::serialWriter() {
	serialSetup();
}

void serialWriter::open_port(void) {

	fd = open("/dev/serial0", O_RDWR | O_NOCTTY | O_NDELAY);

	if(fd == -1) //if port in unsuccessful
	{
	printf("open_port: Unable to open /dev/Serial0. \n");
	}
	else
	{
		fcntl(fd, F_SETFL, 0);
		printf("Port is open.\n");
	}
	return;
}//open_port

void serialWriter::configure_port(void) {

	struct termios port_settings;	//structure to store the port settings in

	cfsetispeed(&port_settings, B38400);	//setting baud rates
	cfsetospeed(&port_settings, B38400);

	port_settings.c_iflag = IGNBRK;
	port_settings.c_cflag = CS8 | CREAD | CLOCAL;	//alex changed the c and i flags to something he found on the internet and now it works
	port_settings.c_cc[VMIN] = 0;			//VMIN and VTIME make sure that non-blocking mode works for reading
	port_settings.c_cc[VTIME] = 0;

	tcsetattr(fd, TCSANOW, &port_settings);		//apply the settings to the port
	return;
}//configure_port

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void serialWriter::serialSetup() {

	open_port();
	configure_port();

	unsigned char setupByte = 170; //change this to corrispond to the right bit rate
	unsigned char setupBytes[] = {setupByte};
	write(fd,setupBytes,1);
	cout<<"Serial setup done."<<endl;
}//serialSetup

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned char sendBytes[4];

void serialWriter::serialWrite(uint16_t address, uint16_t command, uint16_t data) {
	uint16_t check = (address + command + data) & 127;
	sendBytes[0] = address;
	sendBytes[1] = command;
	sendBytes[2] =  data;
	sendBytes[3] = check;
	write(fd, sendBytes, 4);
}//serialWrite


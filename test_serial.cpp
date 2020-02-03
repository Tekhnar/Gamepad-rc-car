#include "serial_usb.h"
#include <stdio.h>

int main () {
	serial avr;
	avr.openPort ("/dev/ttyUSB1");
	avr.writeToPort ("Hello, world!\n");
	char buffer[20] = {};
	avr.readFromPort (buffer);
	printf ("Return: %s\n", buffer);
}


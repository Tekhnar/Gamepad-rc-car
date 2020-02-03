#include "gamepad_input.h"
#include "serial_usb.h"
#include <cstdio>

int main() {
	gamepad xbox;
	xbox.openGamepad ("/dev/input/js0");
	
	serial avr;
	avr.openPort ("/dev/ttyUSB1");
	while (1) {
		xbox.checkNewData ();
		printf ("Steering_wheel %d Brake %d Throtlle %d\n",
			xbox.data.steering_wheel, xbox.data.brake, xbox.data.throtlle);
	}
	return 0;
}


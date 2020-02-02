#include "gamepad_input.h"
#include <cstdio>

int main() {
	gamepad xbox;
	
	xbox.reverse_axes.steering_wheel = 1;
	xbox.reverse_axes.throtlle = 0;
	xbox.reverse_axes.brake = 1;
	
	xbox.openGamepad ("/dev/input/js0");
	
	while (1) {
		xbox.checkNewData ();
		printf ("Steering_wheel %3d Brake %3d Throtlle %3d\n", 
				xbox.data.steering_wheel, xbox.data.brake, xbox.data.throtlle);
	}
	return 0;
}


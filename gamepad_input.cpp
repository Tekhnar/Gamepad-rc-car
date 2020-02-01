#include "gamepad_input.h"


void gamepad::openGamepad (const char *device_name) {
	if (device_name == NULL) {
		printf ("Not received name of gamepad\n");
		assert (device_name != NULL);
	}

	int address = open (device_name, O_RDONLY | O_NONBLOCK); 
	//  That mean that we open file to write
	//  and read

	if (address < 0) {
		printf ("Could not locate gamepad device %s\n", device_name);
		assert (address >= 0);
	}
	
	file_descriptor_ = address;
}	

void gamepad::processEvent () {
	if (joystick_event_.type == 2) {
		if (joystick_event_.number == selected_axes.steering_wheel)
			data.steering_wheel = joystick_event_.value / 4;
		
		if (joystick_event_.number == selected_axes.throtlle)
			data.throtlle = joystick_event_.value / 4;
		
		if (joystick_event_.number == selected_axes.brake)
			data.brake = joystick_event_.value / 4;
	}
}

bool gamepad::checkNewData () {
	while  (read (file_descriptor_, 
			&joystick_event_,
			sizeof (joystick_event_) ) > 0) 
	{
    	processEvent();
    }	
}

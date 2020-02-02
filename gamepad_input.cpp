#include "gamepad_input.h"

gamepad::gamepad () :
	file_descriptor_ (-1) {
	selected_axes.steering_wheel = 0;
	selected_axes.throtlle = 5;
	selected_axes.brake = 2;
	
	data = {(car_type) (MAX_VALUE_CAR_TYPE / 2),0,0};
	reverse_axes = {0,0,0};
}

void gamepad::openGamepad (const char *device_name) {
	if (device_name == NULL) {
		printf ("Not received name of gamepad\n");
		assert (device_name != NULL);
	}

	int address = open (device_name, O_RDONLY | O_NONBLOCK); 
	//  That mean that we open file to write and read

	if (address < 0) {
		printf ("Could not locate gamepad device %s\n", device_name);
		assert (address >= 0);
	}
	
	file_descriptor_ = address;
	
	if (reverse_axes.throtlle != 0)
		data.throtlle = MAX_VALUE_CAR_TYPE;
	if (reverse_axes.brake != 0)
		data.brake = MAX_VALUE_CAR_TYPE;
	
}	

void gamepad::processEvent () {
	if (joystick_event_.type == 2) {
		if (joystick_event_.number == selected_axes.steering_wheel) {
			data.steering_wheel = (joystick_event_.value + MAX_VALUE_INPUT_TYPE) / REDUCTION_RATIO;
			if (reverse_axes.steering_wheel != 0)
				data.steering_wheel = MAX_VALUE_CAR_TYPE - data.steering_wheel;
		}
		
		if (joystick_event_.number == selected_axes.throtlle) {
			data.throtlle = (joystick_event_.value + MAX_VALUE_INPUT_TYPE) / REDUCTION_RATIO;
			if (reverse_axes.throtlle != 0)
				data.throtlle = MAX_VALUE_CAR_TYPE - data.throtlle;
		}
			
		if (joystick_event_.number == selected_axes.brake) {
			data.brake = (joystick_event_.value + MAX_VALUE_INPUT_TYPE) / REDUCTION_RATIO;
			if (reverse_axes.brake != 0)
				data.brake = MAX_VALUE_CAR_TYPE - data.brake;
		}
	}
}

bool gamepad::checkNewData () {
	while  (read (file_descriptor_, 
			&joystick_event_,
			sizeof (joystick_event_) ) > 0) 
	{
    	processEvent();
    }	
    return true;
}

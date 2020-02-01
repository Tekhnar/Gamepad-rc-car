#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/joystick.h>
#include <assert.h>

struct gamepad_data {
	char steering_wheel;
	char throtlle;
	char brake;
};

struct gamepad {
	gamepad_data data;
	gamepad_data selected_axes;
	
	void openGamepad (const char *device_name);
	void processEvent ();
	bool checkNewData (); 
	

	private:	
	js_event joystick_event_;
	int file_descriptor_;
	
};

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/joystick.h>
#include <assert.h>

typedef unsigned char car_type;
typedef short input_type;

struct gamepad_data {
	car_type steering_wheel;
	car_type throtlle;
	car_type brake;
};

struct gamepad {
	gamepad_data data;
	gamepad_data selected_axes;
	gamepad_data reverse_axes;
	
	void openGamepad (const char *device_name);
	void processEvent ();
	bool checkNewData (); 
	
	gamepad ();

	private:	
	js_event joystick_event_;
	int file_descriptor_;
	
	
	const car_type MAX_VALUE_CAR_TYPE = (1 << (8 * sizeof (car_type)) ) - 1; 
	
	const int REDUCTION_RATIO = 256 / sizeof (car_type);
	//  REDUCTION_RATIO automatically recalculate final range for car_type
	
	const input_type MAX_VALUE_INPUT_TYPE = (1 << (8 * sizeof (input_type) - 1)) - 1;
	
};

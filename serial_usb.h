#ifndef H_SERIAL_USB

#define H_SERIAL_USB

// C library headers
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()

void comparisonWithZero (void* suspect, const char *text_error);
struct serial {
	
	termios teletype;
	
	void openPort (const char *name_device, int open_flag = O_RDWR);
	void saveTeletypeSettings ();
	
	void writeToPort (char *data_for_sending);
	void writeToPort (const char *data_for_sending);
	
	int readFromPort (char *read_buffer);
	// Return the number of bytes read
	
	private:
	
	void defaultTeletypeSettings ();
		
	int serial_port_;
	
};

#endif 


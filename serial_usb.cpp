#include "serial_usb.h"

//--------------------overload-------------------------//
void comparisonWithZero (void* suspect, const char *text_error) {
	if (suspect == NULL) {		
		printf ("%s\n", text_error);
		abort ();
	}
}

void comparisonWithZero (int suspect, const char *text_error) {
	comparisonWithZero ((void*) suspect, text_error);
}

void comparisonWithZero (char* suspect, const char *text_error) {
	comparisonWithZero ((void*) suspect, text_error);
}

void comparisonWithZero (const char* suspect, const char *text_error) {
	comparisonWithZero ((void*) suspect, text_error);
}
//--------------------overload-------------------------//


void serial::openPort (const char *name_device, int open_flag) {
	comparisonWithZero (name_device, "Incorrect name \"name_device\"!");
	
	serial_port_ = open (name_device, open_flag);
	//int serial_port = open("/dev/ttyUSB0", O_RDWR);
	
	comparisonWithZero (serial_port_, "Can't open file with this name_device!");
	
	if (tcgetattr (serial_port_, &teletype) != 0)
    	printf("Error %i from tcgetattr: %s\n", errno, strerror (errno));
    	
	defaultTeletypeSettings ();
	saveTeletypeSettings ();
}

void serial::defaultTeletypeSettings () {
	teletype.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
	teletype.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
	teletype.c_cflag |= CS8; // 8 bits per byte (most common)
	teletype.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
	teletype.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

	teletype.c_lflag &= ~ICANON;
	teletype.c_lflag &= ~ECHO; // Disable echo
	teletype.c_lflag &= ~ECHOE; // Disable erasure
	teletype.c_lflag &= ~ECHONL; // Disable new-line echo
	teletype.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
	teletype.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
	teletype.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

	teletype.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
	teletype.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
	// tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)
	// tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT ON LINUX)

	teletype.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
	teletype.c_cc[VMIN] = 0;

	// Set in/out baud rate to be 9600
	cfsetispeed (&teletype, B9600);
	cfsetospeed (&teletype, B9600);
}

void serial::saveTeletypeSettings () {
	if (tcsetattr (serial_port_, TCSANOW, &teletype) != 0) {
    	printf ("Error %i from tcsetattr: %s\n", errno, strerror (errno));
    	abort ();
    }
}

void serial::writeToPort (char *data_for_sending) {
	comparisonWithZero (data_for_sending, "Incorrect address of \"data_for_sending\"!");
	
	write (serial_port_, data_for_sending, strlen (data_for_sending));
}

void serial::writeToPort (const char *data_for_sending) {
	writeToPort ((char*) data_for_sending);
}

int serial::readFromPort (char *read_buffer) {
	return read (serial_port_, read_buffer, sizeof (char));
}

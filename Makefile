all: main.o gamepad_input.o serial_usb.o
	g++ main.o gamepad_input.o serial_usb.o -o game

test-serial: test_serial.o serial_usb.o
	g++ test_serial.o serial_usb.o -o test

test-gamepad: test_gamepad.o gamepad_input.o
	g++ test_gamepad.o gamepad_input.o -o test

test_gamepad.o: test_gamepad.cpp test_gamepad.h
	g++ test_gamepad.cpp -Wall -c -o test_gamepad.o
test_serial.o: test_serial.cpp serial_usb.h
	g++ test_serial.cpp -Wall -c -o test_serial.o

main.o: main.cpp gamepad_input.h serial_usb.h
	g++ main.cpp -c -Wall -o main.o
gamepad_input.o: gamepad_input.cpp gamepad_input.h
	g++ gamepad_input.cpp -Wall -c -o gamepad_input.o

serial_usb.o: serial_usb.h serial_usb.cpp
	g++ serial_usb.cpp -Wall -c -o serial_usb.o



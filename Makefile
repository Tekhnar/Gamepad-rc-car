all: main.o gamepad_input.o
	g++ main.o gamepad_input.o -o game

test-gamepad: test_gamepad.o gamepad_input.o
	g++ test_gamepad.o gamepad_input.o -o game

test_gamepad.o: test_gamepad.cpp
	g++ test_gamepad.cpp -Wall -c -o test_gamepad.o

main.o: main.cpp gamepad_input.h
	g++ main.cpp -c -Wall -o main.o
gamepad_input.o: gamepad_input.cpp gamepad_input.h
	g++ gamepad_input.cpp -Wall -c -o gamepad_input.o	

all: main.o gamepad_input.o
	g++ main.o gamepad_input.o -o game

main.o: main.cpp
	g++ main.cpp -c -o main.o
gamepad_input.o:
	g++ gamepad_input.cpp -c -o gamepad_input.o	

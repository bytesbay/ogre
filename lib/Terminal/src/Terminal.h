#include <Arduino.h>
#include <Core.h>

#ifndef TERMINAL_H
#define TERMINAL_H

class Terminal {
public:
	static const uint8_t MAX_LEN = 64;

	static String buffer;
	static uint8_t pointer_len;
	static uint8_t buffer_len;
	static uint8_t grid[2];
	static uint8_t char_position[2];

	static void begin();
	static void print(String str, uint8_t mode = 0);
	static void print(char symbol, uint8_t mode = 0);
	static void listen(char key, uint8_t mode = 0);
    static void nextLine();
	static void prevLine();
	static void backspace();
	static void erase();
	static void clearBuffer();
	static void left();
	static void right();
};

#endif

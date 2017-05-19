#include "Terminal.h"

String Terminal::buffer;
uint8_t Terminal::buffer_len;
uint8_t Terminal::grid[2];
uint8_t Terminal::char_position[2];

void Terminal::begin() {
	grid[0] = (Graphics::screen_size[0] / Graphics::font_size[0]) - 1;
	grid[1] = (Graphics::screen_size[1] / Graphics::font_size[1]) - 1;
	char_position[0] = 0;
	char_position[1] = 0;
}

void Terminal::print(String str, uint8_t mode, uint8_t R, uint8_t G, uint8_t B) {

	/*
		0 - default increment
		1 - no increment
		2 - remember the position
	*/

	Graphics::setColor(R, G, B);

	uint8_t tmp[] = {
		char_position[0],
		char_position[1]
	};

	for(uint8_t i = 0; str[i] != '\0'; i++) {

		if(str[i] == '\n') {
			nextLine();
			continue;
		}

		Graphics::printSymbol(
			str[i],
			char_position[0] * Graphics::font_size[0],
			char_position[1] * Graphics::font_size[1]
		);

		if(char_position[1] > grid[1])
			erase();

		if(mode == 0 || mode == 2)
			char_position[0]++;

		if(char_position[0] > grid[0])
			nextLine();
	}

	if(mode == 2) {
		char_position[0] = tmp[0];
		char_position[1] = tmp[1];
	}

	Graphics::setColor(255, 255, 255);

}

void Terminal::listen(char key, uint8_t mode) {

	/*
		0 - print input
		1 - no print
	*/

	if(key == 10 || key == 13) {
		String tmp = buffer;
		clearBuffer();
		if(mode == 0) nextLine();
		return;
	}
	else if(key == 8) {
		backspace();
		return;
	}
	else if(key == 60) {
		left();
		return;
	}
	else if(key == 62) {
		right();
		return;
	}

	if(mode == 0)
		print(String(key));

	String before = buffer.substring(0, buffer_len);
	String after = String(key) + buffer.substring(buffer_len, buffer.length());
	buffer = (before+after);
	print(after, 2);
	print("_", 1);
	buffer_len++;
}

void Terminal::prevLine() {
	char_position[1]--;
	char_position[0] = grid[0];
}

void Terminal::nextLine() {
	char_position[1]++;
	char_position[0] = 0;
}

void Terminal::right() {
	if(buffer[buffer_len] != '\0') {
		print(String(buffer[buffer_len]), 1);
		buffer_len++;
		char_position[0]++;
		if(char_position[0] > grid[0])
			nextLine();
	}
}

void Terminal::left() {
	if(buffer_len > 0) {
		if(buffer[buffer_len] != '\0')
			print(String(buffer[buffer_len]), 1);
		else
			print(" ", 1);
		buffer_len--;
		char_position[0]--;
		if(char_position[0] == 0)
			prevLine();
	}
}

void Terminal::backspace() {
	if(buffer_len == 0)
		return;
	buffer.remove(buffer_len-1);

	if(buffer[buffer_len] != '\0')
		print(String(buffer[buffer_len]), 1);
	else
		print(" ", 1);

	for(uint8_t i = buffer_len-1; buffer[i] != '\0'; i++)
		print(String(buffer[i]));

	left();
}

void Terminal::erase() {
	clearBuffer();
	char_position[0] = 0;
	char_position[1] = 0;
	Graphics::clrScr();
}

void Terminal::clearBuffer() {
	buffer = "";
	buffer_len = 0;
}

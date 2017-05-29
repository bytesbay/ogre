#include "Terminal.h"

String Terminal::buffer;
uint8_t Terminal::pointer_len;
uint8_t Terminal::buffer_len;
uint8_t Terminal::grid[2];
uint8_t Terminal::char_position[2];

void Terminal::begin() {
	grid[0] = (Graphics::screen_size[0] / Graphics::font_size[0]) - 1;
	grid[1] = (Graphics::screen_size[1] / Graphics::font_size[1]) - 2;
	char_position[0] = 0;
	char_position[1] = 0;
	buffer_len = 0;
	pointer_len = 0;
	Graphics::setColor(255, 255, 255);
}

void Terminal::print(String str, uint8_t mode) {

	/*
		0 - default increment
		1 - no increment
		2 - remember the position
	*/

	uint8_t tmp[] = {
		char_position[0],
		char_position[1]
	};

	for(uint8_t i = 0; str[i] != '\0'; i++) {

		if(str[i] == '<' && str[i + 1] != '/' && str[i + 2] == '>') {
			char tag = str[i + 1];
			if(tag == 'r') {
				Graphics::setColor(216, 40, 40);
			}
			else if(tag == 'g') {
				Graphics::setColor(91, 255, 80);
			}
			else if(tag == 'b') {
				Graphics::setColor(56, 140, 255);
			}
			else if(tag == 'y') {
				Graphics::setColor(240, 189, 68);
			}
			else if(tag == 'o') {
				Graphics::setColor(217, 86, 51);
			}
			i += 2;
			continue;
		}
		else if(str[i] == '<' && str[i+1] == '/' && str[i + 2] == '>') {
			Graphics::setColor(255, 255, 255);
			i += 2;
			continue;
		}

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

	if(mode != 2)
		Graphics::drawQuad(
			(char_position[0] * Graphics::font_size[0]) + 1,
			(char_position[1] * Graphics::font_size[1]),
			((char_position[0] + 1) * Graphics::font_size[0]) - 1,
			((char_position[1] + 1) * Graphics::font_size[1]) - 1
		);

}

void Terminal::print(char symbol, uint8_t mode) {

	/*
		0 - default increment
		1 - no increment
	*/

	Graphics::printSymbol(
		symbol,
		char_position[0] * Graphics::font_size[0],
		char_position[1] * Graphics::font_size[1]
	);

	if(char_position[1] > grid[1])
		erase();

	if(mode == 0)
		char_position[0]++;

	if(char_position[0] > grid[0])
		nextLine();

	Graphics::drawQuad(
		(char_position[0] * Graphics::font_size[0]) + 1,
		(char_position[1] * Graphics::font_size[1]),
		((char_position[0] + 1) * Graphics::font_size[0]) - 1,
		((char_position[1] + 1) * Graphics::font_size[1]) - 1
	);
}

void Terminal::listen(char key, uint8_t mode) {

	/*
		0 - print input
		1 - no print
	*/

	if(key == 10) {
		if(mode == 0) print(" \n");
		print(Core::exec(buffer));
		clearBuffer();
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
	else if(key == 13) {
		return;
	}

	if(buffer_len >= MAX_LEN)
		return;

	if(mode == 0)
		print(key);

	String tmp = buffer.substring(0, pointer_len);
	String after = buffer.substring(pointer_len, buffer_len);

	buffer = ((tmp + key) + after);
	pointer_len++;
	buffer_len++;
	print(after, 2);
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
	if(pointer_len >= buffer_len)
		return;

	print(buffer[pointer_len], 1);
	pointer_len++;
	char_position[0]++;

	if(char_position[0] > grid[0])
		nextLine();
}

void Terminal::left() {
	if(pointer_len == 0)
		return;

	if(char_position[0] == 0)
		prevLine();

	if(pointer_len != buffer_len)
		print(buffer[pointer_len], 1);
	else
		print(' ', 1);

	pointer_len--;
	char_position[0]--;
}

void Terminal::backspace() {
	if(pointer_len == 0)
		return;
	buffer.remove(pointer_len-1);

	if(buffer[pointer_len] != '\0')
		print(buffer[pointer_len], 1);
	else
		print(' ', 1);

	for(uint8_t i = pointer_len-1; i <= buffer_len; i++)
		print(buffer[i]);

	left();
	buffer_len--;
}

void Terminal::erase() {
	clearBuffer();
	char_position[0] = 0;
	char_position[1] = 0;
	Graphics::clrScr();
}

void Terminal::clearBuffer() {
	buffer = "";
	pointer_len = 0;
	buffer_len = 0;
}

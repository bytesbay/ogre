#include <Arduino.h>
#include <Graphics.h>
#include <Terminal.h>

void setup() {
	Graphics::begin(12, 13);
	Terminal::begin();
	Serial.begin(9600);
	Terminal::print("<System message>", 0, 255, 0, 255);
	Terminal::print(" Hello.\n");
	Terminal::print("<System error>", 0, 255, 0, 0);
	Terminal::print(" SD card fail.\n");
	delay(1000);
}

void loop() {
	if(Serial.available() > 0) {
		Terminal::listen(Serial.read());
	}
}

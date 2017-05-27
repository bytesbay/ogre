#include <Arduino.h>
#include <Graphics.h>
#include <Terminal.h>
#include <Core.h>

void setup() {
	Graphics::begin(12, 13);
	Terminal::begin();
	Core::begin();
	Serial.begin(9600);

	Terminal::print("[ *[[\x01\xFF\x00OK]]* ] SD connect.\n");
	//Terminal::print("[ *[[\x38\x8C\xFFMSG]]* ] Welcome.\n");
}

void loop() {

	if(Serial.available() > 0) Terminal::listen(Serial.read());

}

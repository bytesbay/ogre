#include <Terminal.h>
#include <Core.h>

void setup() {
	Graphics::begin(12, 13);
	Terminal::begin();
	Core::begin();
	Serial.begin(9600);

	if(SD.begin(4)) Terminal::print("[ <g>OK</> ] SD connect.\n");
	else Terminal::print("[ <r>ERROR</> ] SD connect.\n");
	Terminal::print("[ <b>MSG</> ] Welcome.\n");
}

void loop() {

	if(Serial.available() > 0) Terminal::listen(Serial.read());

}

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <MemoryFree.h>
#include <Functions.h>
#include <Terminal.h>
#include <Graphics.h>

#ifndef CORE_H
#define CORE_H

class Core {
public:

    Terminal * GUI;
	Graphics * GLU;

    Core(Graphics * one, Terminal * two);
    String exec(String input);
    String controller(uint8_t to, uint8_t data);
};

#endif

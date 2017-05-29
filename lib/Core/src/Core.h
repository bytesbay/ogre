#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <MemoryFree.h>
#include <Functions.h>
#include <Graphics.h>

#ifndef CORE_H
#define CORE_H

class Core {
public:

    static String root;
    static uint16_t * variables;
    static uint8_t variables_num;

    static void begin();
    static String exec(String input);
    static bool script(String path);
    static void buzzer(uint8_t note, uint16_t sec);
};

#endif

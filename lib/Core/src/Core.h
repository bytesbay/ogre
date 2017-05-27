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

    static void begin();
    static String exec(String input);
    static void script(String path);
};

#endif

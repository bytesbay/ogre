#include <Arduino.h>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void addElem(uint16_t *& array, uint8_t len, uint16_t val);
uint16_t * explode(String str);

#endif

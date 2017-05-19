#include <Arduino.h>
#include <SoftwareSerial.h>

#ifndef GRAPHICS_H
#define GRAPHICS_H

class Graphics {
public:
	static uint8_t font_size[2];
	static uint8_t screen_size[2];
    static SoftwareSerial * GPU;

	static void begin(uint8_t TX, uint8_t RX);
	static void setColor(uint8_t r, uint8_t g, uint8_t b);
	static void drawQuad(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
	static void setFont (uint8_t font_id);
	static void drawPix(uint8_t x, uint8_t y);
	static void clrScr();
	static void setBackground(uint8_t r, uint8_t g, uint8_t b);
	static void drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
	static void printSymbol(uint8_t symbol, uint8_t x = 0, uint8_t y = 0);
	static void getScreen (uint8_t value_id);

private:
	static void waitResponce();
	static void updateValues();
    static const uint8_t RESPONCE_VAL = 255;
};

#endif

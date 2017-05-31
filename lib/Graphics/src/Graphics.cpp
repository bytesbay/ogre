#include "Graphics.h"

SoftwareSerial * Graphics::GPU;
uint8_t Graphics::font_size[2];
uint8_t Graphics::screen_size[2];

void Graphics::begin(uint8_t TX, uint8_t RX) {
    GPU = new SoftwareSerial(TX, RX);
    GPU->begin(9600);
    waitResponce();
    updateValues();
}

void Graphics::setColor(uint8_t R, uint8_t G, uint8_t B) {
    uint8_t command_string[4] = {0, R, G, B};
    GPU->write(command_string, 4);
    waitResponce();
}

void Graphics::drawQuad(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
    uint8_t command_string[5] = {1, x1, y1, x2, y2};

    GPU->write(command_string, 5);

    waitResponce();
}

void Graphics::setFont (uint8_t font_id) {
    uint8_t command_string[2] = {3, font_id};

    GPU->write(command_string, 2);
    waitResponce();
    updateValues();
}

void Graphics::drawPix(uint8_t x, uint8_t y) {
    uint8_t command_string[3] = {6, x, y};
    GPU->write(command_string, 3);

    waitResponce();
}

void Graphics::clrScr() {
    GPU->write(9);
    waitResponce();
}

void Graphics::setBackground(uint8_t r, uint8_t g, uint8_t b) {
    uint8_t command_string[4] = {7, r, g, b};

    GPU->write(command_string, 4);
    waitResponce();
}

void Graphics::drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
    uint8_t command_string[5] = {8, x1, y1, x2, y2};

    GPU->write(command_string, 5);

    waitResponce();
}

void Graphics::printSymbol(uint8_t symbol, uint8_t x, uint8_t y) {
    uint8_t command_string[4] = {4, symbol, x, y};

    GPU->write(command_string, 4);
    waitResponce();
}

void Graphics::getScreen (uint8_t value_id) {
    uint8_t command_string[2] = {5, value_id};

    GPU->write(command_string, 2);

    while(true) {

        if(GPU->available() > 0) {

            switch(value_id) {
                case 0:
                    font_size[0] = GPU->read() - 1;
                    break;
                case 1:
                    font_size[1] = GPU->read();
                    break;
                case 2:
                    screen_size[0] = GPU->read();
                    break;
                case 3:
                    screen_size[1] = GPU->read();
                    break;
            }

            break;
        }
    }
}

void Graphics::waitResponce() {
    while(GPU->read() != RESPONCE_VAL);
}

void Graphics::updateValues() {
    for(uint8_t i = 0; i < 4; i++) {
        getScreen(i);
    }
}

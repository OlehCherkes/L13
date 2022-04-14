#include "Adafruit_MCP23X17.h"

uint32_t tmr = 0;

//Объявление портов кнопок
#define BTN_PIN_1 0
#define BTN_PIN_2 1
#define BTN_PIN_3 2
#define BTN_PIN_4 3
#define BTN_PIN_5 4
#define BTN_PIN_6 5
#define BTN_PIN_7 6
#define BTN_PIN_8 7
#define BTN_PIN_9 8
#define BTN_PIN_10 9
#define BTN_PIN_11 10
#define BTN_PIN_12 11
#define BTN_PIN_13 12
#define BTN_PIN_14 13
#define BTN_PIN_15 14
#define BTN_PIN_16 15

Adafruit_MCP23X17 mcp; // Создание обьекта MCP23017

// Функция настроек кнопок для Setup
void MCP_setings(){
   mcp.begin_I2C(0x20);
}

// Функция считывания кнопок
void ButtonState() {
    if (mcp.digitalRead(BTN_PIN_1) && millis() - tmr > 200) 
    {
        Serial.println("Click");
        tmr = millis();
    }
}
#ifndef BUTTON_H
#define BUTTON_H

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

float button_value1 = 0.1f;          // значение кнопки кноки №1
float previous_button_value1 = 0.0f; // предидущее значение кноки №1
int button_state1 = 0;               // счетчик кнопки кноки №1

int button_value2 = 1;          // значение кнопки кноки №2
int previous_button_value2 = 0; // предидущее значение кноки №2
int button_state2 = 0;          //счетчик кнопки кноки №2

// Функция настроек кнопок для Setup
void MCP_setings()
{
  mcp.begin_I2C(0x20);
}

// Функция считывания кнопок
void ButtonState()
{
  if (mcp.digitalRead(BTN_PIN_1) && millis() - tmr > 200)
  {
    Serial.println("Click");
    tmr = millis();
  }
}

// функция чтения нажатия кновок
void ButtonRead()
{
  //проверка нажатия кнопки с выполнением действия
  if (mcp.digitalRead(BTN_PIN_5) && millis() - tmr > 200)
  {
    button_state1++;
    if (button_state1 == 7)
      button_state1 = 0;
    tmr = millis();
  }

  // выбор шага
  switch (button_state1)
  {
  case 0:
    button_value1 = 0.1f;
    break;
  case 1:
    button_value1 = 1.0f;
    break;
  case 2:
    button_value1 = 10.0f;
    break;
  case 3:
    button_value1 = 100.0f;
    break;
  case 4:
    button_value1 = 1000.0f;
    break;
  case 5:
    button_value1 = 10000.0f;
    break;
  case 6:
    button_value1 = 100000.0f;
    break;
  }

  if (button_state1 < 0)
    button_state1 = 0; // ограничитель кноки 1

  if (mcp.digitalRead(BTN_PIN_9) && millis() - tmr > 200)
  {
    Serial.print("Click1");
    button_state2++;
    if (button_state2 == 4)
      button_state2 = 0;
    tmr = millis();
  }

  switch (button_state2)
  {
  case 0:
    button_value2 = 1;
    break;
  case 1:
    button_value2 = 10;
    break;
  case 2:
    button_value2 = 25;
    break;
  case 3:
    button_value2 = 50;
    break;
  }

  if (button_state2 < 0)
    button_state2 = 0; // ограничитель кноки 2
}

#endif
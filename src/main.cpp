#include <Arduino.h>
#include <EEPROM.h>
#include <SPI.h>
#include "TFT.h"
#include "Encoder.h"
#include "Draw.h"
#include "Button.h"
#include "Clock.h"
#include "Pointer.h"

bool flag_clear = false;
bool flag_batton = false;

void setup()
{
  Clock_setings();    // функция настроек Wi-Fi и часов
  TFT_setings();      // Функция настроек TFT экрана для Setup
  Encoder_setings();  // Функция настроек энкодеров для Setup
  MCP_setings();      // Функция настроек кнопок для Setup
  Serial.begin(9600); // запуск сирийного порта
}

void loop()
{
  switch (flag_screen)
  {
  // Главное меню
  case false:
    if (!flag_clear)
    {
      tft.fillScreen(0x0000);
      flag_clear = true;
    }
    DrawMain();         // Функция вывода главного меню
    ButtonRead();       // Функция считывания состояния кнопок
    EncoderRead();      // Фунция считывания положения энкодера
    DrawButton();       // Функция прорисовки кнопок
    DrawEncoder();      // Функция отрисовки энкодера
    Clock();            // Функция считывания данных с NTP
    DrawClock(GetDate); // Функция отрисовки часов
    DrawIP();           // Функция отрисовки Wi-Fi, IP
    break;

  // Меню настроек
  case true:
    if (flag_clear)
    {
      tft.fillScreen(0x0000);
      flag_clear = false;
    }
    ButtonBack();               // Функция отрисовки кнопки "BACK"
    DrawSecondScreen();         // Отрисовка подменю
    DrawPointer(pointer, flag); // Отрисовка указателя
    break;
  }

  // Меняем страницу экрана
  if (mcp.digitalRead(BTN_PIN_1) && !flag_screen && millis() - tmr > 1000)
  {
    flag_screen = !flag_screen;
    tmr = millis();
  }
}

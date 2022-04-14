#ifndef TFT_H_
#define TFT_H_

// Подключение библиотек для работы TFT экрана
#include "Adafruit_GFX.h" 
#include "Adafruit_ST7796S_kbv.h"
#include "Adafruit_I2CDevice.h" 
#include "Fonts/FreeSans12pt7b.h"
#include "Fonts/FreeSans9pt7b.h"


// Пины подключения TFT экрана
#define TFT_CS 15 // цифровой выход D15
#define TFT_DC 2  // цифровой выход D2
#define TFT_RST 5 // цифровой выход D5

// Создание обьекта tft
Adafruit_ST7796S_kbv tft = Adafruit_ST7796S_kbv(TFT_CS, TFT_DC, TFT_RST);

// Функция настроек TFT экрана
void TFT_setings() {
tft.begin(); // запуск работы TFT екрана
tft.setFont(&FreeSans12pt7b);
tft.fillScreen(0x0000); // закрашивание экрана в черный цыет
tft.setRotation(3); // функуия поворота экрана(экрана позиция №1/горизонтальная)
}

#endif 
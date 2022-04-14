#include "GyverEncoder.h" // библиотека энкодера
#include "Button.h"

// подключение энкодера 1
#define CLK 4 // цифровой выход D4
#define DT 14 // цифровой выход D14

#define CLK2 33 // цифровой выход D33
#define DT2 32  // цифровой выход D32

Encoder enc1(CLK, DT);     // инициализация энкодера
Encoder enc2(CLK2, DT2);     // инициализация энкодера

int value1 = 0;    // счетчик энкодера
int value2 = 0;    // счетчик энкодера

// Функция настроек энкодеров для Setup
void Encoder_setings() {
enc1.setType(TYPE1);    // тип энкодера TYPE1 одношаговый
enc2.setType(TYPE1);    // тип энкодера TYPE1 одношаговый
}

// Фунция считывания положения энкодера
int EncoderRead() {
  enc1.tick();  // обязательная функция отработки. Должна постоянно опрашиваться        
  static int previous_value1 = 0;                                                                  // обязательная функция отработки. Должна постоянно опрашиваться
  if (enc1.isTurn()) {                 // если был совершён поворот (индикатор поворота в любую сторону)
    if (enc1.isRight()) value1 += button_value1;        // если был поворот направо, увеличиваем на 1
    if (enc1.isLeft()) value1 -= button_value1;          // если был поворот налево, уменьшаем на 1
    if (value1 < 0) value1 = 0;                          // ограничитель энкодера
  }

  if (previous_value1 != value1) {
    tft.fillRect(190, 98 , 480, 27, 0x0000); // залить квадрат цветом
    previous_value1 = value1; // обновляем предедущее значение
  }

  enc2.tick();  // обязательная функция отработки. Должна постоянно опрашиваться        
  static int previous_value2 = 0;  
  if (enc2.isTurn()) {                 // если был совершён поворот (индикатор поворота в любую сторону)
    if (enc2.isRight()) value2++;        // если был поворот направо, увеличиваем на 1
    if (enc2.isLeft()) value2--;          // если был поворот налево, уменьшаем на 1
    if (value2 < 0) value2 = 0;                          // ограничитель энкодера
    if (value2 > 100) value2 = 100;                          // ограничитель энкодера
  }

  if (previous_value2 != value2) {
    tft.fillRect(190, 148 , 480, 27, 0x0000); // залить квадрат цветом
    previous_value2 = value2; // обновляем предедущее значение
  }

  return value1;  //функция возвращает значение
}

int previous_value1 = 0;
int previous_value2 = 0;

void DrawEncoder() {
  tft.setCursor(30,120);
  tft.setTextColor(0x0778);
  tft.setTextSize(1);
  tft.print("FREQUENCY: "); tft.print(value1); tft.print(" Hz");
  tft.setCursor(30,170);
  tft.print("DUTY CYCLE: "); tft.print(value2); tft.print(" %");

  if (value1 > previous_value1) {
    tft.fillRect(30+value1, 128, 1, 18, 0x0FF0);
  }
  if (value1 < previous_value1) {
    tft.fillRect(31+value1, 128, 1, 18, 0x0000);
  }
  previous_value1 = value1;

  
  if (value2 > previous_value2) {
    tft.fillRect(30+value2, 178, 1, 18, 0x0FF0);
  }
  if (value2 < previous_value2) {
    tft.fillRect(31+value2, 178, 1, 18, 0x0000);
  }
  previous_value2 = value2;
}
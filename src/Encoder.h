#include "GyverEncoder.h" // библиотека энкодера
#include "Button.h"

// подключение энкодера 1
#define CLK 4 // цифровой выход D4
#define DT 14 // цифровой выход D14

// подключение энкодера 2
#define CLK2 33 // цифровой выход D33
#define DT2 32  // цифровой выход D32

Encoder enc1(CLK, DT);   // инициализация энкодера 1
Encoder enc2(CLK2, DT2); // инициализация энкодера 2

float value1 = 0.0f; // счетчик энкодера 1
int value2 = 0;      // счетчик энкодера 2

// Функция настроек энкодеров для Setup
void Encoder_setings()
{
  enc1.setType(TYPE1); // тип энкодера TYPE1 одношаговый 
  enc2.setType(TYPE1); // тип энкодера TYPE1 одношаговый 
}

// Фунция считывания положения энкодера
void EncoderRead()
{
  enc1.tick();                         // обязательная функция отработки. Должна постоянно опрашиваться
  static float previous_value1 = 0.0f; // обязательная функция отработки. Должна постоянно опрашиваться
  if (enc1.isTurn())
  { // если был совершён поворот (индикатор поворота в любую сторону)
    if (enc1.isRight())
      value1 += button_value1; // если был поворот направо, увеличиваем на 1
    if (enc1.isLeft())
      value1 -= button_value1;              // если был поворот налево, уменьшаем на 1
    value1 = constrain(value1, 0, 1000000); // ограничитель энкодера
  }

  if (previous_value1 != value1)
  {
    tft.fillRect(190, 98, 480, 27, 0x0000); // залить квадрат цветом
    previous_value1 = value1;               // обновляем предедущее значение
  }

  enc2.tick(); // обязательная функция отработки. Должна постоянно опрашиваться
  static int previous_value2 = 0;
  if (enc2.isTurn())
  { // если был совершён поворот (индикатор поворота в любую сторону)
    if (enc2.isRight())
      value2 += button_value2; // если был поворот направо, увеличиваем на 1
    if (enc2.isLeft())
      value2 -= button_value2;          // если был поворот налево, уменьшаем на 1
    value2 = constrain(value2, 0, 100); // ограничитель энкодера
  }

  if (previous_value2 != value2)
  {
    tft.fillRect(190, 148, 480, 27, 0x0000); // залить квадрат цветом
    previous_value2 = value2;                // обновляем предедущее значение
  }

  // return value1;  //функция возвращает значение
}

float previous_value1 = 0.0f;
float previous_value2 = 0.0f;

// Отрисовка значений энкодеров
void DrawEncoder()
{
  tft.setCursor(30, 120);
  tft.setTextColor(0x0778);
  tft.setTextSize(1);
  tft.print("FREQUENCY: ");
  tft.printf("%.1f", value1);
  tft.print(" Hz");
  tft.setCursor(30, 170);
  tft.print("DUTY CYCLE: ");
  tft.print(value2);
  tft.print(" %");

  int draw_line1 = map(value1, 0 , 1000000, 0 ,420);
  if (value1 || value1 > previous_value1)
  {
    tft.fillRect(30, 128, draw_line1, 18, 0x0FF0);

  }
  if (value1 < previous_value1)
  {
    //tft.writeFillRect(448, 128, -(420 - draw_line1), 18, 0xF0F0);
    tft.fillRect(31, 128, 418, 18, 0x0000);
  }
  previous_value1 = value1;

  int draw_line2 = map(value2, 0 , 100, 0 ,420);
  if (value2 || value2 > previous_value2)
  {
    tft.fillRect(30, 178, draw_line2, 18, 0x0FF0);
  }
  if (value2 < previous_value2)
  {
   //tft.writeFillRect(448, 178, -(420 - draw_line2), 18, 0xF000);
    tft.fillRect(31, 178, 418, 18, 0x0000);
  }
  previous_value2 = value2;
}
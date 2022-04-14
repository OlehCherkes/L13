#include "GyverEncoder.h" // библиотека энкодера

// подключение энкодера 1
#define CLK 4 // цифровой выход D4
#define DT 14 // цифровой выход D14

Encoder enc1(CLK, DT);     // инициализация энкодера

int value1 = 0;    // счетчик энкодера

// Функция настроек энкодеров для Setup
void Encoder_setings() {
enc1.setType(TYPE1);    // тип энкодера TYPE1 одношаговый
}

// Фунция считывания положения энкодера
int EncoderRead() {
  enc1.tick();  // обязательная функция отработки. Должна постоянно опрашиваться        
  static int previous_value1 = 0;                                                                  // обязательная функция отработки. Должна постоянно опрашиваться
  if (enc1.isTurn()) {                 // если был совершён поворот (индикатор поворота в любую сторону)
    if (enc1.isRight()) value1++;        // если был поворот направо, увеличиваем на 1
    if (enc1.isLeft()) value1--;          // если был поворот налево, уменьшаем на 1
    if (value1 < 0) value1 = 0;                          // ограничитель энкодера
  }
  if (previous_value1 != value1) {
    tft.fillRect(190, 98 , 480, 27, 0x0000); // залить квадрат цветом
    previous_value1 = value1; // обновляем предедущее значение
  }
  return value1;  //функция возвращает значение
}

int previous_value = 0;

void DrawEncoder() {
  tft.setCursor(30,120);
  tft.setTextColor(0x0778);
  tft.setTextSize(1);
  tft.print("FREQUENCY: "); tft.print(EncoderRead()); tft.print(" Hz");
  tft.setCursor(30,170);
  tft.print("DUTY CYCLE: "); tft.print("0"); tft.print(" %");

  if (value1 > previous_value) {
    tft.fillRect(30+value1, 128, 1, 18, 0x0FF0);
  }
  if (value1 < previous_value) {
    tft.fillRect(31+value1, 128, 1, 18, 0x0000);
  }
  previous_value = value1;
}
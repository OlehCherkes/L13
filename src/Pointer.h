#include <EEPROM.h>

#define ITEMS 8 // Количество пунктов меню

bool flag = true; // флаг состояния кнопки
int data[ITEMS];  // масив где хранятся данные

static uint8_t pointer = 0; // положение указателя

bool flag_state = false;
bool flag_screen = false;

void DrawSecondScreen()
{
    // отрисовка пунктов подменю
    tft.setTextColor(0x0778);
    tft.setCursor(0, 30);
    tft.print(F("     Fan Speed:\n"
                "     Parametr 1:\n"
                "     Parametr 2:\n"
                "     Parametr 3:\n"
                "     Parametr 4:\n"
                "     Parametr 5:\n"
                "     Parametr 6:\n"
                "     Parametr 7:\n"));

    for (int i = 0; i < ITEMS; i++)
    {
        tft.setCursor(170, (i * 29) + 30);
        if (i == 0)
            data[0] = constrain(data[0], 0, 100);
        tft.print(data[i]);
    }

    // считываем положение энкодера
    enc1.tick();
    if (enc1.isLeft())
    {
        if (flag)
        {
            pointer = constrain(pointer - 1, 0, ITEMS - 1);
        }
        else
        {
            tft.fillRect(155, (pointer * 29) + 12, 290, 25, 0x0000); // очистка строки
            data[pointer]--;
        }
    }

    if (enc1.isRight())
    {
        if (flag)
        {
            pointer = constrain(pointer + 1, 0, ITEMS - 1);
        }
        else
        {
            tft.fillRect(155, (pointer * 29) + 12, 290, 25, 0x0000); // очистка строки
            data[pointer]++;
        }
    }

    if (mcp.digitalRead(BTN_PIN_1) && flag_screen && !flag_state && millis() - tmr > 100)
    {
        flag = !flag;
        flag_state = true;
        tmr = millis();
        Serial.println("Click");
    }
    if (mcp.digitalRead(BTN_PIN_1) && flag_screen && flag_state && millis() - tmr > 1000)
    {
        tmr = millis();
        flag = true;
        flag_screen = false;
        flag_state = true;
        pointer = 0;
        Serial.println("Press hold");
    }
    if (!mcp.digitalRead(BTN_PIN_1) && flag_screen && flag_state && millis() - tmr > 100)
    {
        flag_state = false;
        tmr = millis();
        Serial.println("Release");
    }
}

// Отрисовка указателя
void DrawPointer(uint8_t pointer, bool flag)
{
    static uint8_t previous_pointer;
    tft.setTextColor(0x0000);
    if (flag)
    {
        tft.drawRoundRect(28, ((pointer * 29) + 10), 420, 29, 3, 0xFF20);
    }
    else
    {
        tft.drawRoundRect(28, ((pointer * 29) + 10), 420, 29, 3, 0xF000);
    }

    if (previous_pointer != pointer)
    {
        tft.drawRoundRect(28, ((previous_pointer * 29) + 10), 420, 29, 3, 0x0000);
        previous_pointer = pointer;
    }
}
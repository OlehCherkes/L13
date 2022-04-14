#include <WiFi.h>
#include "NTPClient.h"
#include <WiFiUdp.h>

// Логин и пароль Wi-Fi
const char *ssid = "Perchik2_2.4Ghz";
const char *password = "UKR_5016";

// Определяют клиента NTP для запроса даты и времени с сервера NTP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

//День недели
String weekDays[7] = {" Mon",
                      " Tue",
                      " Wed",
                      " Thu",
                      " Fri",
                      " Sat",
                      " Sun"};

//Месяц
String months[12] = {"January",
                     "February",
                     "March",
                     "April",
                     "May",
                     "June",
                     "July",
                     "August",
                     "September",
                     "October",
                     "November",
                     "December"};

void Clock_setings()
{
    // Подключение к Wi-Fi
    WiFi.begin(ssid, password);
    /*while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }*/
    timeClient.begin();              // Инииализация NTPClient для получения времени
    timeClient.setTimeOffset(10800); // GMT +1 = 3600, для Украины (10800)
}

struct DateStruct
{
    time_t epochTime;
    String formattedTime;
    int currentHour;
    int currentMinute;
    int currentSecond;
    String weekDay;
    String currentDate;
};

struct DateStruct GetDate;

DateStruct Clock()
{

    timeClient.update();                                   // Установливаем обновление
    GetDate.epochTime = timeClient.getEpochTime();         // отсчет в секундах с 1970
    GetDate.formattedTime = timeClient.getFormattedTime(); // время чч:мм:сс
    GetDate.currentHour = timeClient.getHours();           // чч
    GetDate.currentMinute = timeClient.getMinutes();       // мм
    GetDate.currentSecond = timeClient.getSeconds();       // сс
    GetDate.weekDay = weekDays[timeClient.getDay()];       // день недели

    // Получаем дату
    struct tm *ptm = gmtime((time_t *)&GetDate.epochTime);

    int monthDay = ptm->tm_mday;                        // день месяца
    int currentMonth = ptm->tm_mon + 1;                 // номер месяц
    String currentMonthName = months[currentMonth - 1]; // название месяца
    int currentYear = ptm->tm_year + 1900;              // год

    // Прорисовка полной даты
    GetDate.currentDate = String(currentYear) + "." + String(currentMonth) + "." + String(monthDay);
    return GetDate;
}

void DrawClock(DateStruct GetDate)
{
    if (WiFi.status() == WL_CONNECTED)
    {
        // Прорисовка часов
        static int previous_second;
        if (GetDate.currentSecond != previous_second)
        {
            tft.fillRect(30, 10, 90, 25, 0x0000);
            previous_second = GetDate.currentSecond;
        }
        tft.setTextColor(0xFFFF);
        tft.setCursor(30, 30);
        tft.print(GetDate.formattedTime);

        // Прорисовка дня недели
        static String previous_weekDay;
        if (GetDate.weekDay != previous_weekDay)
        {
            tft.fillRect(125, 10, 50, 25, 0x0000);
            previous_weekDay = GetDate.weekDay;
        }
        tft.setTextColor(0x0778);
        tft.print(GetDate.weekDay);

        // Прорисовка даты (г/м/д)
        static String previous_currentDate;
        if (GetDate.currentDate != previous_currentDate)
        {
            tft.fillRect(30, 35, 120, 25, 0x0000);
            previous_currentDate = GetDate.currentDate;
        }
        tft.setTextColor(0xFFFF);
        tft.setCursor(30, 55);
        tft.print(GetDate.currentDate);
    }
}

void DrawIP()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        // Прорисовка IP
        tft.drawBitmap(393, 8, WiFi_bitmab, 25, 25, 0xFFFF);
        tft.setCursor(200, 30);
        tft.setTextColor(0x0778);
        tft.print("IP: ");
        tft.print(WiFi.localIP());

        // Прорисовка имени Wi-Fi (ssid)
        // tft.drawRoundRect(209, 34, 43, 27, 3, 0xFF20);
        tft.setCursor(200, 55);
        tft.print(ssid);
    }

    else if (WiFi.status() != WL_CONNECTED && millis() > 8000)
    {
        tft.setCursor(200, 30);
        tft.setTextColor(0x0778);
        tft.print("No WiFi connection");
    }
}
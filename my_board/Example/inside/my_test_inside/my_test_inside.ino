/*
 http://arduino.purel.in.ua
*/

// библиотека кириличнского экрана
#include <LiquidCrystalRus.h>
// библиотека часов
#include <DS1307.h>
// Библиотека памяти EEPROM
#include <EEPROM.h>

#include <SPI.h>
#include <SD.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <TinyGPS++.h>
#include <Servo.h>

// Выходы
const int Backlight         = 10;  // Подсветка
const int GreenLed          = 13;  // пин Зелёного светодиода
const int SDA_pin           = 20;  // пин SDA
const int SCL_pin           = 21;  // пин SCL
const int RS_pin            = 8;
const int RW_pin            = 0;   // Земля
const int Enable_pin        = 9;
const int D4_pin            = 4;
const int D5_pin            = 5;
const int D6_pin            = 6;
const int D7_pin            = 7;

// Переменные целые
int       TimeDelay         = 1000;// значение в милисекундах
int       GreenLedState     = LOW; // состояние Зелёного светодиода
int       VBATvalue         = 0;   // значение АЦП для АКБ
int       SOLARvalue        = 0;   // значение АЦП для Панели
int       address           = 0;   // начальный адресс EEPROM

// Переменные с плавающей точкой
float     VBATfloatValue    = 0;   // значение напряжения АКБ
float     SOLARfloatValue   = 0;   // значение напряжения Панели

// Переменная
String    inString          = "";  // string to hold input
byte      value;

// установить выбраные значения для экрана
// Инициализация LCD             RS,          E,    DB4,    DB5,    DB6,    DB7,   +,   -
//               LCD (01-16)     08,         09,     04,     05,     06,     07,   +,   - )
LiquidCrystalRus lcd       ( RS_pin, Enable_pin, D4_pin, D5_pin, D6_pin, D7_pin);

// Настройка часов
DS1307    rtc(SDA_pin, SCL_pin);    // Инициализация DS1307

// On the Ethernet Shield, CS is pin 4. Note that even if it's not
// used as the CS pin, the hardware CS pin (10 on most Arduino boards,
// 53 on the Mega) must be left as an output or the SD library
// functions will not work.
const int chipSelect = 53;

void setup() {

  while (!Serial) {
    // wait for serial port to connect.
    // Needed for Leonardo only
    ;
  }

  // Включение серийных портов
  Serial.begin(9600);                // Общий
  Serial1.begin(4800);               // GPS
  Serial2.begin(57600);              // GSM(GPRS)
  Serial3.begin(9600);               // ARDUINO

  // зададим пин подсветки как выход
  pinMode(Backlight, OUTPUT);

  // включим подсветку
  BacklightOn();

  // зададим как выход
  pinMode(GreenLed, OUTPUT);
  // включим его
  digitalWrite(GreenLed, HIGH);

  // установить для LCD's колличество колонок и строк
  lcd.begin(20, 4);
  // установить курсор в позицию
  lcd.setCursor(0, 0);
  // приветствие
  lcd.print("Русская версия");
  // ждём заданный интервал
  delay(TimeDelay);
  // отчистить экран
  lcd.clear();

  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(53, OUTPUT);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

void loop() {

  ReadSerialInput();
  // Calculate();
  PrintOnLcd();
  // PrintSerial();

  // if the LED is off turn it on and vice-versa:
  if (GreenLedState == LOW)
    GreenLedState = HIGH;
  else
    GreenLedState = LOW;

  // включить или выключить светодиод
  digitalWrite(GreenLed, GreenLedState);

  // ждём заданный интервал
  delay(TimeDelay);
}

void BacklightOn() {
  
  // включить подсветку экрана
  digitalWrite(Backlight, HIGH);
}

void BacklightOff() {
  
  // выключить подсветку экрана
  digitalWrite(Backlight, LOW);
}

void BacklightFadeOn() {
  
  // увеличить подсветку экрана
  analogWrite(Backlight, 254);  // зажигаем подсветку максимально ярко
  delay(500);                   // Пауза 0,5 секунды
  analogWrite(Backlight, 127);  // Делаем подсветку в 2 раза слабее
  delay(500);                   // Пауза 0,5 секунды
  analogWrite(Backlight, 63);   // Делаем подсветку еще в 2 раза слабее
  delay(500);                   // Пауза 0,5 секунды
  analogWrite(Backlight, 0);    // Выключаем подсветку полностью
  delay(500);                   // Пауза 0,5 секунды
}

void BacklightFadeOff() {
  
  // уменьшить подсветку экрана
  analogWrite(Backlight, 0);    // зажигаем подсветку максимально ярко
  delay(500);                   // Пауза 0,5 секунды
  analogWrite(Backlight, 63);   // Делаем подсветку в 2 раза слабее
  delay(500);                   // Пауза 0,5 секунды
  analogWrite(Backlight, 127);  // Делаем подсветку еще в 2 раза слабее
  delay(500);                   // Пауза 0,5 секунды
  analogWrite(Backlight, 254);  // Выключаем подсветку полностью
  delay(500);                   // Пауза 0,5 секунды
}

void ReadSerialInput() {

  // Read serial input:
  while (Serial1.available() > 0) {
    int inChar = Serial1.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char
      // and add it to the string:
      inString += (char)inChar;
    }
    // if you get a newline, print the string,
    // then the string's value:
    if (inChar == '\n') {
      Serial.print("Value:");
      Serial.println(inString.toInt());
      // clear the string for new input:
      inString = "";
    }
  }
}

void Calculate() {

  // пересчитаем значения
  VBATfloatValue  = (float(VBATvalue)  * 5) / 1023 * 2;
  SOLARfloatValue = (float(SOLARvalue) * 5) / 1023 * 3;

}

void PrintOnLcd() {

  lcd.setCursor(0, 0);            // move cursor to second line "0" and 0 spaces over
  lcd.print("АКБ = ");                // display seconds elapsed since power-up
  lcd.print(VBATvalue);           // display seconds elapsed since power-up
  lcd.setCursor(0, 1);            // move cursor to second line "0" and 0 spaces over
  lcd.print("АКБ = ");                // display seconds elapsed since power-
  lcd.print(VBATfloatValue);      // display seconds elapsed since power-up
  lcd.setCursor(0, 2);            // move cursor to second line "0" and 0 spaces over
  lcd.print("Солнце = ");                // display seconds elapsed since power-up
  lcd.print(SOLARvalue);          // display seconds elapsed since power-up
  lcd.setCursor(0, 3);            // move cursor to second line "0" and 0 spaces over
  lcd.print("Солнце = ");                // display seconds elapsed since power-up
  lcd.print(SOLARfloatValue);     // display seconds elapsed since power-up

}

void PrintSerial() {

  // выдать результат в серийный порт 0
  Serial.print("VBAT value = ");
  Serial.println(VBATvalue);
  Serial.print("Voltage = ");
  Serial.println(VBATfloatValue);
  Serial.print("SOLAR value = ");
  Serial.println(SOLARvalue);
  Serial.print("Voltage = ");
  Serial.print(SOLARfloatValue);
  Serial.println(" ");

}

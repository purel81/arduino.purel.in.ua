#include <DS1307.h>
#include <LiquidCrystalRus.h>
// Инициализация LCD         RS, E, DB5, DB6, DB7, DB8
//               LCD (01-16) 04, 06, 11, 12, 13, 14, +, - )
LiquidCrystalRus lcd       ( 22, 23, 24, 25, 26, 27       );
/*
LiquidCrystal(rs, enable, d4, d5, d6, d7)
LiquidCrystal(rs, rw, enable, d4, d5, d6, d7)
LiquidCrystal(rs, enable, d0, d1, d2, d3, d4, d5, d6, d7)
LiquidCrystal(rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7)
*/

// Аналоговые пины (16 штук)
const int Analog01        = A0 ;            // Аналоговый вход общего питания
const int Analog02        = A1 ;            // Аналоговый вход питания солнечной батареи
const int Analog03        = A2 ;            // Аналоговый вход общего питания
const int Analog04        = A3 ;            // Аналоговый вход общего питания
const int Analog05        = A4 ;            // Аналоговый вход общего питания
const int Analog06        = A5 ;            // Аналоговый вход общего питания
const int Analog07        = A6 ;            // Аналоговый вход общего питания
const int Analog08        = A7 ;            // Аналоговый вход общего питания
const int Analog09        = A8 ;            // Аналоговый вход общего питания
const int Analog10        = A9 ;            // Аналоговый вход общего питания
const int Analog11        = A10;            // Аналоговый вход общего питания
const int Analog12        = A11;            // Аналоговый вход общего питания
const int Analog13        = A12;            // Аналоговый вход общего питания
const int Analog14        = A13;            // Аналоговый вход общего питания
const int Analog15        = A14;            // Аналоговый вход общего питания
const int Analog16        = A15;            // Аналоговый вход общего питания

// Выходы
int       LED_13          = 13;             // внутренний светодиод
int       SDA_pin         = 20;             // пин SDA
int       SCL_pin         = 21;             // пин SCL

// переменные целые
int       ValueAnalog01   = 0 ;             // Первоначальное значение считаное с аналогового входа 01
int       ValueAnalog02   = 0 ;             // Первоначальное значение считаное с аналогового входа 02
int       ValueAnalog03   = 0 ;             // Первоначальное значение считаное с аналогового входа 03
int       ValueAnalog04   = 0 ;             // Первоначальное значение считаное с аналогового входа 04
int       ValueAnalog05   = 0 ;             // Первоначальное значение считаное с аналогового входа 05
int       ValueAnalog06   = 0 ;             // Первоначальное значение считаное с аналогового входа 06
int       ValueAnalog07   = 0 ;             // Первоначальное значение считаное с аналогового входа 07
int       ValueAnalog08   = 0 ;             // Первоначальное значение считаное с аналогового входа 08
int       ValueAnalog09   = 0 ;             // Первоначальное значение считаное с аналогового входа 09
int       ValueAnalog10   = 0 ;             // Первоначальное значение считаное с аналогового входа 10
int       ValueAnalog11   = 0 ;             // Первоначальное значение считаное с аналогового входа 11
int       ValueAnalog12   = 0 ;             // Первоначальное значение считаное с аналогового входа 12
int       ValueAnalog13   = 0 ;             // Первоначальное значение считаное с аналогового входа 13
int       ValueAnalog14   = 0 ;             // Первоначальное значение считаное с аналогового входа 14
int       ValueAnalog15   = 0 ;             // Первоначальное значение считаное с аналогового входа 15
int       ValueAnalog16   = 0 ;             // Первоначальное значение считаное с аналогового входа 16

// переменные с плавающей точкой
float     Voltage01       = 0 ;             // variable for voltage calculation
float     Voltage02       = 0 ;             // variable for voltage calculation
float     Voltage06       = 0 ;             // variable for voltage calculation

// Настройка часов
DS1307    rtc(SDA_pin, SCL_pin);            // Init the DS1307

void setup() {

  // LCD как экран 20*4
  lcd.begin(20, 4);

  // Включение серийных портов
  Serial.begin(9600);                    // Общий
  Serial1.begin(4800);                   // GPS
  Serial2.begin(57600);                  // GSM(GPRS)
  Serial3.begin(9600);                   // ARDUINO

  rtc.halt(false);                       // (false)-включить часы, (true)-остановить часы
  //rtc.setDOW(SUNDAY);                    // Set Day-of-Week to SUNDAY
  //rtc.setTime(17, 11, 0);                // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(22, 06, 2014);             // Set the date to October 3th, 2010

  rtc.setSQWRate(SQW_RATE_1);            // Установить SQW выход как 1Hz
  rtc.enableSQW(true);                   // Включить SQW

  //Serial.println(EEPROM.read(256));
  //EEPROM.write(256,65);

  // внутренний светодиод как выход
  pinMode(LED_13, OUTPUT);
}

void loop() {

  ValueAnalog01 =   analogRead(Analog01);           // прочитать аналоговое значение со входа в переменную
  Voltage01     =   (float(ValueAnalog01) * 5) / 1023; // перевести значение в число с плавающей точкой как вольты
  ValueAnalog02 =   analogRead(Analog02);           // прочитать аналоговое значение со входа в переменную
  Voltage02     =   ValueAnalog02 * (5.0 / 1023) * 3; // перевести значение в число с плавающей точкой как вольты
  ValueAnalog06 =   analogRead(Analog06);           // прочитать аналоговое значение со входа в переменную
  Voltage06     =   (float(ValueAnalog06) * 5) / 1023; // перевести значение в число с плавающей точкой как вольты

  digitalWrite(LED_13, LOW);    // выключить внутренний светодиод

  // показать ДЕНЬ НЕДЕЛИ
  lcd.setCursor(0, 0);
  lcd.print(rtc.getDOWStr(FORMAT_SHORT));

  // показать ВРЕМЯ
  lcd.setCursor(4, 0);
  lcd.print(rtc.getTimeStr());

  // показать ДАТУ
  lcd.setCursor(2, 1);
  lcd.print(rtc.getDateStr());

  // вывести значения в серийный порт
  Serial.print("data=");
  Serial.print(rtc.getDateStr());
  Serial.print(";dow=");
  Serial.print(rtc.getDOWStr(FORMAT_SHORT));
  Serial.print(";time=");
  Serial.print(rtc.getTimeStr());
  Serial.print(";Value01=");
  Serial.print(ValueAnalog01);
  Serial.print(";Voltage01=");
  Serial.print(Voltage01);
  Serial.print(";Value02=");
  Serial.print(ValueAnalog02);
  Serial.print(";Voltage02=");
  Serial.println(Voltage02);

  // Display time centered on the upper line
  lcd.setCursor(16, 0);
  lcd.print(Voltage01);

  // Display time centered on the upper line
  lcd.setCursor(15, 1);
  lcd.print(Voltage02);

  // Display time centered on the upper line
  lcd.setCursor(16, 2);
  lcd.print(Voltage06);

  delay(500);  // ждём пол секунды

  digitalWrite(LED_13, HIGH);   // включить внутренний светодиод

  delay(500);  // ждём пол секунды
}

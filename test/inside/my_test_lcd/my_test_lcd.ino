/*
 http://www.seeedstudio.com/wiki/index.php?title=Solar_Charger_Shield_v2.0b
 */

// start of LCD pin definitions
#include <LiquidCrystal.h>
int LCD_RS_pin     = 8;
int LCD_Enable_pin = 9;
int LCD_D4_pin     = 4;
int LCD_D5_pin     = 5;
int LCD_D6_pin     = 6;
int LCD_D7_pin     = 7;

// select the pins used on the LCD panel
LiquidCrystal lcd(LCD_RS_pin, LCD_Enable_pin, LCD_D4_pin, LCD_D5_pin, LCD_D6_pin, LCD_D7_pin);

const int Backlight         = 10;  // Подсветка
const int GreenLed          = 13;  // пин Зелёного светодиода
int GreenLedState           = LOW; // состояние Зелёного светодиода
int GreenLedStateLow        = LOW; // состояние Зелёного светодиода выключено
int GreenLedStateHigh       = HIGH;// состояние Зелёного светодиода включеноа
int       VBATvalue         = 0;   // значение АЦП для АКБ
int       SOLARvalue        = 0;   // значение АЦП для Панели
float     VBATfloatValue    = 0;   // значение напряжения АКБ
float     SOLARfloatValue   = 0;   // значение напряжения Панели
String    inString          = "";  // string to hold input

void setup() {
  
  while (!Serial) {
    // wait for serial port to connect. Needed for Leonardo only
    ;
  }
  
  Serial.begin(9600);
  Serial1.begin(9600);

  // зададим как выход
  pinMode(Backlight, OUTPUT);
  // включим подсветку
  digitalWrite(Backlight, HIGH);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.home();                 //line=0, x=0
  lcd.setCursor(0, 0);        // set the LCD cursor   position
  lcd.print("Solar charge");  // print a simple message on the LCD
  lcd.clear();         // очистить экран

  // ждём заданный интервал
  delay(TimeDelay);

  // зададим как выход
  pinMode(GreenLed, OUTPUT);
  // включим его
  BacklightOn();
}

void loop() {

  ReadSerialInput();
  // Calculate();
  // PrintOnLcd();
  // PrintSerial();

  // if the LED is off turn it on and vice-versa:
  if (GreenLedState == LOW)
    BacklightOff();
  else
    BacklightOn();

  // включить или выключить светодиод
  digitalWrite(GreenLed, GreenLedState);

  // ждём заданный интервал
  delay(TimeDelay);
}

void BacklightOn() {
  digitalWrite(Backlight, HIGH);
}

void BacklightOff() {
  digitalWrite(Backlight, LOW);
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
  lcd.print("A=");                // display seconds elapsed since power-up
  lcd.print(VBATvalue);           // display seconds elapsed since power-up
  lcd.setCursor(7, 0);            // move cursor to second line "0" and 0 spaces over
  lcd.print("B=");                // display seconds elapsed since power-
  lcd.setCursor(11, 0);           // move cursor to second line "0" and 0 spaces over
  lcd.print(VBATfloatValue);      // display seconds elapsed since power-up
  lcd.setCursor(0, 1);            // move cursor to second line "0" and 0 spaces over
  lcd.print("C=");                // display seconds elapsed since power-up
  lcd.print(SOLARvalue);          // display seconds elapsed since power-up
  lcd.setCursor(7, 1);            // move cursor to second line "0" and 0 spaces over
  lcd.print("D=");                // display seconds elapsed since power-up
  lcd.setCursor(11, 1);           // move cursor to second line
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

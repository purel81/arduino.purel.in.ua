/*
http://zelectro.cc/LCD_Keypad_shield
*/

#include <Wire.h> // добавляем необходимые библиотеки
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7 );

// Нажатые кнопки
int button;
int n;
const int BUTTON_NONE   = 0;
const int BUTTON_RIGHT  = 1;
const int BUTTON_UP     = 2;
const int BUTTON_DOWN   = 3;
const int BUTTON_LEFT   = 4;
const int BUTTON_SELECT = 5;

int getPressedButton()
{
  // считываем значения с аналогового входа(A0)
  int buttonValue = analogRead(0);
  if (buttonValue < 100) {
    return BUTTON_RIGHT;
  }
  else if (buttonValue < 200) {
    return BUTTON_UP;
  }
  else if (buttonValue < 400) {
    return BUTTON_DOWN;
  }
  else if (buttonValue < 600) {
    return BUTTON_LEFT;
  }
  else if (buttonValue < 800) {
    return BUTTON_SELECT;
  }
  return BUTTON_NONE;
}

void setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);        //line=0, x=0
  lcd.print("Press Key:");
  n = 0;
  lcd.setCursor(12, 0);        //line=0, x=12
  lcd.print ("---");
  lcd.setCursor(12, 0);        //line=0, x=12
  lcd.print (n);
}

void loop()
{
  button = getPressedButton();
  switch (button)
  {
    case BUTTON_RIGHT: // при нажатии кнопки выводим следующий текст
      lcd.setCursor(0, 1);
      lcd.print("                 ");
      lcd.setCursor(0, 1);
      lcd.print("BUTTON: RIGHT");
      lcd.setCursor(12, 0);        //line=0, x=12
      lcd.print (n);
      break;
    case BUTTON_LEFT:
      lcd.setCursor(0, 1);
      lcd.print("                   ");
      lcd.setCursor(0, 1);
      lcd.print("BUTTON: LEFT");
      lcd.setCursor(12, 0);        //line=0, x=12
      lcd.print (n);
      break;
    case BUTTON_UP:
      lcd.setCursor(0, 1);
      lcd.print("                  ");
      lcd.setCursor(0, 1);
      lcd.print("BUTTON: UP");
      lcd.setCursor(12, 0);        //line=0, x=12
      n = n + 1;
      lcd.print (n);
      break;
    case BUTTON_DOWN:
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print("BUTTON: DOWN");
      lcd.setCursor(12, 0);        //line=0, x=12
      n = n - 1;
      lcd.print (n);
      break;
    case BUTTON_SELECT:
      lcd.setCursor(0, 1);
      lcd.print("                 ");
      lcd.setCursor(0, 1);
      lcd.print("BUTTON: SELECT");
      lcd.setCursor(12, 0);        //line=0, x=12
      n = 0;
      lcd.print (n);
      break;
  }
}

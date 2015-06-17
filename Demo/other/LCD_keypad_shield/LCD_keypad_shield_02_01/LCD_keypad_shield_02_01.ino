// добавляем необходимые библиотеки
#include <LiquidCrystal.h>
#include <EEPROM.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7 );

// start reading from the first byte (address 0) of the EEPROM
int address = 0;
byte value;

// Нажатые кнопки
int button;
int mainMenu = 0;
int subMenu = 0;
int subsubMenu = 0;
boolean stateMainMenu;
boolean stateSubMenu;
boolean stateSabSabMenu;
const int BUTTON_NONE   = 0;
const int BUTTON_RIGHT  = 1;
const int BUTTON_UP     = 2;
const int BUTTON_DOWN   = 3;
const int BUTTON_LEFT   = 4;
const int BUTTON_SELECT = 5;
const int Backlight = 10;

void setup()
{
  pinMode(Backlight, OUTPUT);
  digitalWrite(Backlight, HIGH);   // Backlight on
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.home();                 //line=0, x=0
  lcd.print("22.10.15");
  lcd.setCursor(0, 1);        //line=1, x=0
  lcd.print("16:35:41");
  lcd.setCursor(9, 1);        //line=, x=9
  lcd.print("123");
  stateMainMenu = false;
  stateSubMenu = false;
  stateSabSabMenu = false;
}

void loop()
{
  // read input:
  readSensors();
}

int getPressedButton()
{
  // считываем значения с аналогового входа(A0)
  int buttonValue = analogRead(0);
  delay (100);
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

void readSensors()
{
  button = getPressedButton();

  switch (button)
  {
    // при нажатии кнопки выводим следующий текст
    case BUTTON_RIGHT:
      if (stateMainMenu == true && stateSubMenu == false && stateSabSabMenu == false)
      {
        mainMenu += 1;
        if (mainMenu == 6)
        {
          mainMenu = 1;
        }
      }
      else if (stateMainMenu == true && stateSubMenu == true && stateSabSabMenu == false)
      {
        subMenu += 1;
        if (subMenu == 6)
        {
          subMenu = 1;
        }
      }
      refreshScreen();
      break;

    case BUTTON_LEFT:
      if (stateMainMenu == true && stateSubMenu == false && stateSabSabMenu == false)
      {
        mainMenu -= 1;
        if (mainMenu == 0)
        {
          mainMenu = 5;
        }
      }
      else if (stateMainMenu == true && stateSubMenu == true && stateSabSabMenu == false)
      {
        subMenu -= 1;
        if (subMenu == 0)
        {
          subMenu = 5;
        }
      }
      refreshScreen();
      break;

    case BUTTON_UP:
      refreshScreen();
      break;

    case BUTTON_DOWN:
      refreshScreen();
      break;

    case BUTTON_SELECT:
      if (stateMainMenu == false && stateSubMenu == false && stateSabSabMenu == false)
      {
        stateMainMenu = true;
        mainMenu = 1;
      }
      else if (stateMainMenu == true && mainMenu == 2 && stateSubMenu == false && stateSabSabMenu == false)
      {
        stateMainMenu = true;
        stateSubMenu = true;
        subMenu = 1;
      }
      else if (stateMainMenu == true && mainMenu == 5 && stateSubMenu == false && stateSabSabMenu == false)
      {
        stateMainMenu = false;
        mainMenu = 0;
      }
      else if (stateMainMenu == true && subMenu == 5 && stateSubMenu == true && stateSabSabMenu == false)
      {
        stateSubMenu = false;
        mainMenu = 2;
      }
      refreshScreen();
      break;
  }
}

void refreshScreen()
{
  if (stateMainMenu == false && stateSubMenu == false && stateSabSabMenu == false)
  {
    lcd.home();        //line=0, x=0
    lcd.print("22.10.15");
    lcd.setCursor(0, 1);        //line=1, x=0
    lcd.print("16:35:41");
    lcd.setCursor(9, 1);        //line=, x=9
    lcd.print("132,450");
  }
  else if (stateMainMenu == true && stateSubMenu == false && stateSabSabMenu == false) {
    if (mainMenu == 1) {
      lcd.home();        //line=0, x=0
      lcd.clear();
      lcd.print("menu:");
      lcd.setCursor(0, 1);        //line=0, x=2
      lcd.print ("1 setings ");
    }
    else if (mainMenu == 2) {
      lcd.setCursor(0, 1);        //line=0, x=2
      lcd.print ("2 clock   ");
    }
    else if (mainMenu == 3) {
      lcd.setCursor(0, 1);        //line=0, x=2
      lcd.print ("3 rele    ");
    }
    else if (mainMenu == 4) {
      lcd.setCursor(0, 1);        //line=0, x=2
      lcd.print ("4 lampa   ");
    }
    else if (mainMenu == 5) {
      lcd.setCursor(0, 1);        //line=0, x=2
      lcd.print ("5 exit    ");
    }
  }
  else if (stateMainMenu == true && stateSubMenu == true && stateSabSabMenu == false) {
    if (subMenu == 1) {
      lcd.home();        //line=0, x=0
      lcd.clear();
      lcd.print("clock:");
      lcd.setCursor(0, 1);        //line=0, x=2
      lcd.print ("1 hour ");
    }
    else if (subMenu == 2) {
      lcd.setCursor(0, 1);        //line=0, x=2
      lcd.print ("2 minute   ");
    }
    else if (subMenu == 3) {
      lcd.setCursor(0, 1);        //line=0, x=2
      lcd.print ("3 secunde    ");
    }
    else if (subMenu == 4) {
      lcd.setCursor(0, 1);        //line=0, x=2
      lcd.print ("4 poyas   ");
    }
    else if (subMenu == 5) {
      lcd.setCursor(0, 1);        //line=0, x=2
      lcd.print ("5 exit    ");
    }
  }
}

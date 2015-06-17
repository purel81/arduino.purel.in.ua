/*
http://chingachgook.net/arduino/podklyuchenie-lcd-keypad-shield-k-arduino.html
*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(0, 0);        //line=0, x=0
  lcd.print("LCD Key Shield");
  lcd.setCursor(0, 1);        //line=1, x=0
  lcd.print("Press Key:");
}

void loop() {
  int x;
  x = analogRead (0);
  lcd.setCursor(10, 1);        //line=1, x=10
  if (x < 60) {
    lcd.print ("Right ");
  }
  else if (x < 200) {
    lcd.print ("Up    ");
  }
  else if (x < 400) {
    lcd.print ("Down  ");
  }
  else if (x < 600) {
    lcd.print ("Left  ");
  }
  else if (x < 800) {
    lcd.print ("Select");
  }
}

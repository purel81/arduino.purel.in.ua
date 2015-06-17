/*
http://chingachgook.net/arduino/podklyuchenie-lcd-keypad-shield-k-arduino.html
*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int n;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(0, 0);        //line=0, x=0
  lcd.print("Press Key:");
  n = 0;
  lcd.setCursor(10, 1);        //line=1, x=10
  lcd.print ("------");
  lcd.setCursor(3, 1);        //line=1, x=3
  lcd.print (n);
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);   // turn the LED on
}

void loop() {

  int x;
  x = analogRead (0);

  if (x < 60) {
    lcd.setCursor(10, 1);        //line=1, x=10
    lcd.print ("Right ");
    lcd.setCursor(3, 1);        //line=1, x=3
    lcd.print (n);
  }
  else if (x < 200) {
    lcd.setCursor(10, 1);        //line=1, x=10
    lcd.print ("Up    ");
    n = n + 1;
    delay (50);
    lcd.setCursor(3, 1);        //line=1, x=3
    lcd.print (n);
  }
  else if (x < 400) {
    lcd.setCursor(10, 1);        //line=1, x=10
    lcd.print ("Down  ");
    n = n - 1;
    delay (50);
    lcd.setCursor(3, 1);        //line=1, x=3
    lcd.print (n);
  }
  else if (x < 600) {
    lcd.setCursor(10, 1);        //line=1, x=10
    lcd.print ("Left  ");
    lcd.setCursor(3, 1);        //line=1, x=3
    lcd.print (n);
  }
  else if (x < 800) {
    lcd.setCursor(10, 1);        //line=1, x=10
    lcd.print ("Select");
    n = 0;
    lcd.setCursor(3, 1);        //line=1, x=3
    lcd.print ("    ");
  }
}

/*******************************************************

   Description:
   Reads an analog input on pin 1, prints the result to the LCD.
   This program takes the temperture sensor LM35 for example.

   Connection:
   Plug the LCD Keypad to the UNO(or other controllers)
   Temperture sensor:
   S(blue) -- A1()
     Note: A0 has been occupied.
   VCC(red) -- VCC
   GND(black) -- GND
   
http://www.dfrobot.com/wiki/index.php/LCD_KeyPad_Shield_For_Arduino_SKU:_DFR0009

********************************************************/

#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);        // select the pins used on the LCD panel

unsigned long tepTimer ;

void setup() {
  lcd.begin(16, 2);                       // start the library
}

void loop() {
  lcd.setCursor(0, 0);                   // set the LCD cursor   position
  int val;                               // variable to store the value coming from the analog pin
  double data;                           // variable to store the temperature value coming from the conversion formula
  val = analogRead(0);                   // read the analog in value:
  data = (double) val * (5 / 10.24);     // temperature conversion formula

  if (millis() - tepTimer > 500) {       // output a temperature value per 500ms
    tepTimer = millis();

    // print the results to the lcd
    lcd.print("T: ");
    lcd.print(data);
    lcd.print("C");
  }
}

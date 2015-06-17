#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

int read_buttons() {

  int adc_key_in = analogRead(0);

  if (adc_key_in > 1000) return btnNONE;
  if (adc_key_in < 50)   return btnRIGHT;  
  if (adc_key_in < 195)  return btnUP; 
  if (adc_key_in < 380)  return btnDOWN; 
  if (adc_key_in < 555)  return btnLEFT; 
  if (adc_key_in < 790)  return btnSELECT;   
}

void setup()
{
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Keypad demo");
}

void loop()
{

  lcd.setCursor(0,1);
  lcd.print("Pressed:");

  int buttons = read_buttons();
  lcd.setCursor(9, 1);  
  if(buttons == btnRIGHT)       lcd.print("RIGHT ");
  else if(buttons == btnLEFT)   lcd.print("LEFT  ");
  else if(buttons == btnUP)     lcd.print("UP    ");
  else if(buttons == btnDOWN)   lcd.print("DOWN  ");
  else if(buttons == btnSELECT) lcd.print("SELECT");
  else if(buttons == btnNONE)   lcd.print("NONE  ");
}


// engine condition monitoring routines
  // cylinder head temperatures, No 1 to 4

// Define the number of samples to keep track of.  The higher the number,
// the more the readings will be smoothed, but the slower the output will
// respond to the input.  Using a constant rather than a normal variable lets
// use this value to determine the size of the readings array.
const int numReadings = 20;
const int number_of_Analogues_in_use = 4;

// start of LCD pin definitions
#include <LiquidCrystal.h> // load the LCD library
  int LCD_RS_pin     = 7;    // was 12
  int LCD_Enable_pin = 8;    // was 11
  int LCD_D4_pin     = 9;    // was 5
  int LCD_D5_pin     = 10;   // was 4
  int LCD_D6_pin     = 11;   // was 3
  int LCD_D7_pin     = 12;   // was 2
LiquidCrystal lcd(LCD_RS_pin, LCD_Enable_pin, LCD_D4_pin, LCD_D5_pin, LCD_D6_pin, LCD_D7_pin);
  // ---------------------------------------------------------
  // start of alarm variable and startup variable definitions
  // ---------------------------------------------------------
int power_up_has_occurred            =  true;
int No1_cht_temperature_is_high      =  false;
int No2_cht_temperature_is_high      =  false;
int No3_cht_temperature_is_high      =  false;
int No4_cht_temperature_is_high      =  false;
int first_run_flag                   =  false;
int alarm_led_output                 =  13;    // engine monitoring module alarm LED is connected to this output
  // ---------------------------------------------------------
  // end of alarm variable and startup variable definitions
  // ---------------------------------------------------------
int start_of_blanking_column_number = 14;
int single_digit_column_number = 17;
int double_digit_column_number = 16;
int triple_digit_column_number = 15;

int readings_No1_cht[numReadings];
int readings_No2_cht[numReadings];
int readings_No3_cht[numReadings];
int readings_No4_cht[numReadings];

int No1_cht_index = 0;                  // the index of the current reading
int No2_cht_index = 0;                  // the index of the current reading
int No3_cht_index = 0;                  // the index of the current reading
int No4_cht_index = 0;                  // the index of the current reading

int total_No1_cht = 0;                  // the running total
int total_No2_cht = 0;                  // the running total
int total_No3_cht = 0;                  // the running total
int total_No4_cht = 0;                  // the running total

int average_No1_cht_temperature = 0;    // the average
int average_No2_cht_temperature = 0;    // the average
int average_No3_cht_temperature = 0;    // the average
int average_No4_cht_temperature = 0;    // the average

int No1_cht_temperature_sample = A0;
int No2_cht_temperature_sample = A1;
int No3_cht_temperature_sample = A2;
int No4_cht_temperature_sample = A3;

int No1_cht_temperature_to_display = 0;
int No2_cht_temperature_to_display = 0;
int No3_cht_temperature_to_display = 0;
int No4_cht_temperature_to_display = 0;

int cylinder_head_alarm_temperature = 270; // max permitted temp = 273c or 525f
  // end of variable definitions
  // ----------------------------------------------------
  // start of variable assignments and once only events
void setup()
{
  // initialize serial communication with computer:
//  Serial.begin(9600);                   

                                 // start of the fixed text on the display
  pinMode(alarm_led_output, OUTPUT);
  lcd.begin(16,4);               // columns, rows.  use 16,4 for a 16x4 LCD, etc.
  lcd.clear();                   // start with a blank screen
  // write all the fixed text to the LCD
  lcd.setCursor(0,0);            // set cursor to column 0, row 0 (the first row)
  lcd.print("NO 1 HEAD TEMP");     //
  lcd.setCursor(19,0);           // set cursor to column 19, row 0 (the first row)
  lcd.print("C");                // 

  lcd.setCursor(0,1);            // set cursor to column 0, row 1  
  lcd.print("NO 2 HEAD TEMP");
  lcd.setCursor(19,1);           // set cursor to column 19, row 1  
  lcd.print("C");

  lcd.setCursor(0,2);            // set cursor to column 0, row 2
  lcd.print("NO 3 HEAD TEMP");
  lcd.setCursor(19,2);           // set cursor to column 19, row 2 
  lcd.print("C");


  lcd.setCursor(0,3);            // set cursor to column 0, row 3
  lcd.print("NO 4 HEAD TEMP");
  lcd.setCursor(19,3);           // set cursor to column 19, row 4
  lcd.print("C");
                                 // end of the fixed text on the display

   // initialize all the No1 EGT averages to zero: 
  for (int thisReadingA0 = 0; thisReadingA0 < numReadings; thisReadingA0++)
    readings_No1_cht[thisReadingA0] = 0;

   // initialize all the No2 EGT averages to zero:
    for (int thisReadingA1 = 0; thisReadingA1 < numReadings; thisReadingA1++)
    readings_No3_cht[thisReadingA1] = 0;

  // initialize all the No3 EGT averages to zero:
    for (int thisReadingA2 = 0; thisReadingA2 < numReadings; thisReadingA2++)
    readings_No3_cht[thisReadingA2] = 0;
   // initialize all the No4 EGT averages to zero:
    for (int thisReadingA3 = 0; thisReadingA3 < numReadings; thisReadingA3++)
    readings_No4_cht[thisReadingA3] = 0;
  // end of the initialization of all the analogue everages to zero: 
}
  // end of variable assignments and once only events
  // -------------------------------------------------
  // 
void loop()
{
  // start of the continious update code
  // start of number one cylinder head temperature averaging
  // subtract the last reading taken at the end of the loop
  total_No1_cht= total_No1_cht - readings_No1_cht[No1_cht_index];         
  // read from the sensor:  
  readings_No1_cht[No1_cht_index] = analogRead(No1_cht_temperature_sample);
  // add the reading to the total:
  total_No1_cht= total_No1_cht + readings_No1_cht[No1_cht_index];       
  // advance to the next position in the array:  
  No1_cht_index = No1_cht_index + 1;                    
  // if we're at the end of the array...
  if (No1_cht_index >= numReadings)              
    // ...wrap around to the beginning: 
    No1_cht_index = 0; 
  // calculate the average:
  average_No1_cht_temperature = total_No1_cht / numReadings;         
  delay(5);        // delay in between reads for stability            
  // end of the number one cylinder head temperature averaging
  // --------------------------------------------
  // start of number two cylinder head temperature averaging
  // subtract the last reading:
  total_No2_cht= total_No2_cht - readings_No2_cht[No2_cht_index];         
  // read from the sensor:  
  readings_No2_cht[No2_cht_index] = analogRead(No2_cht_temperature_sample); 
  // add the reading to the total:
  total_No2_cht = total_No2_cht + readings_No2_cht[No2_cht_index];       
 // advance to the next position in the array:  
  No2_cht_index = No2_cht_index + 1;                    
  // if we're at the end of the array...
  if (No2_cht_index >= numReadings)              
    // ...wrap around to the beginning: 
    No2_cht_index = 0;                           
  // calculate the average:
  average_No2_cht_temperature = total_No2_cht / numReadings;
  delay(5); // delay in between reads for stability     
   // end of the number two cylinder head temperature averaging
  // -----------------------------------------------------------
  // start of number three cylinder head temperature averaging
  // subtract the last reading:
  total_No3_cht= total_No3_cht - readings_No3_cht[No3_cht_index];         
  // read from the sensor:  
  readings_No3_cht[No3_cht_index] = analogRead(No3_cht_temperature_sample);
  // add the reading to the total:
  total_No3_cht= total_No3_cht + readings_No3_cht[No3_cht_index];       
  // advance to the next position in the array:  
  No3_cht_index = No3_cht_index + 1;                    
  // if we're at the end of the array...
  if (No3_cht_index >= numReadings)              
    // ...wrap around to the beginning: 
  No3_cht_index = 0;                           
   // calculate the average:
  average_No3_cht_temperature = total_No3_cht / numReadings;         
  delay(5);        // delay in between reads for stability     
   // end of the number three cylinder head temperature averaging
   // ------------------------------------------------------------
   // start of the number four cylinder head temperature averaging
  // subtract the last reading:
  total_No4_cht= total_No4_cht - readings_No4_cht[No4_cht_index];         
  // read from the sensor:  
  readings_No4_cht[No4_cht_index] = analogRead(No4_cht_temperature_sample); 
  // add the reading to the total:
  total_No4_cht= total_No4_cht + readings_No4_cht[No4_cht_index];       
  // advance to the next position in the array:  
  No4_cht_index = No4_cht_index + 1;                    
  // if we're at the end of the array...
  if (No4_cht_index >= numReadings)              
    // ...wrap around to the beginning: 
    No4_cht_index = 0;                           
  // calculate the average carb inlet air temperature:
  average_No4_cht_temperature = total_No4_cht / numReadings;         
  delay(5);        // delay in between reads for stability     
  // end of the number three cylinder head temperature averaging
  // end of the four averaging routines
  // --------------------------------------------------------
  // start of the four analogue display routines
  // --------------------------------------------------------
  // start of the engine No 1 CHT display loop
  // input is from a Type K thermocouple though a convertor which gives 4 to 20mA output
  // input resistor on the analogue input is 250 ohms to ground
  // this produces 1 to 5 volts at the analogue input representing 0 to 800 degrees centigrade
  // zero and range analogue in next two lines
  No1_cht_temperature_to_display = average_No1_cht_temperature;
  No1_cht_temperature_to_display = map(No1_cht_temperature_to_display, 200, 1012, 0, 800);
  //                   , raw zero, raw range, final zero, final range
  delay(5);
  if  (No1_cht_temperature_to_display < 0)
  {
    No1_cht_temperature_to_display = 0;
  }
  if (No1_cht_temperature_to_display > 800)
 {
    No1_cht_temperature_to_display = 800;
 }
  // --------------------------------------------------------
  // start of the No1 CHT High alarm routine
  // -------------------------------------------------------- 
  if (No1_cht_temperature_to_display > cylinder_head_alarm_temperature)
  {
    No1_cht_temperature_is_high = true;
  }
 else
  {
     No1_cht_temperature_is_high = false;
  }
  //  -------------------------------------
  //  End of the No1 CHT High alarm routine
  //  -------------------------------------
  if (No1_cht_temperature_to_display < 10)
  {
  // do the following if integer average_No1_cht_temperature is less than 10
    lcd.setCursor(start_of_blanking_column_number,0); // set cursor to column 16, row 0 (the first row)
    lcd.print("     ");                               // and overprint the leading zero
    lcd.setCursor(single_digit_column_number,0);                                  // set cursor to column 15, row 0 (the first row)
    lcd.print(No1_cht_temperature_to_display);                   // and print single digit value at tab(15).
  }
   // End of if routine for No 1 CHT in range 0 to 9 Celcius
  if (No1_cht_temperature_to_display > 9 && No1_cht_temperature_to_display < 100)
  {
    lcd.setCursor(start_of_blanking_column_number,0);
    lcd.print("     ");
    lcd.setCursor(double_digit_column_number,0);          // set cursor to column 15, row 0 (the first row)
    lcd.print(No1_cht_temperature_to_display);            // and print double digit text at tab(15+16).
  }
  // End of if routine for No 1 CHT in range 10 to 99 Celcius
  // if test for No 1 CHT > 99
   if (No1_cht_temperature_to_display > 99)
  {
    // do the following if integer average_No1_cht_temperature is greater than 99 i.e. a 3 digit number
    lcd.setCursor(start_of_blanking_column_number,0);     // set cursor to column 16, row 0 (the first row)
    lcd.print("     ");                                   // and overprint the leading zero
    lcd.setCursor(triple_digit_column_number,0);          // set cursor to column 15, row 0 (the first row)
    lcd.print(No1_cht_temperature_to_display);            // and print single digit value at tab(15).
  }
  // End of if routine for CHT in range greater than 800 C, it should not get above if calibration OK
  // end of the engine No 1 CHT display loop
  // -------------------------------------------
  // start of the engine No 2 CHT display loop
  // input is from a Type K thermocouple though a convertor which gives 4 to 20mA output
  // input resistor on the analogue input is 250 ohms to ground
  // this produces 1 to 5 volts at the analogue input representing 0 to 800 degrees centigrade
  No2_cht_temperature_to_display = average_No2_cht_temperature;
  No2_cht_temperature_to_display = map(No2_cht_temperature_to_display, 200, 1013, 0, 800);
  //                                        , raw zero, raw range, final zero, final range  
    if  (No2_cht_temperature_to_display < 0)
  {
    No2_cht_temperature_to_display = 0;
  }
  if (No2_cht_temperature_to_display > 800)
  {
      No2_cht_temperature_to_display = 800;
  }
  // end of No 2 CHT condioning loop. No 2 CHT will now be in the range 0 to 800c
  // --------------------------------------------------------
  // start of the No2 CHT temperature is high alarm routine
  // -------------------------------------------------------- 
  if (No2_cht_temperature_to_display > cylinder_head_alarm_temperature)
  {
    No2_cht_temperature_is_high = true;
  }
 else
  {
     No2_cht_temperature_is_high = false;
  }
  // --------------------------------------------------------
  // end of the No2 CHT temperature is high alarm routine
  // --------------------------------------------------------   
  if (No2_cht_temperature_to_display < 10)
  {
 // do the following if integer No1_cht_temperature is less than 10
  lcd.setCursor(start_of_blanking_column_number,1);
  lcd.print("     ");
  lcd.setCursor(single_digit_column_number,1);
  lcd.print(No2_cht_temperature_to_display);
  }
  if  (No2_cht_temperature_to_display > 9 && No2_cht_temperature_to_display < 100)
  {
  lcd.setCursor(start_of_blanking_column_number,1);
  lcd.print("     ");
  lcd.setCursor(double_digit_column_number,1);
  lcd.print(No2_cht_temperature_to_display);
  }
  if (No2_cht_temperature_to_display > 99)
  {
  // do the following if integer average_No2_cht_temperature is 100 or higher
  lcd.setCursor(start_of_blanking_column_number,1);
  lcd.print("     ");
  lcd.setCursor(triple_digit_column_number,1);
  lcd.print(No2_cht_temperature_to_display);
  }
  // End of No2 CHT
  //----------------------------------------------------------
  // start of No3 CHT display code
  // zero and range are set to 0 to 800 from 1 volt to 5 volts
  // in the map function below
  No3_cht_temperature_to_display = average_No3_cht_temperature;
  No3_cht_temperature_to_display = map(No3_cht_temperature_to_display, 199, 1012, 0, 800);
//                                          , raw zero, raw range, final zero, final range
  if  (No3_cht_temperature_to_display < 0)
  {
       No3_cht_temperature_to_display = 0; // as range is 0 to 800 cut off values below 4mA i.e. loop open circuit
  }
  if (No3_cht_temperature_to_display > 800)
  {
      No3_cht_temperature_to_display = 800;
  }
  // --------------------------------------------------------------
  // start of the No3 CHT temperature is high alarm routine
  // -------------------------------------------------------------- 
  if (No3_cht_temperature_to_display > cylinder_head_alarm_temperature)
  {
    No3_cht_temperature_is_high = true;
  }
 else
  {
     No3_cht_temperature_is_high = false;
  }
  // -------------------------------------------------------------
  // end of the No3 CHT temperature is high alarm routine
  // -------------------------------------------------------------
  // start of the display routines
  if (No3_cht_temperature_to_display < 10)
  // temperature in the range 0c to 9c
  {
  lcd.setCursor(start_of_blanking_column_number,2);
  lcd.print("     ");
  lcd.setCursor(single_digit_column_number,2);
  lcd.print(No3_cht_temperature_to_display);
  }
  //----------------------------------------------  
   if (No3_cht_temperature_to_display > 9 && No3_cht_temperature_to_display < 100)
   // temperature in the range 10c to 99c
  {
    lcd.setCursor(start_of_blanking_column_number,2);
    lcd.print("     ");
    lcd.setCursor(double_digit_column_number,2);
    lcd.print(No3_cht_temperature_to_display);
  }
  //----------------------------------------------
   if (No3_cht_temperature_to_display >99)
   // temperature in the range 100c to 800c
  {
    lcd.setCursor(start_of_blanking_column_number,2);
    lcd.print("     ");
    lcd.setCursor(triple_digit_column_number,2);
    lcd.print(No3_cht_temperature_to_display);
  }
  //----------------------------------------------
  // end of No3 CHT display code
  // ------------------------------------------------------
  // start of of No4 CHT display code
  // zero and range are set to 0 to +800 from 1 volt to 5 volts
  // in the map function below
  No4_cht_temperature_to_display = average_No4_cht_temperature;
  No4_cht_temperature_to_display = map(No4_cht_temperature_to_display, 199, 1013, 0, 800);
  //                                        , raw aero, raw range, final zero, final range 
   if  (No4_cht_temperature_to_display < 0)
  {
           No4_cht_temperature_to_display = 0;
  }
   if  (No4_cht_temperature_to_display > 800)
  {
           No4_cht_temperature_to_display = 800;
  }
    // --------------------------------------------------------------
  // start of the No4 CHT temperature is high alarm routine
  // -------------------------------------------------------------- 
  if (No4_cht_temperature_to_display > cylinder_head_alarm_temperature)
  {
    No4_cht_temperature_is_high = true;
  }
 else
  {
     No4_cht_temperature_is_high = false;
  }
  // -------------------------------------------------------------
  // end of the No4 CHT temperature is high alarm routine
  // -------------------------------------------------------------
//  start of the display routines
  if (No4_cht_temperature_to_display < 10)
  // temperature in the range 0c to 9c
  {
  lcd.setCursor(start_of_blanking_column_number,3);
  lcd.print("     ");
  lcd.setCursor(single_digit_column_number,3);       // set cursor to column 14, row 0 (the first row)
  lcd.print(No4_cht_temperature_to_display);         // change this text to whatever you like. keep it clean.
  }
  //----------------------------------------------  
   if (No4_cht_temperature_to_display > 9 && No3_cht_temperature_to_display < 100)
   // temperature in the range 10c to 99c
  {
    lcd.setCursor(start_of_blanking_column_number,3);
    lcd.print("     ");
    lcd.setCursor(double_digit_column_number,3);      // set cursor to column 14, row 0 (the first row)
    lcd.print(No4_cht_temperature_to_display);        // change this text to whatever you like. keep it clean.
  }
  //----------------------------------------------
   if (No4_cht_temperature_to_display >99)
   // temperature in the range 100c to 800c
  {
    lcd.setCursor(start_of_blanking_column_number,3);
    lcd.print("     ");
    lcd.setCursor(triple_digit_column_number,3);      // set cursor to column 14, row 0 (the first row)
    lcd.print(No4_cht_temperature_to_display);        // change this text to whatever you like. keep it clean.
  }
  //------------------------------------------------
  // end of No4 CHT display code
  // -----------------------------------------------
  // --------------------------------------------------------------
  // start of alarm combining routine
  // -------------------------------------------------------------- 
if (No1_cht_temperature_is_high || No2_cht_temperature_is_high || No3_cht_temperature_is_high || No4_cht_temperature_is_high)
{
    digitalWrite(alarm_led_output, HIGH);
    delay(100);
    digitalWrite(alarm_led_output, LOW);
    delay(100);
}
else
{
    digitalWrite(alarm_led_output, LOW);
}
  // -------------------------------------------------------------
  // end of alarm combining routine
  // -------------------------------------------------------------  

  }
// curlywig on line above is the closing bracket for
// the end of main loop which scannes and writes out the data
//----------------------------------------------------------

/*
 Solar charger shield voltage measurement example. Connect VBAT pin to analog pin A0.

 The pin measures 2.0 V when not under direct exposre to sunlight and 5V when exposed to sunlight.

 This example code is in the public domain.
 http://www.seeedstudio.com/wiki/index.php?title=Solar_Charger_Shield_v2.0b
 */

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A6;  // Analog input pin that the VBAT pin is attached to

int BatteryValue = 0;        // value read from the VBAT pin
float outputValue = 0;        // variable for voltage calculation


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  BatteryValue = analogRead(analogInPin);
  // Calculate the battery voltage value
  outputValue = (float(BatteryValue) * 5) / 1023 * 2;
  
  // print the results to the serial monitor:
  Serial.print("Analog value = ");
  Serial.print(BatteryValue);
  Serial.print("\t voltage = ");
  Serial.print(outputValue);
  Serial.println("V \n");
    
  // wait 10 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(1000);
}

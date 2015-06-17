/*
 * LCD RS pin to digital pin 8
 * LCD Enable pin to digital pin 9
 * LCD D4 pin to digital pin 4
 * LCD D5 pin to digital pin 5
 * LCD D6 pin to digital pin 6
 * LCD D7 pin to digital pin 7
(
    D4-D7    -> LCD Data transmission
    D8       -> Reset pin
    D9       -> Enable pin
    D10      -> Backlight control
)

 Mega IO Expansion Shield V2
 1 microSD slot (SCK=52, MISO=50, MOSI=51 and SS=53)
 http://www.dfrobot.com/wiki/index.php/Mega_IO_Expansion_Shield_V2%28SKU:DFR0165%29

 Взаимодействие между микроконтроллером и SD-картой памяти осуществляется по шине SPI,
 объединяющей в себе выводы 11, 12 и 13 (на большинстве плат Ардуино),
 либо 50, 51 и 52 (на Arduino Mega).
 Помимо перечисленных, еще один вывод должен использоваться для активизации SD-карты.
 Для этого может использоваться как аппаратный вывод SS - вывод 10
 (на большинстве плат Ардуино) или вывод 53 (на Arduino Mega), так и любой другой вывод,
 указанный при вызове метода SD.begin(). Обратите внимание,
 что для корректной работы библиотеки SD, вывод SS должен быть сконфигурирован как выход,
 даже в тех случаях, когда он не используется.
  * SD card attached to SPI bus as follows:
 ** MOSI - pin 51
 ** MISO - pin 50
 ** CLK - pin 52
 ** CS - pin 53
 
 18b20 - tester
 sd - logger
 */

#include <SPI.h>
#include <SD.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2
#define TEMPERATURE_PRECISION 9

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// Number of temperature devices found
int numberOfDevices;

// We'll use this variable to store a found device address
DeviceAddress tempDeviceAddress;

// Выбор чипа для SD
const int chipSelect = 53;

// initialize the library with the numbers of the interface pins
LiquidCrystal  lcd (8, 9, 4, 5, 6, 7);

//Key message
char msgs[5][15] = {"Right Key OK ",
                    "Up Key OK    ",
                    "Down Key OK  ",
                    "Left Key OK  ",
                    "Select Key OK"
                   };
int  adc_key_val[5] = {  30,
                         150,
                         360,
                         535,
                         760
                      };
int NUM_KEYS = 5;
int adc_key_in;
int key = -1;
int oldkey = -1;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(5, 0);           //line=0, x=0
  lcd.write("MENU:");
  lcd.setCursor(5, 1);           //line=1, x=0
  lcd.write("press a key");

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(chipSelect, OUTPUT);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");

  lcd.setCursor(5, 1);           //line=1, x=5
  lcd.print("            ");
}
void loop() {
  adc_key_in = analogRead(0);    // читаем значение из аналогового входа
  key = get_key(adc_key_in);     // конвертируем в нажатие кнопки
  if (key != oldkey) {           // если книпка нажата
    delay(50);		         // ждем чтоб устранить дребезг
    adc_key_in = analogRead(0);  // читаем значение из аналогового входа
    key = get_key(adc_key_in);	 // конвертируем в нажатие кнопки
    if (key != oldkey) {
      oldkey = key;
      if (key >= 0) {
        lcd.setCursor(0, 2);     //line=2, x=0
        lcd.write(msgs[key]);
      }
    }
  }
}

// конвертируем аналоговое значение в код кнопки
int get_key(unsigned int input) {
  int k;
  for (k = 0; k < NUM_KEYS; k++) {
    if (input < adc_key_val[k]) {
      return k;
    }
  }
  if (k >= NUM_KEYS)
    k = -1;// пришло некорректное значение
  return k;
}

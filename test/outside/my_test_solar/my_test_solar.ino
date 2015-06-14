/*
 http://www.seeedstudio.com/wiki/index.php?title=Solar_Charger_Shield_v2.0b
*/

const int GreenLed    = 13;  // пин Зелёного светодиода
const int VBATinPin   = A2;  // аналоговый пин АКБ
const int SOLARinPin  = A1;  // аналоговый пин Панели

int TimeDelay         = 1000;// значение в милисекундах
int GreenLedState     = LOW; // состояние Зелёного светодиода
int GreenLedStateLow  = LOW; // состояние Зелёного светодиода выключено
int GreenLedStateHigh = HIGH;// состояние Зелёного светодиода включено
int VBATvalue         = 0;   // значение АЦП для АКБ
int SOLARvalue        = 0;   // значение АЦП для Панели
float VBATfloatValue  = 0;   // значение напряжения АКБ
float SOLARfloatValue = 0;   // значение напряжения Панели

void setup() {
  
  while (!Serial) {
    // wait for serial port to connect. Needed for Leonardo only
    ;
  }
  
  Serial.begin(9600);
  Serial1.begin(9600);

  // зададим светодиод как выход
  pinMode(GreenLed, OUTPUT);
  // включим светодиод
  digitalWrite(GreenLed, GreenLedStateHigh);
}

void loop() {
  // считаем аналоговые значения:
  VBATvalue  = analogRead(VBATinPin);
  SOLARvalue = analogRead(SOLARinPin);
  
  // пересчитаем значения
  VBATfloatValue  = (float(VBATvalue)  * 5) / 1023 * 2;
  SOLARfloatValue = (float(SOLARvalue) * 5) / 1023 * 3;

  // выдать результат в серийный порт 0
  Serial.print("$");
  Serial.print(VBATvalue);
  Serial.print(";");
  Serial.print(VBATfloatValue);
  Serial.print(";");
  Serial.print(SOLARvalue);
  Serial.print(";");
  Serial.print(SOLARfloatValue);
  Serial.print("\t\n");

  // выдать результат в серийный порт 1
  Serial1.print("$");
  Serial1.print(VBATvalue);
  Serial1.print(";");
  Serial1.print(SOLARvalue);
  Serial1.print("\t\n");

  // if the LED is off turn it on and vice-versa:
  if (GreenLedState == LOW)
    GreenLedState = HIGH;
  else
    GreenLedState = LOW;

  // ждём заданный интервал
  delay(TimeDelay);
}

void GreenLedOn() {
  digitalWrite(GreenLed, GreenLedStateHigh);
}

void GreenLedOff() {
  digitalWrite(GreenLed, GreenLedStateLow);
}

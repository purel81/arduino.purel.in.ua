/*
 http://www.seeedstudio.com/wiki/index.php?title=Solar_Charger_Shield_v2.0b
*/

const int GreenLed    = 13;  // пин Зелёного светодиода
// const int VBATinPin   = A2;  // аналоговый пин АКБ
// const int SOLARinPin  = A1;  // аналоговый пин Панели
const int AnalogInPin  = A3;  // аналоговый пин

int TimeDelay         = 1000;// значение в милисекундах
int GreenLedState     = LOW; // состояние Зелёного светодиода
int GreenLedStateLow  = LOW; // состояние Зелёного светодиода выключено
int GreenLedStateHigh = HIGH;// состояние Зелёного светодиода включено
// int VBATvalue         = 0;   // значение АЦП для АКБ
// int SOLARvalue        = 0;   // значение АЦП для Панели
int ANALOGvalue        = 0;   // значение АЦП для Панели
// float VBATfloatValue  = 0;   // значение напряжения АКБ
// float SOLARfloatValue = 0;   // значение напряжения Панели
float ANALOGfloatValue = 0;   // значение напряжения Панели

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
  GreenLedOn();
}

void loop() {
  
  GreenLedOn();
  
  // считаем аналоговые значения:
  // VBATvalue  = analogRead(VBATinPin);
  // SOLARvalue = analogRead(SOLARinPin);
  ANALOGvalue = analogRead(AnalogInPin);
  
  // пересчитаем значения
  // VBATfloatValue   = (float(VBATvalue)  * 5) / 1023 * 2;
  // SOLARfloatValue  = (float(SOLARvalue) * 5) / 1023 * 3;
  ANALOGfloatValue = (float(ANALOGvalue) * 5) / 1023;

  // выдать результат в серийный порт 0
  Serial.print("$");
  //Serial.print(VBATvalue);
  //Serial.print(";");
  //Serial.print(VBATfloatValue);
  //Serial.print(";");
  //Serial.print(SOLARvalue);
  //Serial.print(";");
  //Serial.print(SOLARfloatValue);
  Serial.print(";");
  Serial.print(ANALOGvalue);
  Serial.print(";");
  Serial.print(ANALOGfloatValue);
  Serial.print("\t\n");

  // выдать результат в серийный порт 1
  Serial1.print("$");
  //Serial1.print(VBATvalue);
  //Serial1.print(";");
  //Serial1.print(SOLARvalue);
  Serial1.print(ANALOGvalue);
  Serial1.print(";");
  Serial1.print(ANALOGfloatValue);
  Serial1.print("\t\n");
  
  GreenLedOff();
  
  // ждём заданный интервал
  delay(TimeDelay);
}

void GreenLedOn() {
  digitalWrite(GreenLed, GreenLedStateHigh);
}

void GreenLedOff() {
  digitalWrite(GreenLed, GreenLedStateLow);
}

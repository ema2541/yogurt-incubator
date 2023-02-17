#include "Max6675.h"

// Output pin to activate incubator
int pin_fan = 2; // กำหนดขาพัดลม
int pin_heater = 4; // กำหนดขา heater
float temperature = 0.0; // กำหนดค่าเริ่มต้นของอุณหภูมิ (Celsius)

Max6675 ts(8, 9, 10); // ขา input รับอุณหภูมิ
// Max6675 module: SO on pin #8, SS on pin #9, CSK on pin #10 of Arduino UNO
// Other pins are capable to run this library, as long as digitalRead works on SO,
// and digitalWrite works on SS and CSK

void setup()
{
  pinMode(pin_fan, OUTPUT); // กำหนดขาทำหน้าที่ให้ขา 2 เป็น OUTPUT
  pinMode(pin_heater, OUTPUT); // กำหนดขาทำหน้าที่ให้ขา 4 เป็น OUTPUT

  digitalWrite(pin_fan, LOW);
  digitalWrite(pin_heater, LOW);

  ts.setOffset(0);
  // set offset for temperature measurement.
  // 1 stannds for 0.25 Celsius

  Serial.begin(9600);
}


void loop()
{
  temperature = ts.getCelsius();
  Serial.println(temperature, 2);

  if (temperature >= 45.00) {
    digitalWrite(pin_fan, LOW);  // ส่งให้ไฟดับ
    digitalWrite(pin_heater, LOW); // ส่งให้ไฟดับ
    Serial.println(String("Deactivate fan and heater at temperature: ") + String(temperature, 2));
  } else if (temperature <= 40.00) {
    digitalWrite(pin_fan, HIGH);  // ส่งให้ไฟติด
    digitalWrite(pin_heater, HIGH); // ส่งให้ไฟติด
    Serial.println(String("Activate fan and heater at temperature: ") + String(temperature, 2)); 
  }

  delay(1000);

}
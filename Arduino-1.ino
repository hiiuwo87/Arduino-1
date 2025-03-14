#include <LiquidCrystal.h>

// تعريف شاشة LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int batteryPin = A0; // المدخل التناظري لقراءة جهد البطارية
const float referenceVoltage = 1; // الجهد المرجعي الداخلي لـ Arduino
float batteryVoltage = 0.0;
float batteryPercentage = 0.0;
float factor = 0.99; // نسبة مقسم الجهد (إذا كنت تستخدمه)

// تعريف صفارة تحذير عند انخفاض البطارية
const int buzzerPin = 9;

void setup() {
    Serial.begin(9600);
    lcd.begin(16, 2);
    pinMode(buzzerPin, OUTPUT);
    
    lcd.print("Battery Monitor");
    delay(2000);
    lcd.clear();
}

void loop() {
   
    int rawValue = analogRead(batteryPin);
    

    batteryVoltage = (rawValue * (5.0 / 1023.0)) * factor;
    
    
    if (batteryVoltage >= 4.2) batteryPercentage = 100;
    else if (batteryVoltage >= 4.1) batteryPercentage = 90;
    else if (batteryVoltage >= 4.0) batteryPercentage = 80;
    else if (batteryVoltage >= 3.9) batteryPercentage = 70;
    else if (batteryVoltage >= 3.8) batteryPercentage = 60;
    else if (batteryVoltage >= 3.7) batteryPercentage = 50;
    else if (batteryVoltage >= 3.6) batteryPercentage = 40;
    else if (batteryVoltage >= 3.5) batteryPercentage = 30;
    else if (batteryVoltage >= 3.4) batteryPercentage = 20;
    else if (batteryVoltage >= 3.3) batteryPercentage = 10;
    else batteryPercentage = 0;


    lcd.setCursor(0, 0);
    lcd.print("Voltage: ");
    lcd.print(batteryVoltage, 2);
    lcd.print("V   ");

    lcd.setCursor(0, 1);
    lcd.print("Charge: ");
    lcd.print(batteryPercentage);
    lcd.print("%   ");


    Serial.print("Battery Voltage: ");
    Serial.print(batteryVoltage, 2);
    Serial.print(" V | Charge: ");
    Serial.print(batteryPercentage);
    Serial.println("%");

    
    if (batteryPercentage <= 20) {
        digitalWrite(buzzerPin, HIGH);
        delay(500);
        digitalWrite(buzzerPin, LOW);
    }

    delay(1000); 
}

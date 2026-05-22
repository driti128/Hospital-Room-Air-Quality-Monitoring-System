#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int sensorPin = A0;

int greenLED = 6;
int redLED = 7;
int yellowLED = 8;
int buzzer = 9;

int value;

void setup()
{
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
}

void loop()
{
  value = analogRead(sensorPin);

  lcd.clear();

  // GOOD AIR
  if (value <= 550)
  {
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);
    digitalWrite(buzzer, LOW);

    lcd.setCursor(0, 0);
    lcd.print("Air Good");
  }

  // MODERATE AIR
  else if (value <= 650)
  {
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, LOW);
    digitalWrite(buzzer, LOW);

    digitalWrite(yellowLED, HIGH);
    delay(300);
    digitalWrite(yellowLED, LOW);
    delay(300);

    lcd.setCursor(0, 0);
    lcd.print("Moderate Air");
  }

  // BAD AIR
  else
  {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);

    lcd.setCursor(0, 0);
    lcd.print("Air Bad");

    // 🔔 Buzzer beep properly
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(500);
  }

  lcd.setCursor(0, 1);
  lcd.print("Val: ");
  lcd.print(value);

  delay(200);
}
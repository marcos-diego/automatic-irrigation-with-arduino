#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2, POSITIVE);

#define sensor_pin A0
#define red_LED_pin 9
#define blue_LED_pin 10
#define green_LED_pin 12
#define relay_waterpump 8
 
void setup()
{
  Serial.begin(9600);
  pinMode(sensor_pin, INPUT);
  pinMode(red_LED_pin, OUTPUT);
  pinMode(blue_LED_pin, OUTPUT);
  pinMode(green_LED_pin, OUTPUT);
  pinMode(relay_waterpump, OUTPUT);

  digitalWrite(relay_waterpump, LOW);

  lcd.begin(16, 2);
}

 
void loop()
{
  // Read the value of sensor pin A0
  int value_porcentage = analogRead(A0);
  int analog_value = map(value_porcentage, 0, 1023, 0, 100);
  lcd.clear();
 
  // Displays the value of analog port on the serial monitor
  Serial.print("Analog port: ");
  Serial.print(analog_value);

  // Displays the percentage value of analog port on the LCD display
  lcd.setBacklight(HIGH);
  lcd.setCursor(13, 0);
  lcd.print("analog value");
  lcd.print("%");

  //=================================================================================
 
  // Moist soil, lights the green LED
  if (analog_value > 50)
  {
    Serial.println("Moist soil");
    lowLEDs();
    digitalWrite(green_LED_pin, HIGH);

    // Display moisture status on the LCD display
    lcd.setBacklight(HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Moist soil");
    lcd.setCursor(0, 1);
    lcd.print("Pump off");
    digitalWrite(relay_waterpump, LOW);
  }

  //=================================================================================
 
  // Soil with moderate humidity, blue LED light
  if (analog_value < 50 && analog_value > 30)
  {
    Serial.println("moderate humidity");
    lowLEDs();
    digitalWrite(blue_LED_pin, HIGH);

    // Display moisture status on the LCD display
    lcd.setBacklight(HIGH);
    lcd.setCursor(0, 0);
    lcd.print("moderate humidity");
    lcd.setCursor(0, 1);
    lcd.print("Pump off");
    digitalWrite(relay_waterpump, LOW);
  }

  //=================================================================================
 
  // Dry soil, red LED light
  if (analog_value < 20 && analog_value >= 0)
  {
    Serial.println("Dry soil");
    lowLEDs();
    digitalWrite(red_LED_pin, HIGH);

    lcd.setCursor(0, 0);
    lcd.setBacklight(HIGH);
    lcd.print("Dry soil");
    lcd.setCursor(0, 1);
    lcd.print("Pump off");
    digitalWrite(relay_waterpump, HIGH);
  }
  delay(1000);
  
}

//=================================================================================
 
void lowLEDs()
{
  digitalWrite(red_LED_pin, LOW);
  digitalWrite(blue_LED_pin, LOW);
  digitalWrite(green_LED_pin, LOW);
}

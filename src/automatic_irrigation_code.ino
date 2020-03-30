/* ====================================================================================================================
    Project: Automatic Watering System
    Developers coder: Marcos Santos and André Souza
    Last update: September 14, 2019
====================================================================================================================== */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Defines the pins that will be used to connect to the lcd display
LiquidCrystal_I2C lcd(0x27, 16, 2, POSITIVE);

#define sensor_pin A0        // define sensor pin
#define red_LED_pin 9        // define red LED pin
#define blue_LED_pin 10      // define blue LED pin
#define green_LED_pin 12     // define green LED pin
#define relay_waterpump 8    // define water pump pin
 
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
  Serial.print("Porta analogica: ");
  Serial.print(analog_value);

  // Displays the percentage value of analog port on the LCD display
  lcd.setBacklight(HIGH);
  lcd.setCursor(13, 0);
  lcd.print("valor_analogico");
  lcd.print("%");

  //=================================================================================
 
  // Moist soil, lights the green LED
  if (analog_value > 50)
  {
    Serial.println(" Status: Solo úmido");
    lowLEDs();
    digitalWrite(green_LED_pin, HIGH);

    // Display moisture status on the LCD display
    lcd.setBacklight(HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Solo úmido");
    lcd.setCursor(0, 1);
    lcd.print("Bomba desligada");
    digitalWrite(relay_waterpump, LOW);
  }

  //=================================================================================
 
  // Soil with moderate humidity, blue LED light
  if (analog_value < 50 && analog_value > 30)
  {
    Serial.println(" Status: Humidade Moderada");
    lowLEDs();
    digitalWrite(blue_LED_pin, HIGH);

    // Display moisture status on the LCD display
    lcd.setBacklight(HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Humidade Moderada");
    lcd.setCursor(0, 1);
    lcd.print("Bomba desligada");
    digitalWrite(relay_waterpump, LOW);
  }

  //=================================================================================
 
  // Dry soil, red LED light
  if (analog_value < 20 && analog_value >= 0)
  {
    Serial.println(" Status: Solo seco");
    lowLEDs();
    digitalWrite(red_LED_pin, HIGH);

    lcd.setCursor(0, 0);
    lcd.setBacklight(HIGH);
    lcd.print("Solo seco");
    lcd.setCursor(0, 1);
    lcd.print("Bomba ligada");
    digitalWrite(relay_waterpump, HIGH);
    //delay(1000);
    //digitalWrite(relay_waterpump, LOW);
    //delay(5000);
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

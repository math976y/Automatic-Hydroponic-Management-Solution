/**
 * DHT11 Sensor Reader
 * This sketch reads temperature and humidity data from the DHT11 sensor and prints the values to the serial port.
 * It also handles potential error states that might occur during reading.
 *
 * Author: Dhruba Saha
 * Version: 2.1.0
 * License: MIT
 */

// Include the DHT11 library for interfacing with the sensor.
#include <DHT11.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Create an instance of the DHT11 class.
// - For Arduino: Connect the sensor to Digital I/O Pin 2.
// - For ESP32: Connect the sensor to pin GPIO2 or P2.
// - For ESP8266: Connect the sensor to GPIO2 or D4.
DHT11 dht11(4);
LiquidCrystal_I2C lcd(0x27,20,4);

bool HumidifierON = true;

void setup() {
    // Initialize serial communication to allow debugging and data readout.
    // Using a baud rate of 9600 bps.
    Serial.begin(9600);
    
    pinMode(9, OUTPUT);

    lcd.init();

    // Uncomment the line below to set a custom delay between sensor readings (in milliseconds).
    // dht11.setDelay(500); // Set this to the desired delay. Default is 500ms.
}

void loop() {
    int temperature = 0;
    int humidity = 0;

    // Attempt to read the temperature and humidity values from the DHT11 sensor.
    int result = dht11.readTemperatureHumidity(temperature, humidity);

    // Check the results of the readings.
    // If the reading is successful, print the temperature and humidity values.
    // If there are errors, print the appropriate error messages.
    lcd.clear();
    if (result == 0) {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print(" °C\tHumidity: ");
        Serial.print(humidity);
        Serial.println("%");


        // Print a message to the LCD.
        lcd.backlight();
        lcd.setCursor(2,0);
        lcd.print("Temperature: ");
        lcd.print(temperature);
        lcd.print("C");
        lcd.setCursor(2,1);
        lcd.print("Humidity:    ");
        lcd.print(humidity);
        lcd.print("%");

    } else {
        // Print error message based on the error code.
        Serial.println(DHT11::getErrorString(result));
    }

    if (humidity <= 60) {
        Serial.println("Humidifier active");

        lcd.setCursor(2,2);
        lcd.print("Humidifier active");

        if(HumidifierON == false){
            digitalWrite(9,LOW);
            delay(50);
            digitalWrite(9,HIGH);
            delay (50);
            HumidifierON = true;
        }

    } else {
        if(HumidifierON == true){
        digitalWrite(9,LOW);
        delay(50);
        digitalWrite(9,HIGH);
        delay(50);
        digitalWrite(9,LOW);
        delay(50);
        digitalWrite(9,HIGH);
        delay(50);
        HumidifierON = false;
        }

    }


}

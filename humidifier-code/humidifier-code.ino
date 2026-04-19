#include <DHT.h>
#include <DHT_U.h>

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
//#include <DHT11.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

// Uncomment whatever DHT sensor type you're using
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)   

// Initialize DHT sensor
DHT dht(18, DHTTYPE);

WiFiMulti wifiMulti;


// Create an instance of the DHT11 class.
// - For Arduino: Connect the sensor to Digital I/O Pin 2.
// - For ESP32: Connect the sensor to pin GPIO2 or P2.
// - For ESP8266: Connect the sensor to GPIO2 or D4.
//DHT11 dht11(18);
LiquidCrystal_I2C lcd(0x27,20,4);

bool HumidifierON = true;
float temperature = 0;
float humidity = 0;

    // Declare task handle
TaskHandle_t BlinkTaskHandle = NULL;

void BlinkTask(void *parameter) {
  for (;;) { // Infinite loop
    if ((wifiMulti.run() == WL_CONNECTED)) {
        HTTPClient http;

        Serial.print("[HTTP] begin...\n");
        // configure traged server and url
        String url = "http://192.168.0.100:5173/api/trpc/setHumidifierVal?input={%22temperature%22:" + String(temperature) + ",%22humidity%22:" + String(humidity) +"}";
        http.begin(url);  //HTTP

        Serial.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            Serial.println(payload);
        }
        } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}



void setup() {
    // Initialize serial communication to allow debugging and data readout.
    // Using a baud rate of 9600 bps.
    Serial.begin(9600);
    
    Wire.begin(6,7);

    pinMode(19, OUTPUT);

    lcd.init();

    // Uncomment the line below to set a custom delay between sensor readings (in milliseconds).
    // dht11.setDelay(500); // Set this to the desired delay. Default is 500ms.

    wifiMulti.addAP("HOTSPOT-1", "MercanSpot2024!");

    xTaskCreatePinnedToCore(
    BlinkTask,         // Task function
    "BlinkTask",       // Task name
    10000,             // Stack size (bytes)
    NULL,              // Parameters
    1,                 // Priority
    &BlinkTaskHandle,  // Task handle
    0                  // Core 1
  );


}

void loop() {

    // Attempt to read the temperature and humidity values from the DHT11 sensor.
    //int result = dht11.readTemperatureHumidity(temperature, humidity);
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();

    // Check the results of the readings.
    // If the reading is successful, print the temperature and humidity values.
    // If there are errors, print the appropriate error messages.
    lcd.clear();
    if (true) {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print(" °C\tHumidity: ");
        Serial.print(humidity);
        Serial.println("%");


        // Print a message to the LCD.
        lcd.backlight();
        lcd.setCursor(0,0);
        lcd.print("Temperature: ");
        lcd.print(temperature);
        lcd.print("C");
        lcd.setCursor(0,1);
        lcd.print("Humidity:    ");
        lcd.print(humidity);
        lcd.print("%");

    } else {
    }

    if (humidity <= 60) {
        Serial.println("Humidifier active");

        lcd.setCursor(0,2);
        lcd.print("Humidifier active");

        if(HumidifierON == false){
            digitalWrite(19,LOW);
            delay(50);
            digitalWrite(19,HIGH);
            delay (50);
            HumidifierON = true;
        }

    } else {
        if(HumidifierON == true){
        digitalWrite(19,LOW);
        delay(50);
        digitalWrite(19,HIGH);
        delay(50);
        digitalWrite(19,LOW);
        delay(50);
        digitalWrite(19,HIGH);
        delay(50);
        HumidifierON = false;
        }

    }




    vTaskDelay(100 / portTICK_PERIOD_MS);
}



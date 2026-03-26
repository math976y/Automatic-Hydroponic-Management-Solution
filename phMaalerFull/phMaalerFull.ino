/**
 * 
  *  Full example for PH4502C_Sensor.h
  * 
  *  By: Nathanne Isip
  *  27/06/2023
  * 
  */

#include <ph4502c_sensor.h>

// Define the pH level pin and temperature pin
#define PH4502C_PH_LEVEL_PIN A0 // Po
#define PH4502C_TEMP_PIN A1 // To

// Create an instance of the PH4502C_Sensor
PH4502C_Sensor ph4502(PH4502C_PH_LEVEL_PIN, PH4502C_TEMP_PIN);

float avgAr[] = {0. , 0. , 0. , 0. , 0. , 0. , 0. , 0. , 0. , 0.};
int avgLen = 10;
int avgInd = 0;

void setup() {

    Serial.begin(9600);

    // Initialize the PH4502 instance
    ph4502.init();
    
}

void loop() {

    // Read the temperature from the sensor
    float temp = float( ph4502.read_temp() ) * 21. / 750.;
    Serial.println("Temperature reading: "
        + String(temp));

    // Read the pH level by average

    // read 7 = 7
    // read 6.53 = 4

    // f(x) = 6.38x - 37.68

    float indPh = ph4502.read_ph_level_single();

    avgAr[avgInd] = indPh;

    avgInd++;
    avgInd %= avgLen;

    float ph = 0.;

    for(int i = 0; i < avgLen; i++){

        ph += avgAr[i];

    }

    ph /= float(avgLen);

    Serial.println("pH Level Reading: "
        + String(ph));

    // There is also this ph4502.read_ph_level_single()

    delay(500);
}
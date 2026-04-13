// Define the pH level pin and temperature pin
#define PH4502C_PH_LEVEL_PIN A0 // Po
#define PH4502C_TEMP_PIN A1 // To

float avgAr[] = {0. , 0. , 0. , 0. , 0. , 0. , 0. , 0. , 0. , 0.};
int avgLen = 10;
int avgInd = 0;

float x_0 = 677.;
float y_0 = 7.01;

float x_1 = 787.;
float y_1 = 4.01;

float a;
float b;

void setup() {

    Serial.begin(9600);

    a = (y_1 - y_0) / (x_1 - x_0);
    b = y_0 - a * x_0;
    
}

float linear( float x ){

    return (-5.7 * x *5.)/1024. + (21.34 + (7. - 2.41));

  //return a * x + b;

}

void loop() {

    // Read the pH level by average

    float indPh = analogRead( PH4502C_PH_LEVEL_PIN );

    indPh = linear(indPh);

    avgAr[avgInd] = indPh;

    avgInd++;
    avgInd %= avgLen;

    float ph = 0.;
    for(int i = 0; i < avgLen; i++){

        ph += avgAr[i];

    }

    ph /= float(avgLen);

    Serial.println("pH Level Reading: " + String( indPh ) );

    delay(500);
}
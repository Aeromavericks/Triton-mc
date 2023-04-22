#include "HX711.h"

//Start commenting: If using an Arduino
const int sens_1 = PA0;
const int sens_2 = PA1;
const int sens_3 = PA2;
const int sens_4 = PA3;
const int sens_5 = PA4;
const int sens_6 = PA5;
const int sens_7 = PA6;
const int sens_8 = PA7;
const int sens_9 = PB0;
const int sens_10 = PB1;
//Stop comment

//Start commenting: If using an STM32
/*
const int sens_1 = A0;
const int sens_2 = A1;
const int sens_3 = A2;
const int sens_4 = A3;
const int sens_5 = A4;
const int sens_6 = A5;
*/
//Stop comment

const int CLK = 2;
const int DOUT = 3;

HX711 scale;

float calibration_factor = -8440; 
const unsigned long BAUD_RATE = 115200;

void setup()
{
    pinMode(sens_1, INPUT_ANALOG);
    pinMode(sens_2, INPUT_ANALOG);
    pinMode(sens_3, INPUT_ANALOG);
    pinMode(sens_4, INPUT_ANALOG);
    pinMode(sens_5, INPUT_ANALOG);
    pinMode(sens_6, INPUT_ANALOG);
    pinMode(sens_7, INPUT_ANALOG);
    pinMode(sens_8, INPUT_ANALOG);
    pinMode(sens_9, INPUT_ANALOG);
    pinMode(sens_10, INPUT_ANALOG);

    Serial.begin(BAUD_RATE);

  scale.begin(DOUT, CLK);
  scale.set_scale(); // obtained with 20lb weight
  scale.tare(); //Reset the scale to 0

    long zero_factor = scale.read_average();
}


void loop(){

    scale.set_scale(calibration_factor); //Adjust to this calibration factor

    int sens_1_val, sens_2_val, sens_3_val, sens_4_val, sens_5_val,
        sens_6_val, sens_7_val, sens_8_val, sens_9_val, sens_10_val;
    
    sens_1_val = analogRead(sens_1);
    sens_2_val = analogRead(sens_2);
    sens_3_val = analogRead(sens_3);
    sens_4_val = analogRead(sens_4);
    sens_5_val = analogRead(sens_5);
    sens_6_val = analogRead(sens_6);
    sens_7_val = analogRead(sens_7);
    sens_8_val = scale.get_units(5);
    sens_9_val = scale.read();
    sens_10_val = scale.get_value(5);

    sens_1_val = map(sens_1_val,102,1023,0,150);
    sens_2_val = map(sens_2_val,102,1023,0,150);
    sens_3_val = map(sens_3_val,102,1023,0,150);    

char buffer[70];
sprintf(buffer,"P, %d, %d, %d, %d, %d, %d, %d, %.2d, %d, %d ",sens_1_val, sens_2_val, sens_3_val, sens_4_val, sens_5_val, sens_6_val);
    Serial.println(buffer);
    
    delay(50);
}
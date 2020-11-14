/***************************************************************************
  This is a library for the BMP280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BMP280 Breakout
  ----> http://www.adafruit.com/products/2651

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/
/*
This is the V1 of the code for the data logger.
*/


#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_BMP280.h>


const int CS = 4  ;   //CS pin if the SD card reader 

double alt ;

Adafruit_BMP280 bmp;  // using I2C not SPI.


void setup() {
  pinMode(LED_BUILTIN , OUTPUT);
  digitalWrite(LED_BUILTIN , LOW);
  Serial.begin(9600);
  Serial.println("Data_Loger_V1");

// checking if sd and bmp280 are functioning. 
  if(!SD.begin(CS)){
    Serial.println("Card failed, or not present");
    while(1);
    }else{
    Serial.println("Card initialized");
    digitalWrite(LED_BUILTIN , HIGH);  //to confirm visually that SD is ok
    delay(2000);
    digitalWrite(LED_BUILTIN , LOW); 
    delay(500);
    }
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }else{
    digitalWrite(LED_BUILTIN , HIGH);  //to confirm visually that SD is ok
    delay(5000);
    digitalWrite(LED_BUILTIN , LOW); 
    }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void loop() {

//Serial prints are not needed for the rocket, they are just for debugging while on the ground
    alt = bmp.readAltitude(1016.39);   // Adjusted for local conditions
    Serial.print("Altitude = ");
    Serial.print(alt);
    Serial.println(" m");
    File datalog = SD.open("datalog.txt" , FILE_WRITE);
    if(datalog){
      datalog.print(alt);
      datalog.println(" ");
      }else{
        Serial.println("error opening datalog.txt");
      }  
    
}

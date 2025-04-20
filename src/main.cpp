//
// Created by kiryanenko on 14.09.19.
//

//////////////////////////////////////////////////////////////////
// Connections
//
// Uno:   SDA <-> A4 (SDA)
//        SCL <-> A5 (SCL)
//
// Mega:  SDA <-> 20 (SDA)
//        SCL <-> 21 (SCL)
//
// Leo:   SDA <-> 2 (SDA)
//        SCL <-> 3 (SCL)
//
//
// esp32: SDA <-> 21 (SDA)
//        SCL <-> 22 (SCL)
//
//////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include <Wire.h>
#include <TTP229.h>

TTP229 ttp229(22, 21); // SCL, SDA

void setup()
{
    Wire.begin();
    Serial.begin(115200);
}

void loop()
{
    //ReadKey8() - 8 buttons mode

    uint8_t key = ttp229.ReadKey16();
    Serial.print("Key: ");
    Serial.println(key);
    delay(1000);
}

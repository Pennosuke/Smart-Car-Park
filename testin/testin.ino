
#include <Arduino.h>
#include <Wire.h>

#define Ago 23
#define Ain 39

bool isAvail = false;

void gotRespond()
{
    isAvail = true;
    StopAskAvail();
}

void AskAvail()
{
    digitalWrite(Ago, HIGH);
}

void StopAskAvail()
{
    digitalWrite(Ago, LOW);
}

void setup()
{
    Serial.begin(9600);
    pinMode(Ago, OUTPUT);
    pinMode(Ain, INPUT);
    attachInterrupt(digitalPinToInterrupt(Ain), gotRespond, RISING);
    
}

void loop()
{
    AskAvail();
    unsigned long now = millis();
    while(millis()-now<3000 && isAvail==false) {
        ;
    }
    StopAskAvail();

    if(isAvail==true) {
        Serial.println("Got Avail");
        isAvail = false;
    }
    else {
        Serial.println("No respond");
    }

    delay(2000);
}

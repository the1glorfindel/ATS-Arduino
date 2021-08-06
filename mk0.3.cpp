//Start-over of a small arduino program to act as a control unit for an Automatic Transfer Switch
//MK0.3 Includes smarter delays to avoid relay bounce


//Libraries
#include <Arduino.h>

//Constant Integers

const int poweron = 3;
const int poweroff = 4;
const int transfersig = 5;


//Setup Code

void setup() {
    pinMode (poweron, OUTPUT);                             //Will output HIGH when Main Power Supply is On
    pinMode (poweroff, OUTPUT);                            //Will output HIGH when Main Power Supply is Off
    pinMode (transfersig, INPUT);                          //Will be input signal to control Power Transfer Switch
    Serial.begin(9600);
}


//Looped main program

void loop() {
    int transfertrigger = digitalRead(transfersig);       //set up a variable to store current Mains Electricity state
    if (transfertrigger == HIGH)                          //if the trigger is HIGH... 
    {
        delay(100);                                       //...wait 100ms...
        if (digitalRead(transfersig) == HIGH)             //...if still high...
        {
            delay(100);                                   //...wait additional 100ms...
            digitalWrite(poweroff, HIGH);                 //...and set poweroff pin HIGH to trigger power transfer to Backup Power Supply
            digitalWrite(poweron, LOW);                   //...and set poweron pin LOW.
        }
        
    }
    else                                                  //otherwise...
    {
        delay(200);                                       //...wait 200ms to avoid relay bounce...
        digitalWrite(poweron, HIGH);                      //...set the poweron pin to HIGH to trigger power transfer to Main Power Supply  
        digitalWrite(poweroff, LOW);
    }
    delay(100);
    Serial.println(transfersig);
    
}

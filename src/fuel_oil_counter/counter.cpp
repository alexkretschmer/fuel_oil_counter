/*
  counter.cpp 
  calculation heatoil 
  
*/

#include "Arduino.h"
#include "counter.h"


#define seconds() (MyMillis()/1000)
#define HourMillis 3600000
#define OverflowLimit 4233605000

unsigned long MMdelta = 0; //0xFFE488BF;   //30min befor overflow
void(* resetFunc) (void) = 0; //declare reset function @ address 0

unsigned long MyMillis()
{
 return millis()+ MMdelta;
}



Counter::Counter(int inPin,int LED) // Init sequence
{
  _inPin = inPin;
  _led = LED;
  
  // initialize the LED pin as an output:
  pinMode(LED, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(_inPin, INPUT_PULLUP);
  currActSec=0;
  _nextHour = HourMillis;
  active=false;
  _newPulse=false;
}


int Counter::Update (void)
  {
    //***************************
    // Update
    // return 0 = no clac
    //        1 = normal calc
    //        2 = next  hour with pulse
    //        3 = next hour without pulse
    //****************************
    unsigned long tempMlSummary;
    unsigned long diffTime;
    int tmpReturn=0;
    active = !digitalRead(_inPin);   //inverted module
      
    
    if(active && !_oldActive){
       _startTime = MyMillis();
       _newPulse = true;
       digitalWrite(_led,true);
    }
    else if(!active && _oldActive)
    {
      _stopTime = MyMillis();
      digitalWrite(_led,false);
    }
     _oldActive = active;
    
     if (MyMillis()>_nextHour){    // NEW HOUR
        tmpReturn = 3; // detection for Save Data in EEPROM
        _nextHour = _nextHour + HourMillis;
        if(active){
        tmpReturn = 2;
       _stopTime = MyMillis();   // simulation new value
        active = false;
        _newPulse = true;

        }
     }
     if (!active&&_newPulse)    //calc
     {
        if(tmpReturn==0)tmpReturn=1;
        diffTime = _stopTime - _startTime;         // diff time impuls length
        _addTimeSekunde = diffTime/1000; 
        sumSec = sumSec + _addTimeSekunde;          // New Sec Summary
        
        tempMlSummary = _addTimeSekunde;
        tempMlSummary = tempMlSummary * ulSec;
        tempMlSummary = tempMlSummary /1000;
        sumMl = tempMlSummary + sumMl;      //NEW Ml Summary
        _newPulse = false;

     }
     if (tmpReturn == 2){
        _startTime = _stopTime;   // simulation new value
        active = true;
     }
        timeMillis = MyMillis();   // simulation new value

     if (OverflowLimit<MyMillis())
     {
        resetFunc();  //call reset
     }
     return tmpReturn;
   }






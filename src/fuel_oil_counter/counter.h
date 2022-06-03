/*
  counter.h 
  calculation of heatoil and time counting
*/
#ifndef counter_h
#define counter_h

#include "Arduino.h"

class Counter
{
  public:
    Counter(int inPin,int LED);
    int Update(void);
    IsrRoutine(bool pinState);
    unsigned int ulSec;        //µl per Second
    unsigned long sumMl;      //Summary mili Liter
    unsigned long sumSec;     //Summary Seconds
    bool active; //detection if powerup active
    unsigned int currActSec;
    unsigned long timeMillis;    //current time in milliseconds




    bool _oldActive; //detection if powerup active
    bool _newPulse;

  private:
    // later private
    unsigned long _tmpTime;     //last stopTime
    unsigned long _startTime;    //last startTime
    unsigned long _stopTime;     //last stopTime
    unsigned long _nextHour;
    unsigned long _addTimeSekunde;
    void _calcActSec(void);
    void _calc(void);
    int _inPin;
    int _led;





};

#endif



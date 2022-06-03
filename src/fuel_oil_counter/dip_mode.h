/*
  dip_mode.h 
  calculation DIP switch
*/
#ifndef dip_mode.h
#define dip_mode.h

#include "Arduino.h"

class dip
{
  public:
    dip(int sum,int pin[]);
    restart();
    int value;
    int x,y,z;
  private:
    int _sum;
    int _pin[];
};

#endif

/*
const uint8_t dipCount = 8;
const uint8_t dip[dipCount] = {2, 3, 4, 5, 6, 7, 8};
uint8_t getMode(void)
{
  uint8_t retValue = 0;
  
  for(uint8_t ct = 0; ct < dipCount; ct++)
  {
    retValue |= digitalRead(dip[ct]);
  }
}
*/

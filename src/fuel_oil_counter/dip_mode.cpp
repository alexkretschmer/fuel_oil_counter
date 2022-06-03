/*
  dip_mode.cpp 
  calculation DIP switch value
  
*/

#include "Arduino.h"
#include "dip_mode.h"


dip::dip(int sum,int pin[])
{

  value = 0;
  //_pin = pin;
  _sum = sum;
  for(int ct = 0; ct < sum; ct++)
  {
   // _pin[ct] = pin[ct];
    pinMode(pin[ct],INPUT);
    value |= digitalRead(pin[ct])<<ct;
  }
}



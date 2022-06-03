/* heatoilcounter
 * 17.02.2021 Alexander Kretschmer
 * BOARD Arduino nano
 * Prozessor ATmega168
 */

#include "dip_mode.h"
#include <EEPROM.h>
#include "counter.h"
#include<ModbusRtu.h>       //Library for using Modbus in Arduino

#define fw_version 10
#define inPowerDetect 3     // pin 2 problem ??
#define ledPower 13

#define Rg_ml_summary_hi 1
#define Rg_ml_summary_low 2
#define Rg_s_summary_hi 3
#define Rg_s_summary_low 4
#define Rg_time_hi 5
#define Rg_time_low 6
#define Rg_l_summary 7
#define Rg_h_active_summary 8
#define Rg_DIP 9
#define Rg_g_per_hour 10
#define Rg_ml_per_hour 11
#define Rg_fw_version 12
#define Rg_Device_address 13
#define Rg_Baud_rate 14
#define Rg_Reset_summary 15


#define sumDIP 5
#define DIP1 5
#define DIP2 6
#define DIP3 7
#define DIP4 8
#define DIP5 9

const int inputs[sumDIP] = {DIP1,DIP2,DIP3,DIP4,DIP5};
dip DIP(sumDIP,inputs);

unsigned int g_per_hour;
unsigned int ml_per_hour;
unsigned int ul_per_second;

unsigned int currentActiveSeconds;

unsigned long summaryMl;
unsigned long summarySeconds;
unsigned int Device_address;
unsigned int baudrate;



Modbus bus;                          //Define Object bus for class modbus 
// Modbus register data array (start register = 0)
uint16_t au16data[22] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0}; // 20 registers


Counter counter(inPowerDetect,ledPower );

void saveConfig() {
  int address = 0; // EEPROM starting address
  // Save configuration from RAM into EEPROM
  EEPROM.begin();
    EEPROM.put(address, counter.sumMl);
    address = address + 4;
    delay(200);
   EEPROM.put(address, counter.sumSec);
    address = address + 4;
        delay(200);
   EEPROM.put(address, Device_address);
    address = address + 2;
   EEPROM.put(address, baudrate);
    address = address + 2;
    
    delay(200);

  EEPROM.end();                         // Free RAM copy of structure
}

void loadConfig() {
  int address = 0; // EEPROM starting address
  // Loads configuration from EEPROM into RAM
  EEPROM.begin();
    EEPROM.get(address, counter.sumMl);
    address = address +4;
    EEPROM.get(address, counter.sumSec);
    address = address +4;
    EEPROM.get(address, Device_address);
    address = address +2;
    if (Device_address==0)
    {
      Device_address=1;
    }
    EEPROM.get(address, baudrate);
    address = address +2;
    if (baudrate>3)
    {
      baudrate = 0;
    }
    

  EEPROM.end();
}



void setup() 
{
  pinMode(4,OUTPUT); //TEST
  digitalWrite(4,LOW); //TEST
  loadConfig();
  bus = Modbus(Device_address,1,4);            //Modbus slave ID as 1 and 1 connected via RS-485 and 4 connected to DE & RE pin of RS-485 Module 
  if (baudrate==2)bus.begin(19200);                //Modbus slave baudrate at 9600
  else if (baudrate==1)bus.begin(14400); 
  else bus.begin(9600); 

  g_per_hour = DIP.value*50 + 1450;     //calculation gramm per hour
  ml_per_hour = (g_per_hour*10/86)*10;  //calculation mililiter per hour
  ul_per_second = ml_per_hour*10/36;    //Calculation uliter per second

 // init values
  counter.ulSec = ul_per_second;   

  au16data[Rg_DIP] = DIP.value;
  au16data[Rg_g_per_hour] = g_per_hour;
  au16data[Rg_ml_per_hour] = ml_per_hour;
  au16data[Rg_fw_version] = fw_version;
  au16data[Rg_h_active_summary] = counter.sumSec/3600;
  au16data[Rg_l_summary] = counter.sumMl/1000;
  au16data[Rg_ml_summary_low]= counter.sumMl;
  au16data[Rg_ml_summary_hi]= counter.sumMl>>16;
  au16data[Rg_Device_address] = Device_address;
  au16data[Rg_s_summary_low]=counter.sumSec;
  au16data[Rg_s_summary_hi]=counter.sumSec>>16;
  
}

void loop() {

  //  Mbus - Commands
  bus.poll(au16data,sizeof(au16data)/sizeof(au16data[0]));       //Used to receive or write value from Master 
  if (au16data[Rg_Reset_summary] == 0xAFFE)            // Reset summary values
  {
    // Reset Values
    counter.sumSec = 0;
    counter.sumMl = 0;
    saveConfig();
    au16data[Rg_h_active_summary] = 0;
    au16data[Rg_l_summary] = 0;
    au16data[Rg_ml_summary_low]= 0;
    au16data[Rg_ml_summary_hi]= 0;
    au16data[Rg_Reset_summary]=0x321;
  }
  if (au16data[Rg_Device_address]!=Device_address)     // new configuration Device Address
  {
    Device_address = au16data[Rg_Device_address];
    saveConfig();
  }
  if (au16data[Rg_Baud_rate]!=baudrate)                  // new configuration baudrate
  {
    baudrate = au16data[Rg_Baud_rate];
    saveConfig();
  }

  // Counter
  int calc = counter.Update(); 
  if (calc!=0)
  {
    au16data[Rg_l_summary] = counter.sumMl/1000;
    au16data[Rg_h_active_summary] = counter.sumSec/3600;
    au16data[Rg_ml_summary_low]= counter.sumMl;
    au16data[Rg_ml_summary_hi]= counter.sumMl>>16;
    au16data[Rg_s_summary_low]=counter.sumSec;
    au16data[Rg_s_summary_hi]=counter.sumSec>>16;
  }
    au16data[Rg_time_low]=counter.timeMillis;
    au16data[Rg_time_hi]=counter.timeMillis>>16;
  if (calc>2){
    saveConfig();
  }
  delay(200); 
}




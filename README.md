# Fuel oil counter
Fuel oil counter with Modbus (operating hours counters to calculate the fuel oil consumption).
Calculation of the consumption based on the set nozzle liter consumption.


## Parameter
operating voltage: 5V
output signal: RS-485
communication protocol: Modbus RTU
communication address: 1 ~ 247 (Standard 1)

## Modbus Protocol
### Function codes
        
|command register| function                  |
|----------------|---------------------------|
| 0x03           | read keep register        |
| 0x04           | read input register       |
| 0x06           | write a single register   |
| 0x10           | write more keep registers |

### Registers

|regsiter type   | register address | gegister contents   | bytes | register - ID  |
|----------------|------------------|---------------------|-------|----------------|
| input register | 0x0001           | ml summary Hi Byte  |   2   |  1             | 
| input register | 0x0002           | ml summary Low Byte |   2   |  2             | 
| input register | 0x0003           | s summary Hi Byte   |   2   |  3             | 
| input register | 0x0004           | s summary Low Byte  |   2   |  4             | 
| input register | 0x0005           | ms time   Hi Byte   |   2   |  5             | 
| input register | 0x0006           | ms time   Low Byte  |   2   |  6             |
| input register | 0x0007           | l summary           |   2   |  7 (EEPROM)    |
| input register | 0x0008           | h active summary    |   2   |  8 (EEPROM)    |
| debug register | 0x0009           | DIP value           |   2   |  9             |
| debug register | 0x0010           | gram per hour       |   2   |  10            |
| debug register | 0x0011           | ml per hour         |   2   |  11            |
| debug register | 0x0012           | fw version          |   2   |  12            |
| keep register  | 0x0013           | device address      |   2   |  13 optional   |
| keep register  | 0x0014           | baud rate           |   2   |  14 optional   |
| keep register  | 0x0015           | reset summary       |   2   |  15time & Date |

baudrate = 0 =>  9600 baud
           1 => 14400 baud
           2 => 19200 baud

## OpenHab example

![open_hab_example](gfx/open_hab_example.png)
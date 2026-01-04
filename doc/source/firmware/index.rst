Firmware
========

Please add EEPROM and ModbusRtu Libary in the Arduino IDE.

parameter
-------------
operating voltage: 5V output signal: RS-485 communication protocol: Modbus RTU communication address: 1 ~ 247 (Standard 1)


programming table SW1
------------------------

The factor for the calculation of the heating oil is set with the dip switch SW1.

.. csv-table:: DIP Switch SW1
   :file: /table/SW1.csv
   :header-rows: 1
   :widths: auto

Modbus Protocol
------------------
Function codes
~~~~~~~~~~~~~~~~~~
.. csv-table:: Function Codes
   :file: /table/function_codes.csv
   :header-rows: 1
   :widths: auto 


Registers
~~~~~~~~~~~~~~~~~~

.. csv-table:: register
   :file: /table/register.csv
   :header-rows: 1
   :widths: auto 

Baudrates / parameter
~~~~~~~~~~~~~~~~~~~~~~~~~

* 0 =>  9600 baud
* 1 => 14400 baud
* 2 => 19200 baud




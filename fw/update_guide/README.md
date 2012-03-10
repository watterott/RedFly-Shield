# How to update the RedFly Firmware?


## Update under Windows with Hyper Terminal

* Load the **FWupdate** Sketch into the Arduino Board.


* Connect a 3V3 FTDI Basic-Breakout to the FTDI-3V3 connector on the RedFly. 
  Or you can also use an Arduino with FTDI chipset for the update 
  (baud rate error on the boards with ATmega8u2/16u2 is too high).
  In this case connect pin 0 to FTDI-3V3 pin 4 (TxO) and pin 1 to FTDI-3V3 pin 5 (RxI):<br>
  ![RedFly-Shield](https://github.com/watterott/RedFly-Shield/raw/master/fw/update_guide/fw_redfly.png)

* Run Windows Hyper Terminal: **115200 baud, 8N1, no handshake**<br>
  ![HTerm](https://github.com/watterott/RedFly-Shield/raw/master/fw/update_guide/fw_hterm1.png)
  ![HTerm](https://github.com/watterott/RedFly-Shield/raw/master/fw/update_guide/fw_hterm2.png)
  ![HTerm](https://github.com/watterott/RedFly-Shield/raw/master/fw/update_guide/fw_hterm3.png)

* Power cycle the Arduino+RedFly and make sure that on the RedFly no LED is on. If a LED is on then power cycle again.

* Start connection on the serial port and wait about 20 seconds. Then the module starts with the default settings.

* On the firmware upgrade question press y.<br>

    WELCOME TO REDPINE SIGNALS
    Firmware upgrade (y/n) y


* Send the respected file when the prompt Send xxx appears and use the Kermit protocol.<br>

    WELCOME TO REDPINE SIGNALS
    Firmware upgrade (y/n) y
    Send taim1,taim2,tadm1,tadm2 files in order to upgrade the firmware
    Send taim1

  ![HTerm](https://github.com/watterott/RedFly-Shield/raw/master/fw/update_guide/fw_hterm4.png)
  ![HTerm](https://github.com/watterott/RedFly-Shield/raw/master/fw/update_guide/fw_hterm5.png)
  ![HTerm](https://github.com/watterott/RedFly-Shield/raw/master/fw/update_guide/fw_hterm6.png)

    WELCOME TO REDPINE SIGNALS
    Firmware upgrade (y/n) y
    Send taim1,taim2,tadm1,tadm2 files in order to upgrade the firmware
    Send taim1
    Send taim2
    Send tadm1
    Send tadm2


* Power cycle the Arduino+RedFly after the update is completed.<br>

    WELCOME TO REDPINE SIGNALS
    Firmware upgrade (y/n) y
    Send taim1,taim2,tadm1,tadm2 files in order to upgrade the firmware
    Send taim1
    Send taim2
    Send tadm1
    Send tadm2
    Firmware Upgradation completed


## Update under Linux with cutecom and kermit

Alternatively it's also possible to do the firmware update with cutecom and kermit. 
In this case run kermit with following settings.

    set xm li on
    set line /dev/ttyUSB0
    set speed 115200
    set modem type none
    set flow-control none
    set handshake none
    connect

_(Thanks to Jesse Madsen.)_

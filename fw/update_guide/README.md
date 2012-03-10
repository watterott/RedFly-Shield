# How to update the RedFly Firmware?

##Update under Windows with Hyper Terminal

1. Load the **FWupdate** Sketch into the Arduino Board.

2. Connect a 3V3 FTDI Basic-Breakout to the FTDI-3V3 connector on the RedFly. 
   Or you can also use an Arduino with FTDI chipset for the update (baud rate error on the boards with ATmega8u2/16u2 is too high).
   In this case connect pin 0 to FTDI-3V3 pin 4 (TxO) and pin 1 to FTDI-3V3 pin 5 (RxI):<br>
   ![RedFly-Shield](https://github.com/watterott/RedFly-Shield/raw/master/fw/update_guide/img/fw_redfly.png)

3. Run Windows Hyper Terminal: **115200 baud, 8N1, no handshake**<br>
   ![HTerm](https://github.com/watterott/RedFly-Shield/raw/master/fw/update_guide/img/img/fw_hterm1.png)
   ![HTerm](https://github.com/watterott/RedFly-Shield/raw/master/fw/update_guide/img/img/fw_hterm2.png)
   ![HTerm](https://github.com/watterott/RedFly-Shield/raw/master/fw/update_guide/img/img/fw_hterm3.png)

4. Power cycle the Arduino+RedFly and make sure that on the RedFly no LED is on. If a LED is on then power cycle again.

5. Start connection on the serial port and wait about 20 seconds. Then the module starts with the default settings.

6. On the firmware upgrade question press y.<br>
   `WELCOME TO REDPINE SIGNALS`<br>
   `Firmware upgrade (y/n) y`<br>

7. Send the respected file when the prompt Send xxx appears and use the Kermit protocol.<br>
   `WELCOME TO REDPINE SIGNALS`<br>
   `Firmware upgrade (y/n) y`<br>
   `Send taim1,taim2,tadm1,tadm2 files in order to upgrade the firmware`<br>
   `Send taim1`<br>
   ![HTerm](https://github.com/watterott/RedFly-Shield/raw/master/fw/update_guide/img/img/fw_hterm4.png)
   ![HTerm](https://github.com/watterott/RedFly-Shield/raw/master/fw/update_guide/img/img/fw_hterm5.png)
   ![HTerm](https://github.com/watterott/RedFly-Shield/raw/master/fw/update_guide/img/img/fw_hterm6.png)
   `WELCOME TO REDPINE SIGNALS`<br>
   `Firmware upgrade (y/n) y`<br>
   `Send taim1,taim2,tadm1,tadm2 files in order to upgrade the firmware`<br>
   `Send taim1`<br>
   `Send taim2`<br>
   `Send tadm1`<br>
   `Send tadm2`<br>

8. Power cycle the Arduino+RedFly after the update is completed.<br>
   `WELCOME TO REDPINE SIGNALS`<br>
   `Firmware upgrade (y/n) y`<br>
   `Send taim1,taim2,tadm1,tadm2 files in order to upgrade the firmware`<br>
   `Send taim1`<br>
   `Send taim2`<br>
   `Send tadm1`<br>
   `Send tadm2`<br>
   `Firmware Upgradation completed`<br>


##Update under Linux with cutecom and kermit

Alternatively it's also possible to do the firmware update with cutecom and kermit. 
In this case run kermit with following settings.

   `set xm li on`<br>
   `set line /dev/ttyUSB0`<br>
   `set speed 115200`<br>
   `set modem type none`<br>
   `set flow-control none`<br>
   `set handshake none`<br>
   `connect`<br>

_(Thanks to Jesse Madsen.)_

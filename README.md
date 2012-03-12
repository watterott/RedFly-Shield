# RedFly-Shield
The RedFly-Shield is a plug-on module with WiFi/WLAN for Arduino.

<http://www.watterott.com/en/Arduino-RedFly-Shield>

![RedFly-Shield](https://github.com/watterott/RedFly-Shield/raw/master/img/redfly-shield.jpg)


## Features
 * IEEE 802.11b/g/n/i 2.4GHz
 * Wireless security: AES, WEP, WPA, WPA2 - PSK
 * Ad-hoc (IBSS) and Infrastructure mode (on Ad-hoc only WEP encryption)
 * Scanning for networks with signal strengh indicator
 * Integrated WiFi and IPv4 stack (TCP, UDP, DHCP, DNS)
 * Supports up to 8 sockets at the same time
 * 3V3 - 5V tolerant IOs


## Hardware
Compatible with Arduino Uno, Duemilanove, Diecimila and Mega.

![RedFly-Shield hardware dia](https://github.com/watterott/RedFly-Shield/raw/master/img/hw_dia.png)

_Note: The PCB v1.3 has the new Arduino UNO R3 layout. But the connectors are the normal ones, which don't use SDA, SCL, IOREF and NC. So that the shield can be mounted also on an Arduino Duemilanove or Mega._

## Software
[Arduino Library + Examples](https://github.com/watterott/RedFly-Shield/downloads)


## Directories
 /fw  - Firmware for the WiFi module
 
 /pcb - Schematics and Layout files
 
 /src - Arduino Library and Examples

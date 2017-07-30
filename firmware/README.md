Firmware Update Guide: https://github.com/watterott/RedFly-Shield/tree/master/firmware/update_guide


## Release notes

* 4.7.1
  * Wireless firmware upgrade and configuration feature.
  * Added support for 4 WEP keys.
  * Fixed TCP max payload length 1460 and UDP max payload length 1472.
  * Uses the new RF and BB programming values to improve sensitivity.
  * Improve the accuracy of RSSI value by doing averaging.
  * Support for 32 byte SSID.
  * Number of sockets supported limited to 7.

* 4.5.0
  * Fixed some IBSS issues.
  * Fix for not sending ack for reset from remote peer.
  * WPA/WPA2 password with up to 63 characters.

* 4.4.6
  * Fixed IBSS issues in high traffic scenarios.
  * Added TCP keep alive functionality.
  * Added retry mechanism for TCP SYN-ACK packet.

* 4.4.5
  * Fixed issue with TCP server in handling more than one socket with the same port nnumber.
  * Bugfix in WEP security mode.

* 4.3.0
  * Supporting DNS client.
  * Supporting Multicast socket.
  * Supporting Auto IP.
  * Supporting WEP security mode in IBSS network.

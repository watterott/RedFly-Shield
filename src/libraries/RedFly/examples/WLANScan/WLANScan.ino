/*
  Wlan Scanner
 
  This sketch scans for WLANs using a RedFly-Shield. 
 */

#include <RedFly.h>


//serial format: 9600 Baud, 8N2
void debugout(char *s)  { RedFly.disable(); Serial.print(s);   RedFly.enable(); }
void debugoutln(char *s){ RedFly.disable(); Serial.println(s); RedFly.enable(); }


void setup()
{
  uint8_t ret;

  //init the WiFi module on the shield
  // ret = RedFly.init(br, pwr) //br=9600|19200|38400|57600|115200|200000|230400, pwr=LOW_POWER|MED_POWER|HIGH_POWER
  // ret = RedFly.init(pwr) //9600 baud, pwr=LOW_POWER|MED_POWER|HIGH_POWER
  // ret = RedFly.init() //9600 baud, HIGH_POWER
  ret = RedFly.init();
  if(ret)
  {
    debugoutln("INIT ERR");
    for(;;); //do nothing forevermore
  }
  else
  {
    //get firmware version
    char ver[5+1];
    if(RedFly.getversion(ver) == 0)
    {
      debugout("FW: ");
      debugoutln(ver);
    }

    //get WiFi module MAC
    uint8_t mac[6];
    if(RedFly.getmac(mac) == 0)
    {
      char tmp[32];
      sprintf_P(tmp, PSTR("MAC: %x:%x:%x:%x:%x:%x"), mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
      debugoutln(tmp);
    }
  }
  debugoutln("-----------------");
  debugoutln("Start scanning...");
  debugoutln("-----------------");
}


void loop()
{
  uint8_t ret, mode, rssi, type, mac[6];
  char buf[64];

  //scan for wireless networks
  buf[0] = 0;
  ret = RedFly.scan(buf, &mode, &rssi);
  while((ret == 0) && (rssi != 0))
  {
    //show mode (0=Open, 1=WPA, 2=WPA2, 3=WEP) and RSSI
    debugout(buf);
    sprintf_P(buf, PSTR(", mode %i, rssi %i"), mode, rssi);
    debugoutln(buf);

    //get and show type (0=Ad-hoc, 1=Infrastructure)
    ret = RedFly.gettype(buf, &type);
    if(ret == 0)
    {
      debugout(buf);
      sprintf_P(buf, PSTR(", type %i"), type);
      debugoutln(buf);
    }

    //get and show BSSID
    ret = RedFly.getbssid(buf, mac);
    if(ret == 0)
    {
      debugout(buf);
      sprintf_P(buf, PSTR(", bssid %x:%x:%x:%x:%x:%x"), mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
      debugoutln(buf);
    }

    //next scan
    buf[0] = 0;
    ret = RedFly.nextscan(buf, &mode, &rssi);
  }

  //wait 3s
  delay(3000); 
}

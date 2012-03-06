/*
  Twitter Writer
 
  This sketch posts a message on Twitter http://twitter.com/RedFlyShield

  Based on the Twitter Lib from NeoCat
  http://www.arduino.cc/playground/Code/TwitterLibrary
  http://arduino-tweet.appspot.com

  Requires RedFly + mSD-shield with MI0283QT-Adapter and the 
  PS2Keyboard Library http://www.pjrc.com/teensy/td_libs_PS2Keyboard.html
 */

#include <MI0283QT2.h>
#include <ADS7846.h>
#include <PS2Keyboard.h>
#include <RedFly.h>


#define TP_EEPROMADDR (0x00) //eeprom address for calibration data
MI0283QT2 lcd;
ADS7846 tp;
PS2Keyboard keyboard;

byte ip[]        = { 192,168,  0, 30 }; //ip from shield (client)
byte netmask[]   = { 255,255,255,  0 }; //netmask
byte gateway[]   = { 192,168,  0,103 }; //ip from gateway/router
byte dnsserver[] = { 192,168,  0,103 }; //ip from dns server
byte server[]    = {   0,  0,  0,  0 }; //{ 209, 85,149,141 }; //ip from arduino-tweet.appspot.com (server)
#define HOSTNAME "arduino-tweet.appspot.com" //host
#define TOKEN    "273978908-s6eBqQrr97iXcrXVw4abHcpZ0bof2v5mKdQANXEI" //token from twitter.com/RedFlyShield

char message[256]; //min. 141
uint8_t m_pos=0;


//display output functions
#define infoClear()  lcd.fillRect(0, (lcd.getHeight()/2)-15, lcd.getWidth()-1,(lcd.getHeight()/2)+5, COLOR_WHITE);
#define infoText(x)  lcd.fillRect(0, (lcd.getHeight()/2)-15, lcd.getWidth()-1,(lcd.getHeight()/2)+5, COLOR_BLACK); lcd.drawTextPGM((lcd.getWidth()/2)-60, (lcd.getHeight()/2)-10, PSTR(x), 1, COLOR_WHITE, COLOR_BLACK)
#define errorText(x) lcd.fillRect(0, (lcd.getHeight()/2)-15, lcd.getWidth()-1,(lcd.getHeight()/2)+5, COLOR_BLACK); lcd.drawTextPGM((lcd.getWidth()/2)-60, (lcd.getHeight()/2)-10, PSTR(x), 1, COLOR_RED, COLOR_BLACK)


uint8_t clearall(void)
{
  lcd.clear(COLOR_WHITE);
  lcd.fillRect(0, 0, lcd.getWidth()-1, 20, COLOR_BLACK);
  lcd.drawTextPGM(20, 3, PSTR("Write a message and press Enter..."), 1, COLOR_WHITE, COLOR_BLACK);
}


uint8_t startwifi(void)
{
  uint8_t ret, i;

  //init the WiFi module
  infoText("Init WiFi...");
  ret = RedFly.init(115200, HIGH_POWER); //baud rate, LOW_POWER MED_POWER HIGH_POWER
  if(ret)
  {
    errorText("Init WiFi...Error"); //there are problems with the communication between the Arduino and the RedFly
    return 1;
  }

  //join network
  for(i=3; i!=0; i--) //try 3 times
  {
    //scan for wireless networks (must be run before join command)
    infoText("Scan...");
    RedFly.scan();

    //join network
    // ret = join("wlan-ssid", "wlan-passw", INFRASTRUCTURE or IBSS_JOINER or IBSS_CREATOR, chn, authmode) //join infrastructure or ad-hoc network, or create ad-hoc network
    // ret = join("wlan-ssid", "wlan-passw", IBSS_CREATOR, chn) //create ad-hoc network with password, channel 1-14
    // ret = join("wlan-ssid", IBSS_CREATOR, chn) //create ad-hoc network, channel 1-14
    // ret = join("wlan-ssid", "wlan-passw", INFRASTRUCTURE or IBSS_JOINER) //join infrastructure or ad-hoc network with password
    // ret = join("wlan-ssid", INFRASTRUCTURE or IBSS_JOINER) //join infrastructure or ad-hoc network
    // ret = join("wlan-ssid", "wlan-passw") //join infrastructure network with password
    // ret = join("wlan-ssid") //join infrastructure network
    infoText("Join network...");
    ret = RedFly.join("wlan-ssid", "wlan-passw", INFRASTRUCTURE);
    if(ret)
    {
      errorText("Join network...Error");
    }
    else
    {
      break;
    }
  }
  if(ret)
  {
    return 2;
  }

  //set ip config
  // ret = RedFly.begin(); //DHCP
  // ret = RedFly.begin(1 or 2); //1=DHCP or 2=Auto-IP
  // ret = RedFly.begin(ip);
  // ret = RedFly.begin(ip, dnsserver);
  // ret = RedFly.begin(ip, dnsserver, gateway);
  // ret = RedFly.begin(ip, dnsserver, gateway, netmask);
  infoText("Set IP config...");
  ret = RedFly.begin(ip, dnsserver, gateway, netmask);
  if(ret)
  {
    errorText("Set IP config...Error");
    RedFly.disconnect();
    return 3;
  }

  infoClear();

  return 0;
}


void setup()
{
  uint8_t ret;

  //init display
  lcd.init(2); //spi-clk = Fcpu/2
  lcd.setOrientation(0);

  //init touch controller
  tp.init();
  tp.setOrientation(0);
  
  //init keyboard
  keyboard.begin(18, 19); //Data, Clock (Uno: 2 3 | Mega: 2 3 18 19 20 21)

  //clear screen
  lcd.clear(COLOR_WHITE);
  
  //touch-panel calibration
  tp.service();
  if(tp.getPressure() > 5)
  {
    tp.doCalibration(&lcd, TP_EEPROMADDR, 0); //dont check EEPROM for calibration data
  }
  else
  {
    tp.doCalibration(&lcd, TP_EEPROMADDR, 1); //check EEPROM for calibration data
  }

  //clear screen
  lcd.clear(COLOR_WHITE);

  //start WiFi
  while(startwifi() != 0){ delay(1000); }

  //draw screen background
  clearall();

  //set print options
  lcd.printOptions(2, COLOR_BLACK, COLOR_WHITE);
  lcd.printXY(2, 25);
}


uint8_t send_msg(void)
{
  uint8_t http, sock, buf[32];
  uint16_t rd, len, msg_len;

  infoText("Get server IP...");
  if(RedFly.getip(HOSTNAME, server) == 0) //get ip
  {
    infoText("Connecting...");
    http = RedFly.socketConnect(PROTO_TCP, server, 80); //start connection to server on port 80
    if(http != 0xFF)
    {
      infoText("Send message...");
      //build message and send to Twitter app
      RedFly.socketSendPGM(http, PSTR("POST http://"HOSTNAME"/update HTTP/1.0\r\nHost: "HOSTNAME"\r\nContent-Length: ")); //send HTTP header
      sprintf((char*)buf, "%i\r\n\r\n", strlen("token="TOKEN"&status=")+strlen(message)); //calc content length
      RedFly.socketSend(http, (char*)buf); //send content length and HTTP header end
      RedFly.socketSendPGM(http, PSTR("token="TOKEN"&status=")); //send token

      RedFly.socketSend(http, message); //send message
      delay(100);

      //get response
      for(msg_len=0, message[0]=0;;)
      {
        sock = 0xFF; //0xFF = return data from all open sockets
        rd = RedFly.socketRead(&sock, &len, buf, sizeof(buf));
        if(sock == http)
        {
          if((rd != 0) && (rd != 0xFFFF))
          {
            if((msg_len+rd) > sizeof(message))
            {
              rd = sizeof(message)-msg_len;
            }
            memcpy(&message[msg_len], buf, rd);
            msg_len += rd;
          }
          if((rd == 0xFFFF) || (len == 0)) //connection closed or all data received
          {
            break;
          }
        }
        else if(RedFly.socketClosed(http))
        {
          break;
        }
      }
      message[msg_len] = 0;

      //print response
      infoClear();
      lcd.drawMLText(2, 25, lcd.getWidth()-1, lcd.getHeight()-1, message, 1, COLOR_BLACK, COLOR_WHITE);
      delay(5000);

      RedFly.socketClose(http);
      RedFly.socketReset();
    }
    else
    {
      errorText("Connecting...Error");
      return 2;
    }
  }
  else
  {
    errorText("Get server IP...Error");
    return 1;
  }

  infoClear();

  return 0;
}


void loop()
{
  char c;
  uint8_t i;

  if(keyboard.available())
  {
    c = keyboard.read();
    switch(c)
    {
      case PS2_ENTER:
        if(send_msg())
        {
          while(startwifi() != 0){ delay(1000); } //restart wifi connection
          send_msg();
        }
        message[0] = 0;
        m_pos      = 0;
        clearall();
        lcd.printXY(2, 25);
        break;

      case PS2_ESC:
        memset(message, 0, sizeof(message));
        m_pos = 0;
        clearall();
        lcd.printXY(2, 25);
        break;

      case PS2_DELETE:
        if(m_pos > 0)
        {
          message[--m_pos] = 0;
          if(lcd.printGetX() > 5)
          {
            lcd.printXY(lcd.printGetX()-(FONT_WIDTH*2), lcd.printGetY());
          }
          else
          {
            lcd.printXY(((FONT_WIDTH*2)*(((lcd.getWidth()-2)/(FONT_WIDTH*2))-1))+2, lcd.printGetY()-1-(FONT_HEIGHT*2));
          }
          lcd.fillRect(lcd.printGetX(), lcd.printGetY(), lcd.printGetX()+(FONT_WIDTH*2), lcd.printGetY()+(FONT_HEIGHT*2), COLOR_WHITE);
        }
        break;

      default:
        if((c >= '0') && (c <= '9') ||
           (c >= 'A') && (c <= 'Z') ||
           (c >= 'a') && (c <= 'z') ||
           (c == ' ')               ||
           (c == '@')               ||
           (c == '-')               ||
           (c == '+')               ||
           (c == '*')               ||
           (c == ',')               ||
           (c == '.')               ||
           (c == ':')               ||
           (c == ';')               ||
           (c == '!')               ||
           (c == '?'))
        {
          if(m_pos < 140)
          {
            message[m_pos++] = c;
            message[m_pos]   = 0;
            lcd.print(c);
          }
        }
        break;
    }
  }

  if(tp.getPressure() > 5)
  {

  }

}

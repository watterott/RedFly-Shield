#ifndef REDFLYNBNS_h
#define REDFLYNBNS_h


#ifdef __cplusplus
extern "C" {
#endif
  #include <inttypes.h>
  #include <avr/pgmspace.h>
#ifdef __cplusplus
}
#endif
#include "RedFlyServer.h"


class RedFlyNBNS : RedFlyServer
{
  public:
    RedFlyNBNS(void);
    RedFlyNBNS(char *name);
    ~RedFlyNBNS(void);

    void setName(char *name);
    void setNamePGM(PGM_P name);
    uint8_t service(void);

  private:
    char devname[16+1];

    uint8_t decode(char *dst, char *src);
    void encode(char *dst, char *src, uint8_t type);
};


#endif //REDFLYNBNS_h

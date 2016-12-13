#ifndef FUNC_H
#define FUNC_H

//#ifdef __cplusplus
//extern "C" {
//#endif

#ifdef WIN32
#include <memory.h>
#endif

#include <string.h>
#include "basedef.h"
#include "protocol.h"

#define HEX_TO_BCD(x) (((x)/0x0A)*0x10+((x)%0x0A))
#define BCD_TO_HEX(x) (((x)/0x10)*0x0A+((x)%0x10))

#define ASCII_TO_HEX(c) ((c >='0' && c <='9')?(c-'0'):((c>='A'&&c<='F')?(c-'A'+10):((c>='a'&&c<='f')?(c-'a'+10):0)))
#define isdigit(c)	((unsigned) ((c)-'0') < 10)

#define IS_SPACE	0x01
#define NOT_SPACE	0x00

extern void readSysTime(sysTimePtr pTime);
extern uint8 countCheck(uint8*_data, uint16 _len);
extern uint8 trimSpace(uint8* s, uint16 len);
extern uint8 isNumber(uint8* s, uint16 len);
extern uint8 inverseStrToBCD(uint8* s, uint16 sLen, uint8* t);
extern void inverseArray(uint8* s, uint16 sLen);
extern void trimZero(uint8* buf, uint8 bufSize);
extern void supplementToLenWith0(uint8* s, uint16 len);
extern void supplementTo12(uint8* data);
extern void getSvrId(uint8* svrId);
extern void getGatewayId(uint8* gateId);
extern uint32 bcdToInt(uint8* buf, uint16 bufSize, uint8 needInv);
//#ifdef __cplusplus
//}
//#endif

#endif // FUNC_H

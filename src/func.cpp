#include <QDateTime>
#include <QSettings>
#include "func.h"

static const uint8 spaces[] = { ' ', '\t', '\n', '\r', '\0' };

void readSysTime(sysTimePtr pTime)
{
	QDate time = QDate::currentDate();
	QTime current_time = QTime::currentTime();

	pTime->u8year = HEX_TO_BCD(time.year());
	pTime->u8month = HEX_TO_BCD(time.month());
	pTime->u8day = HEX_TO_BCD(time.day());
	pTime->u8hour = HEX_TO_BCD(current_time.hour());
	pTime->u8minute = HEX_TO_BCD(current_time.minute());
	pTime->u8second = HEX_TO_BCD(current_time.second());
}

uint8 countCheck(uint8*data, uint16 len)
{
	uint8 cs = 0;
	uint16 i;
	for (i = 0;i < len;i++, data++)
		cs += *data;

	return ((~cs) + 1);
}

uint8 isSpace(uint8 s)
{
	uint16 i = 0;
	uint16 arrayLen = sizeof(spaces);
	for (i = 0;i < arrayLen;i++)
		if (s == spaces[i])
			return IS_SPACE;
	return NOT_SPACE;
}

uint8 trimSpace(uint8* s, uint16 len)
{
	uint8* p = s;
	uint8  buf[256] = { 0 };
	uint16 i = 0, j = 0;
	for (i = 0, j = 0;i < len; p++, i++) {
		if (!isSpace(*p)) {
			buf[j] = *p;
			j++;
		}
	}
	memset(s, 0x00, len);
	memcpy(s, buf, j + 1);
	return NO_ERR;
}

uint8 isNumber(uint8* s, uint16 len)
{
	uint16 i = 0;
	if (len == 0) {
		return ERR_CRITICAL;
	}
	for (i = 0;i < len; s++, i++) {
		if (!isdigit(*s)) {
			return ERR_CRITICAL;
		}
	}

	return NO_ERR;
}

uint8 inverseStrToBCD(uint8* s, uint16 sLen, uint8* t)
{
	uint16 i = 0;

	if (sLen % 2)
		return ERR_CRITICAL;

	for (i = 0;i < sLen / 2;i++, s += 2) {//convert ascii to hex each two chars
		t[i] = (ASCII_TO_HEX(s[0]) << 4 | ASCII_TO_HEX(s[1]));
	}

	inverseArray(t, i);
	return NO_ERR;
}

void inverseArray(uint8* buf, uint16 bufSize)
{
	uint16 i = 0;
	for (i = 0;i < bufSize / 2; i++) {//swap two symmetric elements
		buf[i] = buf[i] ^ buf[bufSize - i - 1];
		buf[bufSize - i - 1] = buf[i] ^ buf[bufSize - i - 1];
		buf[i] = buf[i] ^ buf[bufSize - i - 1];
	}
}

void trimZero(uint8* buf, uint8 bufSize)
{
	uint16 i = 0;
	uint8* lu8pBuf = buf;
	uint8 tmpBuf[512] = { 0 };
	while (i < bufSize && (*lu8pBuf == '0')) {
		i++;
		lu8pBuf++;
	}
	memcpy(tmpBuf, lu8pBuf, bufSize - i);
	memset(buf, 0, bufSize);
	memcpy(buf, tmpBuf, bufSize - i);
}

void supplementToLenWith0(uint8* s, uint16 len)
{
	uint8 lu8tmpStr[GATEWAY_FRAME_MAX_LEN] = { 0 };

	if (STRLEN(s) >= len) {
		return;
	}

	memset(lu8tmpStr, '0', (len - STRLEN(s)));
	memcpy(lu8tmpStr + (len - STRLEN(s)), s, STRLEN(s));
	memcpy(s, lu8tmpStr, len);
}

void supplementTo12(uint8* data)
{
	size_t lu8InputLen = 0;

	//supplement '0' before data, if lu8InputLen < 2 * GATEWAY_OADD_LEN
	lu8InputLen = STRLEN(data);
	//we use 2 chars to represent a byte, so the mod is 2.
	if (lu8InputLen % 2) {//if lu8InputLen is Odd, lu8InputLen must <= (2 * GATEWAY_OADD_LEN - 1)
		if (lu8InputLen > 2 * GATEWAY_OADD_LEN - 1)
			return;
	}
	else {//if lu8InputLen is Even, lu8InputLen must <= 2 * GATEWAY_OADD_LEN
		if (lu8InputLen > 2 * GATEWAY_OADD_LEN)
			return;
	}
	supplementToLenWith0(data, 2 * GATEWAY_OADD_LEN);
}

void getId(uint8* id, QString idName)
{
	QSettings settings(INI_PATH, QSettings::IniFormat);
	QByteArray b;
	uint8*  pBuf = NULL;
	uint8	buf[2 * GATEWAY_OADD_LEN] = { 0 };

	b = settings.value(idName).toString().toLocal8Bit();
	pBuf = (uint8*)b.data();
	memcpy(buf, pBuf, b.length());
	supplementTo12(buf);
	inverseStrToBCD(buf, 2 * GATEWAY_OADD_LEN, id);
}

void getSvrId(uint8* svrId)
{
	getId(svrId, STRING_SVRID);
}

void getGatewayId(uint8* gateId)
{
	getId(gateId, STRING_SVRID);
}

uint32 bcdToInt(uint8* buf, uint16 bufSize, uint8 needInv)
{
	uint32 value = 0;
	uint16 i = 0;
	uint8 d = 0;

	if (needInv) {
		inverseArray(buf, bufSize);
	}
	for (i = 0;i < bufSize;i++) {
		d = BCD_TO_HEX(buf[i]);
		value = d + value * 100;
	}
	return value;
}
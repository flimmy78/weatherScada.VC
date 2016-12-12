#ifndef BASEDEF_H
#define BASEDEF_H

#  ifdef WIN32
#  define DLL_EXPORT __declspec(dllexport)
#  else
#  define DLL_EXPORT
#  endif

typedef unsigned char   uint8;
typedef unsigned short  uint16;
typedef unsigned int    uint32;
typedef char   int8;
typedef short  int16;
typedef int    int32;


#define NO_ERR			0//无错误
#define ERR_OVERTIME	1//超时
#define ERR_CRITICAL	-1//致命错误

#define RELEASE_PNT(POINTER)    if(NULL != POINTER){delete POINTER;POINTER=NULL;}

#define CONNECT_THREAD(OBJECT, THREAD)	connect((THREAD), SIGNAL(started()), (OBJECT), SLOT(startThread()));\
											connect((OBJECT), SIGNAL(finished()), (THREAD), SLOT(quit()));\
											connect((OBJECT), SIGNAL(finished()), (OBJECT), SLOT(deleteLater()));\
											connect((THREAD), SIGNAL(finished()), (THREAD), SLOT(deleteLater()));\
											(THREAD)->start()

#define STRLEN(c)	strlen((const char*)(c))
#define SLEEP_SEC(SEC)		QThread::sleep((SEC))
#define SLEEP_MSEC(MSEC)	QThread::msleep((MSEC))

#define INI_PATH			"ini/sysconfig.ini"
#define STRING_GATEWAYID	"gatewayId"
#define STRING_SVRID		"svrId"
#define STRING_ROOMTEMP_NO	"roomTempNo"
#define STRING_AIRTEMP_NO	"airTempNo"
#define STRING_HEATMETER_NO	"heatMeterNo"
#define STRING_WINDRATE_NO	"windMeterNo"
#define STRING_ROOMAREA		"roomArea"
#define STRING_COM			"com"
#define STRING_BAUDRATE		"baudrate"
#define STRING_DATABITS		"databits"
#define STRING_PARITY		"parity"
#define STRING_STOPBITS		"stopbits"

typedef enum {
	weather_fine = 0,	//天气晴
	weather_cloudy,		//天气多云
	weather_shade		//天气阴
}weatherEnum;

#pragma	pack(push)
#pragma pack(1)

typedef struct {//统一为BCD码
	uint8 u8second;
	uint8 u8minute;
	uint8 u8hour;
	uint8 u8day;
	uint8 u8month;
	uint8 u8year;
}sysTimeStr;
typedef sysTimeStr* sysTimePtr;

typedef struct {
	uint32	seq;			//序列号
	sysTimeStr	timeNode;	//抄表时间点
	float	tIn;			//供水温度
	float	tOut;			//回水温度
	float	tAvg;			//供回水的平均温度
	float	flowRate;		//流速m3/h
	float	power;			//热功率kW
	float	accumFlow;		//累计流量m3
	float	deltaFlow;		//流量增量m3
	float	energy;			//累计热量kWh
	float	deltaEnergy;	//热量增量kWh
	float	inTemp1;		//室内温度1
	float	inTemp2;		//室内温度2
	float	outTemp1;		//室外温度1
	float	outTemp2;		//室外温度2
	float	windRate;		//风速m/s
	weatherEnum	weather;	//天气情况
	float	roomArea;		//房屋建筑面积
} historyDataStr;
typedef historyDataStr*	historyDataPtr;

#pragma pack(pop)

#endif // BASEDEF_H

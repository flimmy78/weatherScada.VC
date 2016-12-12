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


#define NO_ERR			0//�޴���
#define ERR_OVERTIME	1//��ʱ
#define ERR_CRITICAL	-1//��������

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
	weather_fine = 0,	//������
	weather_cloudy,		//��������
	weather_shade		//������
}weatherEnum;

#pragma	pack(push)
#pragma pack(1)

typedef struct {//ͳһΪBCD��
	uint8 u8second;
	uint8 u8minute;
	uint8 u8hour;
	uint8 u8day;
	uint8 u8month;
	uint8 u8year;
}sysTimeStr;
typedef sysTimeStr* sysTimePtr;

typedef struct {
	uint32	seq;			//���к�
	sysTimeStr	timeNode;	//����ʱ���
	float	tIn;			//��ˮ�¶�
	float	tOut;			//��ˮ�¶�
	float	tAvg;			//����ˮ��ƽ���¶�
	float	flowRate;		//����m3/h
	float	power;			//�ȹ���kW
	float	accumFlow;		//�ۼ�����m3
	float	deltaFlow;		//��������m3
	float	energy;			//�ۼ�����kWh
	float	deltaEnergy;	//��������kWh
	float	inTemp1;		//�����¶�1
	float	inTemp2;		//�����¶�2
	float	outTemp1;		//�����¶�1
	float	outTemp2;		//�����¶�2
	float	windRate;		//����m/s
	weatherEnum	weather;	//�������
	float	roomArea;		//���ݽ������
} historyDataStr;
typedef historyDataStr*	historyDataPtr;

#pragma pack(pop)

#endif // BASEDEF_H

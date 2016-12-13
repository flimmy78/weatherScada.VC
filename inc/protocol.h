#ifndef PROTOCOL_H
#define PROTOCOL_H

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#include "basedef.h"

#define CJ188_HEAT_METER
#define GATEWAY_PROTOCOL_VER 0x03	//Э��汾��

#ifdef GATEWAY_PROTOCOL_VER
#if GATEWAY_PROTOCOL_VER == 0x03
#define GATEWAY_PREFIX      0xFB    //������ͨѶЭ���ǰ����
#define GATEWAY_SUFIX       0xFD    //������ͨѶЭ��Ľ�����
#define GATEWAY_START       0x7B    //������ͨѶЭ�����ʼ��
#define GATEWAY_PREFIX_CNT  2       //������ͨѶЭ���ǰ��������
#define GATEWAY_SUFIX_CNT   2       //������ͨѶЭ��Ľ���������
#define GATEWAY_START_CNT   1       //������ͨѶЭ�����ʼ������
#define GATEWAY_VER_LEN     1       //������ͨѶЭ��İ汾�ų���
#define GATEWAY_SADD_LEN    6       //������ͨѶЭ���Դ��ַ����
#define GATEWAY_OADD_LEN    6       //������ͨѶЭ���Ŀ���ַ����
#define GATEWAY_MID_LEN     1       //������ͨѶЭ�����Ϣ���кų���
#define GATEWAY_MSGL_LEN    2       //������ͨѶЭ�����Ϣ�ֽ�������
#define GATEWAY_MT_LEN      1       //������ͨѶЭ�����Ϣ���ͳ���
#define GATEWAY_TS_LEN      6       //������ͨѶЭ��������ճ���
#define GATEWAY_HCK_LEN     1       //������ͨѶЭ���ͷ��У�鳤��
#define GATEWAY_EC_LEN      1       //������ͨѶЭ�����Ϣ��У�鳤��
#define GATEWAY_HEAD_LEN    (GATEWAY_VER_LEN+GATEWAY_SADD_LEN+GATEWAY_OADD_LEN+GATEWAY_MID_LEN\
                            +GATEWAY_MSGL_LEN+GATEWAY_MT_LEN+GATEWAY_TS_LEN)
#define GATEWAY_RETID_OFFSET	(GATEWAY_PREFIX_CNT+GATEWAY_START_CNT+GATEWAY_VER_LEN)//offset that gatewayId in return frame
#define GATEWAY_MAIN_FRAME_LEN	30	//������Э���� �ų���Ϣ�岿�ֵ�֡����(������Ϣ��У��)
#define GATEWAY_FRAME_MAX_LEN	2048//ÿ֡Э����󳤶�
#define GATEWAY_METERINFO_LEN	40//�Ǳ���Ϣ�ĳ���
#define GATEWAY_MAX_METERINFO_CNT	24//������Э����ÿ������·�����������
#define GATEWAY_BODY_OFFSET	27//��Ϣ��ƫ����
#define GATEWAY_BODYLEN_OFFSET	17//��Ϣ�峤��ƫ����
//#define GATEWAY_MAX_METERINFO_CNT	2//������Э����ÿ������·�����������
#define GATEWAY_ISSUE_BODY_HEAD	3//�·����ַ��Ϣͷ�ĳ���

#define GATEWAY_TIMENODE_CNT_LEN	1//����ʱ�������ĳ���
#define GATEWAY_TIMENODE_LEN		2//ÿ������ʱ���ĳ���
#define GATEWAY_TIMENODE_MAX_CNT	24//����ARM7���֧�ֶ��ٸ�����ʱ���

#define GATEWAY_ASWCODE_OFFSET		19//����������֡��Ӧ�����ƫ����
#define GATEWAY_STATCODE_OFFSET		27//����������֡�гɹ�״̬���ƫ����
#define GATEWAY_SEQCODE_OFFSET		28//����������֡�з��������͵��������ƫ����
#define GATEWAY_WITHSEQ_LEN			32//����������֡�д��з��������͵����кŵ�֡����
#define GATEWAY_WITHOUTSEQ_LEN		31//����������֡�в����з��������͵����кŵ�֡����
//�쳣��Ӧ����--��ʾ����
#define GAT_EXCEP_FAIL          0x10//ʧ��, �쳣
#define GAT_EXCEP_MEASURE_POINT 0x11//�쳣, �鲻��ָ��������š�
#define GAT_EXCEP_CHANNEL_BUSY  0x12//�쳣, ��������æ, ���ڲ��ܳ���.
#define GAT_EXCEP_PARAM_EXCEED  0x13//������������Χ
#define GAT_EXCEP_PROTO_VER     0x14//��Ϣ��汾�Ŵ���

/*������Э����MSG_TYPE��������� START*/
#define GAT_MT_SVR_CP_1_METER   0x06//��վ�·�������ָ��(0x06)
#define GAT_MT_CLT_CP_1_METER   0x07//����������վ���͵�������(0x07)

#define GAT_MT_SVR_1OF_MFRM     0x11//��վ�����������ض�������(0x11)

#define GAT_MT_SVR_MODIFY_SINFO 0x13//��վ���ĵ��������������Ϣ(0x13)
#define GAT_MT_CLT_MODIFY_SINFO 0x14//��������Ӧ��վ���ĵ����ȱ��ַ��Ϣ(0x14)

#define GAT_MT_SVR_SEND_MINFO   0x0C//��վ�·������Ǳ��ַ(0x0C)
#define GAT_MT_CLT_SEND_MINFO	0x0D//��������Ӧ��վ�·��Ǳ��ַ(0x0D)

#define GAT_MT_SVR_TIME_POINT   0x20//��վ���ö�ʱ����ʱ��(0x20)
#define GAT_MT_CLT_TIME_POINT   0x21//���ö�ʱ����ʱ�䷴��(0x21)

#define GAT_MT_SVR_HISDATA      0x22//��վ������������ʷʱ�������б�����(0x22)
#define GAT_MT_CLT_HISDATA      0x23//����������վ���͹̶�ʱ�����������(0x23)

#define GAT_MT_SVR_TIME_SET     0x24//���ü�����ʱ��ʱ��(0x24)
#define GAT_MT_CLT_TIME_SET     0x25//��������Ӧ����ʱ��(0x25)

#define GAT_MT_SVR_TIME_RD      0x26//��ȡ������ʱ��ʱ��(0x26)
#define GAT_MT_CLT_TIME_RD      0x27//��������Ӧ����ʱ��(0x27)

#define GAT_MT_CLT_HB           0x2E//GPRS����(0x2E)
#define GAT_MT_SVR_HB           0x2F//GPRS������Ӧ(0x2F)

#define GAT_MT_SVR_REREAD       0x3A//��վ���Ĳ�������ز���(0x3A)��λms
#define GAT_MT_CLT_REREAD       0x3B//��������Ӧ��վ���Ĳ�������ز���(0x3B)��λms

#define GAT_MT_SVR_REBOOT       0x34//����������ָ��(0x34)
#define GAT_MT_CLT_REBOOT       0x35//������ָ��Ļ�Ӧ(0x35)�������յ�����ָ���, ���Ȼ�Ӧ��λ��, 5�������

#define GAT_MT_SVR_SHISDATA     0x3C//��վ������������ʷʱ���ĳ���������(0x3C)
#define GAT_MT_CLT_SHISDATA     0x3D//����������վ���͹̶�ʱ���ĳ���������(0x3D)

#define GAT_MT_SVR_CPY_IMMDT    0x3E//���ü�������������(0x3E)
#define GAT_MT_CLT_CPY_IMMDT    0x3F//��������Ӧ������������(0x3F)

#define GAT_MT_SVR_RD_CONFIG    0x90//��վ��ȡ����������(0x90)
#define GAT_MT_CLT_RD_CONFIG    0x91//��վ��ȡ������������Ӧ(0x91)

#define GAT_MT_SVR_RD_ALLINFO   0x92//��վ��ȡ��������ȫ���ȱ��ַ��Ϣ (0x92 )
#define GAT_MT_CLT_RD_ALLINFO   0x93//����������վ�����ȱ��ַ��Ϣ(0x93)

#define GAT_MT_SVR_CHIP         0x94//��վ���ļ�����IP���˿ں�(0x94)
#define GAT_MT_CLT_CHIP         0x95//��������Ӧ��վ���ļ�����IP���˿ں���Ӧ(0x95)

#define GAT_MT_SVR_MID			0x98//��վ���ļ�����������վ���
#define GAT_MT_CLT_MID			0x99//��������Ӧ��վ���ļ�����������վ���
/*������Э����MSG_TYPE��������� END*/

#define	GATEWAY_ASW_CODE_SUC				0x01//�����ɹ�
#define GATEWAY_ASW_CODE_FAIL				0x10//����ʧ��
#define GATEWAY_ASW_CODE_NOREC				0x11//�鲻��ָ���������
#define GATEWAY_ASW_CODE_MBUS_BUSY			0x12//MBUS��æ
#define GATEWAY_ASW_CODE_EXCEED				0x13//������������Χ
#define GATEWAY_ASW_CODE_MSGBODY_VER_ERR	0x14//��Ϣ��汾�Ŵ���

#define PROTO_LEN_MADDR		7//Э�����Ǳ��ַ����
#define PROTO_LEN_VADDR		7//Э���з��ŵ�ַ����
#define PROTO_LEN_ROWID		2//Э���м������ų���
#define PROTO_LEN_ROOMID	2//Э���з����ų���
#define PROTO_LEN_RSV		8//�����ֶγ���

/************************************************************************/
/*                       ���ſ���                                       */
/************************************************************************/
#define PROTO_VOPEN_ZERO	0x99//ȫ��
#define PROTO_VOPEN_QUATER	0x88//�ķ�֮һ��
#define PROTO_VOPEN_HALF	0x77//�뿪
#define PROTO_VOPEN_3QUATER	0x66//�ķ�֮����
#define PROTO_VOPEN_ALL		0x55//ȫ��
/************************************************************************/

/************************************************************************/
/*                       һ��24Сʱ��ʱ���                               */
/************************************************************************/
#define TNODE_00	0x00//ʱ���00ʱ
#define TNODE_01	0x01//ʱ���01ʱ
#define TNODE_02	0x02//ʱ���02ʱ
#define TNODE_03	0x03//ʱ���03ʱ
#define TNODE_04	0x04//ʱ���04ʱ
#define TNODE_05	0x05//ʱ���05ʱ
#define TNODE_06	0x06//ʱ���06ʱ
#define TNODE_07	0x07//ʱ���07ʱ
#define TNODE_08	0x08//ʱ���08ʱ
#define TNODE_09	0x09//ʱ���09ʱ
#define TNODE_10	0x10//ʱ���10ʱ
#define TNODE_11	0x11//ʱ���11ʱ
#define TNODE_12	0x12//ʱ���12ʱ
#define TNODE_13	0x13//ʱ���13ʱ
#define TNODE_14	0x14//ʱ���14ʱ
#define TNODE_15	0x15//ʱ���15ʱ
#define TNODE_16	0x16//ʱ���16ʱ
#define TNODE_17	0x17//ʱ���17ʱ
#define TNODE_18	0x18//ʱ���18ʱ
#define TNODE_19	0x19//ʱ���19ʱ
#define TNODE_20	0x20//ʱ���20ʱ
#define TNODE_21	0x21//ʱ���21ʱ
#define TNODE_22	0x22//ʱ���22ʱ
#define TNODE_23	0x23//ʱ���23ʱ
/************************************************************************/

#pragma pack(push)
#pragma pack(1)

typedef struct{//�·��������Ǳ������Ϣ�ṹ
    uint8 rowId[PROTO_LEN_ROWID];		//������, ����Ψһ��ʾһ��(Little Ending, Hex)
    uint8 meterAddr[PROTO_LEN_MADDR];  //�Ǳ�(������,ˮ���)��ַ(Little Ending, BCD)
    uint8 vendorId;					//���̴���(Hex)
    uint8 protoVer;					//�Ǳ�Э��汾��(Hex)
    uint8 meterType;					//�Ǳ�����(Hex)
    uint8 channel;						//ͨ����(Hex)
    uint8 valveProtoVer;				//����Э��汾��(Hex)
    uint8 valveAddr[PROTO_LEN_VADDR];  //���ص�ַ(Little Ending, BCD)
    uint8 controlPanelAddr[PROTO_LEN_VADDR]; //�¿�����ַ(Little Ending, BCD)
    uint8 buildId;						//¥����(Hex)
    uint8 unitId;						//��Ԫ��(Hex)
    uint8 roomId[PROTO_LEN_ROOMID];    //�����(Little Ending, Hex)
    uint8 reserved[PROTO_LEN_RSV];     //�����ֶ�
}meter_row_str;
typedef meter_row_str* meter_row_ptr;

typedef struct {//�������������Ϣ��Ϣͷ
    uint8 totalRows;			//һ���ж����б��ַ
    uint8 seq;					//��֡��������
    uint8 thisRows;			//��֡���������б��ַ
}meterinfo_bodyHead_str;
typedef meterinfo_bodyHead_str* meterinfo_bodyHead_ptr;

typedef struct {//�·�GPRS��ز����ṹ��
    uint8 Method;			//�������ȼ�����20H;����ʽ�ȷ����A0H;ʱ��ͨ�������B0H;
    uint8 DataSource;		//0X0A ��λ����0X0B���س���
    uint8 Period[2];		//��̯���ڣ����ӣ�
    uint8 LogReportTime;	//0x00 :�� ��0x01:����
    uint8 LogOpenType; 	//0X00: �� ��0X01 ������
    uint8 APN;             //GPRS����APN�����ѡ��.
    uint8 IPAddr[4];		//0�ǵ�λIP  3�Ǹ�λIP 16�����·�
    uint8 HostPor[2];		//��վ�˿ںŸ�8λ  (ע���˿ںŸߵ��ֽ�˳���0x90��0x91��ȡʱ˳���෴��)
}gprs_param_str;
typedef gprs_param_str* gprs_param_ptr;

typedef struct {//��ȡGPRS�Լ���Ӳ���汾����Ϣ�Ľṹ��
    uint8 Ip[4];			//������IP, ����
    uint8 Port[2];			//�������˿�
    uint8 Address[6];		//��������ַ
    uint8 HostAddress[6];	//��վ��ַ
    uint8 SoftVer[2];		//����汾��, ���磺0x0232����2.32
    uint8 HardwareVer[2];	//Ӳ���汾��, ���磺0x0232����2.32*/
    uint8 u8APN;			//GPRSģ��APN����㣬0-cmnet������1-��ͨM2M��������2-�����ȵ硣
    uint8 u8Reserved[6];	//����
} gateway_params_str;
typedef gateway_params_str* gateway_params_ptr;

typedef struct {//������ز����ṹ��
	uint8	mReadCnt;	//�ȱ�������
    uint16 mReadIntv;	//�ȱ���ʱ����ms
	uint8	vReadCnt;	//���ز�������
    uint16 vReadIntv;	//���ز���ʱ����ms
}reread_param_str;
typedef reread_param_str* reread_param_ptr;

typedef struct {//��Ϣͷ���ṹ��
    uint8 prefix[GATEWAY_PREFIX_CNT];		//ǰ����0xFB
    uint8 start;							//��ʼ��0x7B
    uint8 protoVer;						//Э��汾��
    uint8 SourceAddr[GATEWAY_SADD_LEN];	//Դ��ַ, ���ͷ���ַ
    uint8 DestAddr[GATEWAY_OADD_LEN];		//Ŀ�ĵ�ַ, ���շ���ַ
    uint8 MsgID;							//��Ϣ����
    uint16 bodyLen;						//��Ϣ�峤��
    uint8 MsgType;							//��Ϣ����
    sysTimeStr sysTime;					//TSʱ���ǩ
    uint8 HeadCheck;						//��ϢͷУ��
} protocol_head_str;
typedef protocol_head_str* protocol_type_ptr;

typedef struct {//������Э����Ϣ��ṹ
    protocol_head_str head_str;	//��Ϣͷ��
    uint8*  pMsgBody;				//��Ϣ��ָ��
	uint8	bodyChk;				//��Ϣ��У��
} gateway_protocol_str;
typedef gateway_protocol_str* gateway_protocol_ptr;

typedef struct {//��ȡ���������ַ��Ϣ, ��Ϣͷ�ṹ��
    uint8 succeed;		//�Ƿ��к��֡, 0-û��, 1-��, 10-�쳣
    uint8 seq;			//�������
    uint8 meterType;	//�Ǳ�����, �̶�Ϊ0x20
    uint8 rowCnt;		//��֡�����ı��ַ����
} base_info_head_str;
typedef base_info_head_str* base_info_head_ptr;

typedef struct {//��ȡ�������ȱ���ʷ��Ϣ�ṹ��
    uint8	DailyHeat[4];			//����������
    uint8	DailyHeatUnit;			//һ��ΪkWh, 0x05
    uint8	CurrentHeat[4];			//��ǰ����
    uint8	CurrentHeatUnit;		//һ��ΪkWh, 0x05
    uint8	HeatPower[4];			//�ȹ���
    uint8	HeatPowerUnit;			//һ��ΪkW, 0x17
    uint8	Flow[4];				//��������
    uint8	FlowUnit;				//һ��Ϊm3/h, 0x35
    uint8	AccumulateFlow[4];		//�ۻ�����
    uint8	AccumulateFlowUnit;		//һ��Ϊm3, 0x2C
    uint8	WaterInTemp[3];			//��ˮ�¶�
    uint8 	WaterOutTemp[3];		//��ˮ�¶�
    uint8 	AccumulateWorkTime[3];	//�ۼƹ���ʱ��
	uint8	RealTime[7];		    //ʵʱʱ��
	uint16	ST;					    //״̬ST
}CJ188_Format;
typedef CJ188_Format* CJ188_Format_ptr;

typedef struct {//��ʷ�����еĹ̶���Ϣ����
    uint16	meterId;				//�������
    uint8	meterType;				//�Ǳ�����
    uint8	meterAddr[7];			//�Ǳ��ַ
    uint8	buildId;				//¥��
    uint8	unitId;					//��Ԫ��
	uint16	roomId;					//�����
    uint8	mSecondBCD;				//���ȱ���BCD
    uint8	mMinuteBCD;				//���ȱ����BCD
    uint8	mHourBCD;				//���ȱ�СʱBCD
    uint8	meterDataLen;			//�ȱ����ݳ���
} hisdata_meter_fix_str;
typedef hisdata_meter_fix_str* hisdata_fix_ptr;

typedef struct {
    uint8	vSecondBCD;				//������BCD
    uint8	vMinuteBCD;				//��������BCD
    uint8	vHourBCD;				//����СʱBCD
    uint8	RoomTempBCD[3];			//�����¶�
    uint8	vOpen;					//���ſ���
    uint8	vState;					//����״̬
    uint8	vReserve;				//����
} hisdata_valve_fix_str;
typedef hisdata_valve_fix_str* hisdata_valve_fix_ptr;

typedef struct {//�¿ؼ���һ�廯, ��ʷ���ݸ�ʽ
    hisdata_meter_fix_str	fixMeter;//�ȱ�Ĺ̶�����
#ifdef CJ188_HEAT_METER
    CJ188_Format	MeterData;		//�ȱ�����
#endif // CJ188_HEAT_METER
    hisdata_valve_fix_str fixValve;	//���صĹ̶�����
} tempControl_messure_hisdata_str;
typedef tempControl_messure_hisdata_str* tempControl_messure_hisdata_ptr;

typedef struct {//�¿ؼ���һ�廯��ͨ��ʱ�����������ʷ����ͷ���ṹ
    uint8 succeed;			//�Ƿ��к��֡, 0-û��, 1-��, 10-�쳣
    uint8 seq;				//�������
	sysTimeStr timeNode;//�洢ʱ����
} hisdata_head_str;
typedef hisdata_head_str*  hisdata_head_ptr;

typedef struct {//͸�������������еĹ̶���Ϣ����
    uint16 meterId;				//�������
    uint8	meterType;				//�Ǳ�����
    uint8	meterAddr[7];			//�Ǳ��ַ
    uint8	buildId;				//¥��
    uint8	unitId;					//��Ԫ��
    uint16	roomId;					//�����
	uint8	meterDataLen;			//�ȱ����ݳ���
} remote_meter_fix_str;
typedef remote_meter_fix_str* remote_meter_fix_ptr;

typedef struct {
    uint8	RoomTempBCD[3];			//�����¶�
    uint8	vOpen;					//���ſ���
    uint8	vState;					//����״̬
    uint8	vReserve;				//����
} remote_valve_fix_str;
typedef remote_valve_fix_str* remote_valve_fix_ptr;

typedef struct {//�¿ؼ���һ�廯, ��ʷ���ݸ�ʽ
    remote_meter_fix_str	fixMeter;//�ȱ�Ĺ̶�����
#ifdef CJ188_HEAT_METER
    CJ188_Format	MeterData;		//�ȱ�����
#endif // CJ188_HEAT_METER
    remote_valve_fix_str fixValve;	//���صĹ̶�����
} tempControl_messure_remote_str;
typedef tempControl_messure_remote_str* tempControl_messure_remote_ptr;

#pragma pack(pop)

extern uint8 protoR_readHisData(uint8* buf, uint16* bufSize, sysTimePtr timeNode);
extern uint8 protoR_readMultiInfo(uint8* buf, uint16* bufSize, uint8* seq);
extern uint8 protoA_hisData(uint8* buf, const uint16 bufSize, uint16* hisDataCnt, \
	hisdata_head_ptr pBodyHead, tempControl_messure_hisdata_ptr pHisData);
#endif//GATEWAY_PROTOCOL_VER==0x03
#endif // GATEWAY_PROTOCOL_VER

#ifdef __cplusplus
}
#endif//__cplusplus

#endif // PROTOCOL_H

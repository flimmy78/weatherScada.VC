#ifndef PROTOCOL_H
#define PROTOCOL_H

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
#define GATEWAY_ASW_CODE_EXCEED				0x13//����������Χ
#define GATEWAY_ASW_CODE_MSGBODY_VER_ERR	0x14//��Ϣ��汾�Ŵ���

#define PROTO_LEN_MADDR		7//Э�����Ǳ��ַ����
#define PROTO_LEN_VADDR		7//Э���з��ŵ�ַ����
#define PROTO_LEN_ROWID		2//Э���м������ų���
#define PROTO_LEN_ROOMID	2//Э���з����ų���
#define PROTO_LEN_RSV		8//�����ֶ�

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

typedef struct{//ͳһΪBCD��
    uint8 u8second;
    uint8 u8minute;
    uint8 u8hour;
    uint8 u8day;
    uint8 u8month;
    uint8 u8year;
}sys_time_str;
typedef sys_time_str* sys_time_ptr;

typedef struct{//�·��������Ǳ������Ϣ�ṹ
    U8 rowId[PROTO_LEN_ROWID];		//������, ����Ψһ��ʾһ��(Little Ending, Hex)
    U8 meterAddr[PROTO_LEN_MADDR];  //�Ǳ�(������,ˮ���)��ַ(Little Ending, BCD)
    U8 vendorId;					//���̴���(Hex)
    U8 protoVer;					//�Ǳ�Э��汾��(Hex)
    U8 meterType;					//�Ǳ�����(Hex)
    U8 channel;						//ͨ����(Hex)
    U8 valveProtoVer;				//����Э��汾��(Hex)
    U8 valveAddr[PROTO_LEN_VADDR];  //���ص�ַ(Little Ending, BCD)
    U8 controlPanelAddr[PROTO_LEN_VADDR]; //�¿�����ַ(Little Ending, BCD)
    U8 buildId;						//¥����(Hex)
    U8 unitId;						//��Ԫ��(Hex)
    U8 roomId[PROTO_LEN_ROOMID];    //�����(Little Ending, Hex)
    U8 reserved[PROTO_LEN_RSV];     //�����ֶ�
}meter_row_str;
typedef meter_row_str* meter_row_ptr;

typedef struct {//�������������Ϣ��Ϣͷ
    U8 totalRows;			//һ���ж����б��ַ
    U8 seq;					//��֡��������
    U8 thisRows;			//��֡���������б��ַ
}meterinfo_bodyHead_str;
typedef meterinfo_bodyHead_str* meterinfo_bodyHead_ptr;

typedef struct {//�·�GPRS��ز����ṹ��
    U8 Method;			//�������ȼ�����20H;����ʽ�ȷ����A0H;ʱ��ͨ�������B0H;
    U8 DataSource;		//0X0A ��λ����0X0B���س���
    U8 Period[2];		//��̯���ڣ����ӣ�
    U8 LogReportTime;	//0x00 :�� ��0x01:����
    U8 LogOpenType; 	//0X00: �� ��0X01 ������
    U8 APN;             //GPRS����APN�����ѡ��.
    U8 IPAddr[4];		//0�ǵ�λIP  3�Ǹ�λIP 16�����·�
    U8 HostPor[2];		//��վ�˿ںŸ�8λ  (ע���˿ںŸߵ��ֽ�˳���0x90��0x91��ȡʱ˳���෴��)
}gprs_param_str;
typedef gprs_param_str* gprs_param_ptr;

typedef struct {//��ȡGPRS�Լ���Ӳ���汾����Ϣ�Ľṹ��
    U8 Ip[4];			//������IP, ����
    U8 Port[2];			//�������˿�
    U8 Address[6];		//��������ַ
    U8 HostAddress[6];	//��վ��ַ
    U8 SoftVer[2];		//����汾��, ���磺0x0232����2.32
    U8 HardwareVer[2];	//Ӳ���汾��, ���磺0x0232����2.32*/
    U8 u8APN;			//GPRSģ��APN����㣬0-cmnet������1-��ͨM2M��������2-�����ȵ硣
    U8 u8Reserved[6];	//����
} gateway_params_str;
typedef gateway_params_str* gateway_params_ptr;

typedef struct {//������ز����ṹ��
    U8	mReadCnt;	//�ȱ�������
    U16 mReadIntv;	//�ȱ���ʱ����ms
    U8	vReadCnt;	//���ز�������
    U16 vReadIntv;	//���ز���ʱ����ms
}reread_param_str;
typedef reread_param_str* reread_param_ptr;

typedef struct {//��Ϣͷ���ṹ��
    U8 prefix[GATEWAY_PREFIX_CNT];		//ǰ����0xFB
    U8 start;							//��ʼ��0x7B
    U8 protoVer;						//Э��汾��
    U8 SourceAddr[GATEWAY_SADD_LEN];	//Դ��ַ, ���ͷ���ַ
    U8 DestAddr[GATEWAY_OADD_LEN];		//Ŀ�ĵ�ַ, ���շ���ַ
    U8 MsgID;							//��Ϣ����
    U16 bodyLen;						//��Ϣ�峤��
    U8 MsgType;							//��Ϣ����
    sys_time_str sysTime;				//TSʱ���ǩ
    U8 HeadCheck;						//��ϢͷУ��
} protocol_head_str;
typedef protocol_head_str* protocol_type_ptr;

typedef struct {//������Э����Ϣ��ṹ
    protocol_head_str head_str;	//��Ϣͷ��
    U8 *pMsgBody;				//��Ϣ��ָ��
    U8	bodyChk;				//��Ϣ��У��
} gateway_protocol_str;
typedef gateway_protocol_str* gateway_protocol_ptr;

typedef struct {//��ȡ���������ַ��Ϣ, ��Ϣͷ�ṹ��
    U8 succeed;		//�Ƿ��к��֡, 0-û��, 1-��, 10-�쳣
    U8 seq;			//�������
    U8 meterType;	//�Ǳ�����, �̶�Ϊ0x20
    U8 rowCnt;		//��֡�����ı��ַ����
} base_info_head_str;
typedef base_info_head_str* base_info_head_ptr;

typedef struct {//��ȡ�������ȱ���ʷ��Ϣ�ṹ��
    U8	DailyHeat[4];			//����������
    U8	DailyHeatUnit;			//һ��ΪkWh, 0x05
    U8	CurrentHeat[4];			//��ǰ����
    U8	CurrentHeatUnit;		//һ��ΪkWh, 0x05
    U8	HeatPower[4];			//�ȹ���
    U8	HeatPowerUnit;			//һ��ΪkW, 0x17
    U8	Flow[4];				//��������
    U8	FlowUnit;				//һ��Ϊm3/h, 0x35
    U8	AccumulateFlow[4];		//�ۻ�����
    U8	AccumulateFlowUnit;		//һ��Ϊm3, 0x2C
    U8	WaterInTemp[3];			//��ˮ�¶�
    U8 	WaterOutTemp[3];		//��ˮ�¶�
    U8 	AccumulateWorkTime[3];	//�ۼƹ���ʱ��
    U8	RealTime[7];		    //ʵʱʱ��
    U16	ST;					    //״̬ST
}CJ188_Format;
typedef CJ188_Format* CJ188_Format_ptr;

typedef struct {//��ʷ�����еĹ̶���Ϣ����
    U16 meterId;				//�������
    U8	meterType;				//�Ǳ�����
    U8	meterAddr[7];			//�Ǳ��ַ
    U8	buildId;				//¥��
    U8	unitId;					//��Ԫ��
    U16	roomId;					//�����
    U8	mSecondBCD;				//���ȱ���BCD
    U8	mMinuteBCD;				//���ȱ����BCD
    U8	mHourBCD;				//���ȱ�СʱBCD
    U8	meterDataLen;			//�ȱ����ݳ���
} hisdata_meter_fix_str;
typedef hisdata_meter_fix_str* hisdata_fix_ptr;

typedef struct {
    U8	vSecondBCD;				//������BCD
    U8	vMinuteBCD;				//��������BCD
    U8	vHourBCD;				//����СʱBCD
    U8	RoomTempBCD[3];			//�����¶�
    U8	vOpen;					//���ſ���
    U8	vState;					//����״̬
    U8	vReserve;				//����
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
    U8 succeed;		//�Ƿ��к��֡, 0-û��, 1-��, 10-�쳣
    U8 seq;			//�������
    U8 u8second;	//�洢ʱ����
    U8 u8minute;	//�洢ʱ�ķ�
    U8 u8hour;		//�洢ʱ��ʱ
    U8 u8day;		//�洢ʱ����
    U8 u8month;		//�洢ʱ����
    U8 u8year;		//�洢ʱ����
} hisdata_head_str;
typedef hisdata_head_str*  hisdata_head_ptr;

typedef struct {//͸�������������еĹ̶���Ϣ����
    U16 meterId;				//�������
    U8	meterType;				//�Ǳ�����
    U8	meterAddr[7];			//�Ǳ��ַ
    U8	buildId;				//¥��
    U8	unitId;					//��Ԫ��
    U16	roomId;					//�����
    U8	meterDataLen;			//�ȱ����ݳ���
} remote_meter_fix_str;
typedef remote_meter_fix_str* remote_meter_fix_ptr;

typedef struct {
    U8	RoomTempBCD[3];			//�����¶�
    U8	vOpen;					//���ſ���
    U8	vState;					//����״̬
    U8	vReserve;				//����
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

#endif//GATEWAY_PROTOCOL_VER==0x03
#endif // GATEWAY_PROTOCOL_VER

#endif // PROTOCOL_H

#ifndef PROTOCOL_H
#define PROTOCOL_H

#define CJ188_HEAT_METER
#define GATEWAY_PROTOCOL_VER 0x03	//协议版本号

#ifdef GATEWAY_PROTOCOL_VER
#if GATEWAY_PROTOCOL_VER == 0x03
#define GATEWAY_PREFIX      0xFB    //集中器通讯协议的前导符
#define GATEWAY_SUFIX       0xFD    //集中器通讯协议的结束符
#define GATEWAY_START       0x7B    //集中器通讯协议的起始符
#define GATEWAY_PREFIX_CNT  2       //集中器通讯协议的前导符个数
#define GATEWAY_SUFIX_CNT   2       //集中器通讯协议的结束符个数
#define GATEWAY_START_CNT   1       //集中器通讯协议的起始符个数
#define GATEWAY_VER_LEN     1       //集中器通讯协议的版本号长度
#define GATEWAY_SADD_LEN    6       //集中器通讯协议的源地址长度
#define GATEWAY_OADD_LEN    6       //集中器通讯协议的目标地址长度
#define GATEWAY_MID_LEN     1       //集中器通讯协议的消息序列号长度
#define GATEWAY_MSGL_LEN    2       //集中器通讯协议的消息字节数长度
#define GATEWAY_MT_LEN      1       //集中器通讯协议的消息类型长度
#define GATEWAY_TS_LEN      6       //集中器通讯协议的年月日长度
#define GATEWAY_HCK_LEN     1       //集中器通讯协议的头部校验长度
#define GATEWAY_EC_LEN      1       //集中器通讯协议的消息体校验长度
#define GATEWAY_HEAD_LEN    (GATEWAY_VER_LEN+GATEWAY_SADD_LEN+GATEWAY_OADD_LEN+GATEWAY_MID_LEN\
                            +GATEWAY_MSGL_LEN+GATEWAY_MT_LEN+GATEWAY_TS_LEN)
#define GATEWAY_RETID_OFFSET	(GATEWAY_PREFIX_CNT+GATEWAY_START_CNT+GATEWAY_VER_LEN)//offset that gatewayId in return frame
#define GATEWAY_MAIN_FRAME_LEN	30	//集中器协议中 排除消息体部分的帧长度(包括消息体校验)
#define GATEWAY_FRAME_MAX_LEN	2048//每帧协议最大长度
#define GATEWAY_METERINFO_LEN	40//仪表信息的长度
#define GATEWAY_MAX_METERINFO_CNT	24//集中器协议中每行最大下发多少行数据
#define GATEWAY_BODY_OFFSET	27//消息体偏移量
#define GATEWAY_BODYLEN_OFFSET	17//消息体长度偏移量
//#define GATEWAY_MAX_METERINFO_CNT	2//集中器协议中每行最大下发多少行数据
#define GATEWAY_ISSUE_BODY_HEAD	3//下发表地址消息头的长度

#define GATEWAY_TIMENODE_CNT_LEN	1//抄表时间点个数的长度
#define GATEWAY_TIMENODE_LEN		2//每个抄表时间点的长度
#define GATEWAY_TIMENODE_MAX_CNT	24//现在ARM7最多支持多少个抄表时间点

#define GATEWAY_ASWCODE_OFFSET		19//集中器返回帧中应答码的偏移量
#define GATEWAY_STATCODE_OFFSET		27//集中器返回帧中成功状态码的偏移量
#define GATEWAY_SEQCODE_OFFSET		28//集中器返回帧中服务器发送的序列码的偏移量
#define GATEWAY_WITHSEQ_LEN			32//集中器返回帧中带有服务器发送的序列号的帧长度
#define GATEWAY_WITHOUTSEQ_LEN		31//集中器返回帧中不带有服务器发送的序列号的帧长度
//异常回应代码--表示意义
#define GAT_EXCEP_FAIL          0x10//失败, 异常
#define GAT_EXCEP_MEASURE_POINT 0x11//异常, 查不到指定计量点号。
#define GAT_EXCEP_CHANNEL_BUSY  0x12//异常, 集中器正忙, 现在不能抄表.
#define GAT_EXCEP_PARAM_EXCEED  0x13//参数超出允许范围
#define GAT_EXCEP_PROTO_VER     0x14//消息体版本号错误

/*集中器协议中MSG_TYPE代表的意义 START*/
#define GAT_MT_SVR_CP_1_METER   0x06//主站下发抄单表指令(0x06)
#define GAT_MT_CLT_CP_1_METER   0x07//集中器向主站发送单抄表结果(0x07)

#define GAT_MT_SVR_1OF_MFRM     0x11//主站请求多包传输特定包数据(0x11)

#define GAT_MT_SVR_MODIFY_SINFO 0x13//主站更改单个计量点基础信息(0x13)
#define GAT_MT_CLT_MODIFY_SINFO 0x14//集中器响应主站更改单个热表地址信息(0x14)

#define GAT_MT_SVR_SEND_MINFO   0x0C//主站下发所有仪表地址(0x0C)
#define GAT_MT_CLT_SEND_MINFO	0x0D//集中器响应主站下发仪表地址(0x0D)

#define GAT_MT_SVR_TIME_POINT   0x20//主站设置定时抄表时间(0x20)
#define GAT_MT_CLT_TIME_POINT   0x21//设置定时抄表时间反馈(0x21)

#define GAT_MT_SVR_HISDATA      0x22//主站向集中器请求历史时间点的所有表数据(0x22)
#define GAT_MT_CLT_HISDATA      0x23//集中器向主站发送固定时间点数据内容(0x23)

#define GAT_MT_SVR_TIME_SET     0x24//设置集中器时钟时间(0x24)
#define GAT_MT_CLT_TIME_SET     0x25//集中器响应设置时间(0x25)

#define GAT_MT_SVR_TIME_RD      0x26//读取集中器时钟时间(0x26)
#define GAT_MT_CLT_TIME_RD      0x27//集中器响应设置时间(0x27)

#define GAT_MT_CLT_HB           0x2E//GPRS心跳(0x2E)
#define GAT_MT_SVR_HB           0x2F//GPRS心跳回应(0x2F)

#define GAT_MT_SVR_REREAD       0x3A//主站更改补抄表相关参数(0x3A)单位ms
#define GAT_MT_CLT_REREAD       0x3B//集中器响应主站更改补抄表相关参数(0x3B)单位ms

#define GAT_MT_SVR_REBOOT       0x34//集中器重启指令(0x34)
#define GAT_MT_CLT_REBOOT       0x35//对重启指令的回应(0x35)集中器收到重启指令后, 会先回应上位机, 5秒后重启

#define GAT_MT_SVR_SHISDATA     0x3C//主站向集中器请求历史时间点某单表的数据(0x3C)
#define GAT_MT_CLT_SHISDATA     0x3D//集中器向主站发送固定时间点某单表的数据(0x3D)

#define GAT_MT_SVR_CPY_IMMDT    0x3E//设置集中器立即抄表(0x3E)
#define GAT_MT_CLT_CPY_IMMDT    0x3F//集中器响应立即抄表设置(0x3F)

#define GAT_MT_SVR_RD_CONFIG    0x90//主站读取集中器参数(0x90)
#define GAT_MT_CLT_RD_CONFIG    0x91//主站读取集中器参数响应(0x91)

#define GAT_MT_SVR_RD_ALLINFO   0x92//主站读取集中器中全部热表地址信息 (0x92 )
#define GAT_MT_CLT_RD_ALLINFO   0x93//集中器向主站发送热表地址信息(0x93)

#define GAT_MT_SVR_CHIP         0x94//主站更改集中器IP及端口号(0x94)
#define GAT_MT_CLT_CHIP         0x95//集中器响应主站更改集中器IP及端口号响应(0x95)

#define GAT_MT_SVR_MID			0x98//主站更改集中器及其主站编号
#define GAT_MT_CLT_MID			0x99//集中器响应主站更改集中器及其主站编号
/*集中器协议中MSG_TYPE代表的意义 END*/

#define	GATEWAY_ASW_CODE_SUC				0x01//操作成功
#define GATEWAY_ASW_CODE_FAIL				0x10//操作失败
#define GATEWAY_ASW_CODE_NOREC				0x11//查不到指定计量点号
#define GATEWAY_ASW_CODE_MBUS_BUSY			0x12//MBUS正忙
#define GATEWAY_ASW_CODE_EXCEED				0x13//参数出允许范围
#define GATEWAY_ASW_CODE_MSGBODY_VER_ERR	0x14//消息体版本号错误

#define PROTO_LEN_MADDR		7//协议中仪表地址长度
#define PROTO_LEN_VADDR		7//协议中阀门地址长度
#define PROTO_LEN_ROWID		2//协议中计量点编号长度
#define PROTO_LEN_ROOMID	2//协议中房间编号长度
#define PROTO_LEN_RSV		8//保留字段

/************************************************************************/
/*                       阀门开度                                       */
/************************************************************************/
#define PROTO_VOPEN_ZERO	0x99//全关
#define PROTO_VOPEN_QUATER	0x88//四分之一开
#define PROTO_VOPEN_HALF	0x77//半开
#define PROTO_VOPEN_3QUATER	0x66//四分之三开
#define PROTO_VOPEN_ALL		0x55//全开
/************************************************************************/

/************************************************************************/
/*                       一天24小时的时间点                               */
/************************************************************************/
#define TNODE_00	0x00//时间点00时
#define TNODE_01	0x01//时间点01时
#define TNODE_02	0x02//时间点02时
#define TNODE_03	0x03//时间点03时
#define TNODE_04	0x04//时间点04时
#define TNODE_05	0x05//时间点05时
#define TNODE_06	0x06//时间点06时
#define TNODE_07	0x07//时间点07时
#define TNODE_08	0x08//时间点08时
#define TNODE_09	0x09//时间点09时
#define TNODE_10	0x10//时间点10时
#define TNODE_11	0x11//时间点11时
#define TNODE_12	0x12//时间点12时
#define TNODE_13	0x13//时间点13时
#define TNODE_14	0x14//时间点14时
#define TNODE_15	0x15//时间点15时
#define TNODE_16	0x16//时间点16时
#define TNODE_17	0x17//时间点17时
#define TNODE_18	0x18//时间点18时
#define TNODE_19	0x19//时间点19时
#define TNODE_20	0x20//时间点20时
#define TNODE_21	0x21//时间点21时
#define TNODE_22	0x22//时间点22时
#define TNODE_23	0x23//时间点23时
/************************************************************************/

#pragma pack(push)
#pragma pack(1)

typedef struct{//统一为BCD码
    uint8 u8second;
    uint8 u8minute;
    uint8 u8hour;
    uint8 u8day;
    uint8 u8month;
    uint8 u8year;
}sys_time_str;
typedef sys_time_str* sys_time_ptr;

typedef struct{//下发集中器仪表基础信息结构
    U8 rowId[PROTO_LEN_ROWID];		//计量点, 用作唯一标示一行(Little Ending, Hex)
    U8 meterAddr[PROTO_LEN_MADDR];  //仪表(热量表,水表等)地址(Little Ending, BCD)
    U8 vendorId;					//厂商代码(Hex)
    U8 protoVer;					//仪表协议版本号(Hex)
    U8 meterType;					//仪表类型(Hex)
    U8 channel;						//通道号(Hex)
    U8 valveProtoVer;				//阀控协议版本号(Hex)
    U8 valveAddr[PROTO_LEN_VADDR];  //阀控地址(Little Ending, BCD)
    U8 controlPanelAddr[PROTO_LEN_VADDR]; //温控面板地址(Little Ending, BCD)
    U8 buildId;						//楼栋号(Hex)
    U8 unitId;						//单元号(Hex)
    U8 roomId[PROTO_LEN_ROOMID];    //房间号(Little Ending, Hex)
    U8 reserved[PROTO_LEN_RSV];     //保留字段
}meter_row_str;
typedef meter_row_str* meter_row_ptr;

typedef struct {//集中器表基础信息消息头
    U8 totalRows;			//一共有多少行表地址
    U8 seq;					//本帧的索引号
    U8 thisRows;			//本帧包含多少行表地址
}meterinfo_bodyHead_str;
typedef meterinfo_bodyHead_str* meterinfo_bodyHead_ptr;

typedef struct {//下发GPRS相关参数结构体
    U8 Method;			//超声波热计量表20H;电子式热分配表A0H;时间通断面积法B0H;
    U8 DataSource;		//0X0A 上位机，0X0B本地抄表
    U8 Period[2];		//分摊周期（分钟）
    U8 LogReportTime;	//0x00 :打开 ，0x01:不打开
    U8 LogOpenType; 	//0X00: 打开 ，0X01 ：不打开
    U8 APN;             //GPRS网络APN接入点选择.
    U8 IPAddr[4];		//0是低位IP  3是高位IP 16进制下发
    U8 HostPor[2];		//主站端口号高8位  (注：端口号高低字节顺序和0x90、0x91读取时顺序相反！)
}gprs_param_str;
typedef gprs_param_str* gprs_param_ptr;

typedef struct {//读取GPRS以及软硬件版本等信息的结构体
    U8 Ip[4];			//服务器IP, 倒序
    U8 Port[2];			//服务器端口
    U8 Address[6];		//集中器地址
    U8 HostAddress[6];	//主站地址
    U8 SoftVer[2];		//软件版本号, 例如：0x0232代表2.32
    U8 HardwareVer[2];	//硬件版本号, 例如：0x0232代表2.32*/
    U8 u8APN;			//GPRS模块APN接入点，0-cmnet公网，1-联通M2M物联网，2-威海热电。
    U8 u8Reserved[6];	//保留
} gateway_params_str;
typedef gateway_params_str* gateway_params_ptr;

typedef struct {//补抄相关参数结构体
    U8	mReadCnt;	//热表补抄次数
    U16 mReadIntv;	//热表补抄时间间隔ms
    U8	vReadCnt;	//阀控补抄次数
    U16 vReadIntv;	//阀控补抄时间间隔ms
}reread_param_str;
typedef reread_param_str* reread_param_ptr;

typedef struct {//消息头部结构体
    U8 prefix[GATEWAY_PREFIX_CNT];		//前导符0xFB
    U8 start;							//开始符0x7B
    U8 protoVer;						//协议版本号
    U8 SourceAddr[GATEWAY_SADD_LEN];	//源地址, 发送方地址
    U8 DestAddr[GATEWAY_OADD_LEN];		//目的地址, 接收方地址
    U8 MsgID;							//消息序列
    U16 bodyLen;						//消息体长度
    U8 MsgType;							//消息类型
    sys_time_str sysTime;				//TS时间标签
    U8 HeadCheck;						//消息头校验
} protocol_head_str;
typedef protocol_head_str* protocol_type_ptr;

typedef struct {//集中器协议消息体结构
    protocol_head_str head_str;	//消息头部
    U8 *pMsgBody;				//消息体指针
    U8	bodyChk;				//消息体校验
} gateway_protocol_str;
typedef gateway_protocol_str* gateway_protocol_ptr;

typedef struct {//读取集中器表地址信息, 消息头结构体
    U8 succeed;		//是否有后继帧, 0-没有, 1-有, 10-异常
    U8 seq;			//本包序号
    U8 meterType;	//仪表类型, 固定为0x20
    U8 rowCnt;		//本帧包含的表地址数量
} base_info_head_str;
typedef base_info_head_str* base_info_head_ptr;

typedef struct {//读取集中器热表历史信息结构体
    U8	DailyHeat[4];			//结算日热量
    U8	DailyHeatUnit;			//一般为kWh, 0x05
    U8	CurrentHeat[4];			//当前热量
    U8	CurrentHeatUnit;		//一般为kWh, 0x05
    U8	HeatPower[4];			//热功率
    U8	HeatPowerUnit;			//一般为kW, 0x17
    U8	Flow[4];				//流量流速
    U8	FlowUnit;				//一般为m3/h, 0x35
    U8	AccumulateFlow[4];		//累积流量
    U8	AccumulateFlowUnit;		//一般为m3, 0x2C
    U8	WaterInTemp[3];			//供水温度
    U8 	WaterOutTemp[3];		//回水温度
    U8 	AccumulateWorkTime[3];	//累计工作时间
    U8	RealTime[7];		    //实时时间
    U16	ST;					    //状态ST
}CJ188_Format;
typedef CJ188_Format* CJ188_Format_ptr;

typedef struct {//历史数据中的固定信息部分
    U16 meterId;				//计量点号
    U8	meterType;				//仪表类型
    U8	meterAddr[7];			//仪表地址
    U8	buildId;				//楼号
    U8	unitId;					//单元号
    U16	roomId;					//房间号
    U8	mSecondBCD;				//抄热表秒BCD
    U8	mMinuteBCD;				//抄热表分钟BCD
    U8	mHourBCD;				//抄热表小时BCD
    U8	meterDataLen;			//热表数据长度
} hisdata_meter_fix_str;
typedef hisdata_meter_fix_str* hisdata_fix_ptr;

typedef struct {
    U8	vSecondBCD;				//抄阀秒BCD
    U8	vMinuteBCD;				//抄阀分钟BCD
    U8	vHourBCD;				//抄阀小时BCD
    U8	RoomTempBCD[3];			//室内温度
    U8	vOpen;					//阀门开度
    U8	vState;					//阀门状态
    U8	vReserve;				//保留
} hisdata_valve_fix_str;
typedef hisdata_valve_fix_str* hisdata_valve_fix_ptr;

typedef struct {//温控计量一体化, 历史数据格式
    hisdata_meter_fix_str	fixMeter;//热表的固定部分
#ifdef CJ188_HEAT_METER
    CJ188_Format	MeterData;		//热表数据
#endif // CJ188_HEAT_METER
    hisdata_valve_fix_str fixValve;	//阀控的固定部分
} tempControl_messure_hisdata_str;
typedef tempControl_messure_hisdata_str* tempControl_messure_hisdata_ptr;

typedef struct {//温控计量一体化和通断时间面积法的历史数据头部结构
    U8 succeed;		//是否有后继帧, 0-没有, 1-有, 10-异常
    U8 seq;			//本包序号
    U8 u8second;	//存储时的秒
    U8 u8minute;	//存储时的分
    U8 u8hour;		//存储时的时
    U8 u8day;		//存储时的日
    U8 u8month;		//存储时的月
    U8 u8year;		//存储时的年
} hisdata_head_str;
typedef hisdata_head_str*  hisdata_head_ptr;

typedef struct {//透传计量点数据中的固定信息部分
    U16 meterId;				//计量点号
    U8	meterType;				//仪表类型
    U8	meterAddr[7];			//仪表地址
    U8	buildId;				//楼号
    U8	unitId;					//单元号
    U16	roomId;					//房间号
    U8	meterDataLen;			//热表数据长度
} remote_meter_fix_str;
typedef remote_meter_fix_str* remote_meter_fix_ptr;

typedef struct {
    U8	RoomTempBCD[3];			//室内温度
    U8	vOpen;					//阀门开度
    U8	vState;					//阀门状态
    U8	vReserve;				//保留
} remote_valve_fix_str;
typedef remote_valve_fix_str* remote_valve_fix_ptr;

typedef struct {//温控计量一体化, 历史数据格式
    remote_meter_fix_str	fixMeter;//热表的固定部分
#ifdef CJ188_HEAT_METER
    CJ188_Format	MeterData;		//热表数据
#endif // CJ188_HEAT_METER
    remote_valve_fix_str fixValve;	//阀控的固定部分
} tempControl_messure_remote_str;
typedef tempControl_messure_remote_str* tempControl_messure_remote_ptr;

#pragma pack(pop)

#endif//GATEWAY_PROTOCOL_VER==0x03
#endif // GATEWAY_PROTOCOL_VER

#endif // PROTOCOL_H

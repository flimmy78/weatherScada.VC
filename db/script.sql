---------------------------------
--历史数据表
---------------------------------
drop table if exists "t_history_data"
;

create table t_history_data
(
	f_id integer not null primary key autoincrement, --主键 float, 自增
	f_timestamp timestamp default (datetime('now', 'localtime')), --插入时的时间戳（'yyyy-MM-dd HH:mm:ss.zzz')
	f_timenode timestamp,			--抄读仪表数据时的时间点(每天24小时的那个时间点)
	f_tIn float,					--供水温度
	f_tOut float,					--回水温度
	f_tAvg float,					--供回水的平均温度
	f_flowRate float,				--流速m3/h
	f_power float,					--热功率kW
	f_accumFlow float,				--累计流量m3
	f_deltaFlow float,				--流量增量m3
	f_energy float,					--累计热量kWh
	f_deltaEnergy float,			--热量增量kWh
	f_inTemp1 float,				--室内温度1
	f_inTemp2 float,				--室内温度2
	f_outTemp1 float,				--室外温度1
	f_outTemp2 float,				--室外温度2
	f_windRate float,				--风速m/s
	f_weather float,				--天气情况
	f_roomArea float				--房屋建筑面积
);
create unique index uk_timeNode on t_history_data(f_timenode);
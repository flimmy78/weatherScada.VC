---------------------------------
--历史数据表
---------------------------------
drop table if exists "t_history_data"
;

create table t_history_data
(
	f_id integer not null primary key autoincrement,
	f_timestamp timestamp not null,     --插入时的时间戳（'yyyy-MM-dd HH:mm:ss.zzz')
	f_timenode							--抄读仪表数据时的时间点(每天24小时的那个时间点)
	
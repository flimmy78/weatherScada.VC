---------------------------------
--��ʷ���ݱ�
---------------------------------
drop table if exists "t_history_data"
;

create table t_history_data
(
	f_id integer not null primary key autoincrement,
	f_timestamp timestamp not null,     --����ʱ��ʱ�����'yyyy-MM-dd HH:mm:ss.zzz')
	f_timenode							--�����Ǳ�����ʱ��ʱ���(ÿ��24Сʱ���Ǹ�ʱ���)
	
---------------------------------
--��ʷ���ݱ�
---------------------------------
drop table if exists "t_history_data"
;

create table t_history_data
(
	f_id integer not null primary key autoincrement, --���� float, ����
	f_timestamp timestamp default (datetime('now', 'localtime')), --����ʱ��ʱ�����'yyyy-MM-dd HH:mm:ss.zzz')
	f_timenode timestamp,			--�����Ǳ�����ʱ��ʱ���(ÿ��24Сʱ���Ǹ�ʱ���)
	f_tIn float,					--��ˮ�¶�
	f_tOut float,					--��ˮ�¶�
	f_tAvg float,					--����ˮ��ƽ���¶�
	f_flowRate float,				--����m3/h
	f_power float,					--�ȹ���kW
	f_accumFlow float,				--�ۼ�����m3
	f_deltaFlow float,				--��������m3
	f_energy float,					--�ۼ�����kWh
	f_deltaEnergy float,			--��������kWh
	f_inTemp1 float,				--�����¶�1
	f_inTemp2 float,				--�����¶�2
	f_outTemp1 float,				--�����¶�1
	f_outTemp2 float,				--�����¶�2
	f_windRate float,				--����m/s
	f_weather float,				--�������
	f_roomArea float				--���ݽ������
);
create unique index uk_timeNode on t_history_data(f_timenode);
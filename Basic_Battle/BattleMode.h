#pragma once

#include <time.h>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

#define TIME_LEFT_MAX 4000


class BattleMode
{
public:
	//ָʾ����ս����ģʽ����
	string battleTypeName;
	bool limitTime;		//ʱ������?
	int limit_time_frame;		//ʱ��֡��

	bool record;		//�Ƿ�����¼��

	//bool debug_log;		//�Ƿ����ɵ��Լ�¼

	string record_name;		//¼�����ƺ�·��

	bool statistics;		//�Ƿ�����ս��ͳ��
	string battle_statistics_name;			//BattleStatistics·������

	string map_name;		//��ͼ�ļ�·������!!!

	string json_path;
	string xmlformat_path;

	BattleMode():record_name("Record_tmp.txt")
	{
		battleTypeName="undef";
		limitTime=true;
		limit_time_frame=TIME_LEFT_MAX;
		record=true;
		statistics=false;
		map_name = "!!!";
		json_path = "./GameData.json";
		xmlformat_path = "./battle_xml_format.xml";
		//debug_log=false;
	}


	BattleMode(bool _is_limit_time,int _limit_time_frame,bool _is_record,string _record_name):record_name(_record_name)
	{
		battleTypeName="undef";
		limitTime=_is_limit_time;
		limit_time_frame=_limit_time_frame;
		record=_is_record;
		statistics=false;
	}

	//filename  �ļ�����·��
	void SetByConfigFile(const char * filename)
	{
		//BattleModeConfig.conf��ʽ
		//ս��ģʽ�����������

		//�Ƿ�����ʱ��
		//ʱ������֡��
		//�Ƿ�����¼��
		//¼��·��
		//�Ƿ�����ս��ͳ����Ϣ
		//BattleStatistics���·��
		//��ͼ�ļ�����·������!!!




		ifstream in;
		in.open(filename);
		if(in.is_open())
		{



			string tmp;
			getline(in,tmp);	//��һ��������������й��ܣ������ӵ�


			getline(in,battleTypeName);	//ս��ģʽ�����������

			in>>limitTime;				//�Ƿ�����ʱ��
			in>>limit_time_frame;		//ʱ������֡��
			in>>record;					//�Ƿ�����¼��
			in>>record_name;			//!!����¼��·��
			in>>statistics;				//�Ƿ�����ս��ͳ����Ϣ
			in>>battle_statistics_name;//!!�˴�����ս��ͳ�Ƶ����·��


			in>>map_name;

			in>>json_path;
			in>>xmlformat_path;

			in.close();




			string tstr=TimeString();
			record_name+=tstr+"_battleRecord.txt";
			battle_statistics_name+=tstr+"_battleStatistics.xml";

			/*
            cout<<'\n'<<filename<<'\n'
				<<battleTypeName<<'\n'
				<<limitTime<<'\n'
				<<limit_time_frame<<'\n'
				<<record<<'\n'
				<<record_name<<'\n'
				<<statistics<<'\n'
				<<battle_statistics_name<<'\n';
            */
		}
	}

	string TimeString(/*...*/)
	{
		time_t t=time(0);
		struct tm buf;
		char tmp[25];
		localtime_s(&buf, &t);
		strftime(tmp,sizeof(tmp),"%y-%m-%d-%H-%M-%S", &buf);
		string tmp2=tmp;

		return tmp2;
	}

};

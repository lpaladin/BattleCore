//#include "stdafx.h"

#include <fstream>

#include "Basic_Battle/Robot/RobotAITest.h"

#include "stdafx.h"
#include "BattleCoreOutput.h"




void LoadGameData()
{
	//pDataLoader->LoadDataFromLuaScript("GameData.lua");
	pDataLoader->LoadDataFromJSON(pBattlefield->battleMode.json_path.c_str());
}


void InitNewBattle()
{
	//�������������
	SetSeed();

	//��ɨ֮ǰ��ս��
	pBattlefield->SweepBattlefield(true,true,true,true);

}

/*
void SetBattleMode(const BattleMode & battleMode)
{
	pBattlefield->SetBattleMode(battleMode);
}
*/

void SetBattleModeWithConfigFile(const char * filename)
{
	pBattlefield->SetBattleModeWithConfigFile(filename);
}

void SetBattleModeNew(const char * filename,const char * record_path,const char * statistics_path)
{
	pBattlefield->SetBattleModeWithConfigFile(filename);
	pBattlefield->SetBattleModeNew(record_path,statistics_path);
}


int AddRobotAI(RobotAI_Interface* pAI)
{
	//��Battlefield���AI
	//ΪpAIָ���AI�����µĻ����˼��뵽ս��
	
	
	//����ָ�븳ֵ
	pAI->trace=trace_global;		//�����������ָ��
	
	pAI->getWeaponName=getWeaponName;
	//pAI->getWeaponDamage=getWeaponDamage;
	pAI->getWeaponAmmo=getWeaponAmmo;
	pAI->getWeaponCoolingTime=getWeaponCoolingTime;
	pAI->getWeaponInaccuracy=getWeaponInaccuracy;
	pAI->getWeaponRotationSpeed=getWeaponRotationSpeed;
	
	pAI->getEngineName=getEngineName;
	pAI->getEngineMaxSpeed=getEngineMaxSpeed;
	pAI->getEngineMaxHp=getEngineMaxHp;
	pAI->getEngineRotationSpeed=getEngineRotationSpeed;
	pAI->getEngineAcceleration=getEngineAcceleration;

	pAI->getBulletName=getBulletName;
	pAI->getBulletSpeed=getBulletSpeed;
	pAI->getBulletDamage=getBulletDamage;
	pAI->getBulletFlyTime=getBulletFlyTime;
	///////////////////
	

	//TODO:�����indexԭ����AIManager�е�AI�±�
	//���ڲ���Ҫ��
	//��װ��BattleCore����������������AI����Ϣ

	//ֻҪ���ص�ǰ����AI��pRobot���±�
	return (pBattlefield->AddRobotAI(pAI,0));	//��0����һ��
}

/*
AchievementData_Battle& GetAchievementData(int robotID)
{
	return (pBattlefield->GetAchievementData(robotID));
}
*/

/*
BattleStatistics& GetBattleStatistics()
{
	return (pBattlefield->GetBattleStatistics());
}
*/




bool LaunchBattle()
{
	pBattlefield->NewBattle();

	//temp
	return true;
}



#ifdef ROBOT_AI_TEST

void StartTestingBattleWithRandomEquipment()
{
	BattleMode defaultBattleMode(true,4000,true,"zTestingBattle.txt");
	RobotAI_Interface* ai0=new RobotAITest();
	RobotAI_Interface* ai1=new RobotAITest();


	InitNewBattle();
	pBattlefield->SetBattleMode(defaultBattleMode);
	int id0=AddRobotAI(ai0);
	int id1=AddRobotAI(ai1);
	LaunchBattle();

	//TODO:��ӡһЩս��ͳ������
	BattleStatistics& battleStatistics=pBattlefield->GetBattleStatistics();

	cout<<"winner id: "<<battleStatistics.winnerID<<'\n';

	delete ai0;
	delete ai1;
}

void StartTestingBattleWithAssignedEquipment(int weapon0,int engine0,int weapon1,int engine1)
{
	BattleMode defaultBattleMode(true,4000,true,"zTestingBattle.txt");
	
	RobotAI_Interface* ai0=new RobotAITest();
	((RobotAITest*)ai0)->m_weapon=(weapontypename)weapon0;
	((RobotAITest*)ai0)->m_engine=(enginetypename)engine0;

	RobotAI_Interface* ai1=new RobotAITest();
	((RobotAITest*)ai1)->m_weapon=(weapontypename)weapon1;
	((RobotAITest*)ai1)->m_engine=(enginetypename)engine1;


	InitNewBattle();
	pBattlefield->SetBattleMode(defaultBattleMode);
	int id0=AddRobotAI(ai0);
	int id1=AddRobotAI(ai1);
	LaunchBattle();

	//TODO:��ӡһЩս��ͳ������
	BattleStatistics& battleStatistics=pBattlefield->GetBattleStatistics();

	cout<<"winner id: "<<battleStatistics.winnerID<<'\n';

	delete ai0;
	delete ai1;
}


#endif
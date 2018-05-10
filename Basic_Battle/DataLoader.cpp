//#include "stdafx.h"
#include "../stdafx.h"
#include "DataLoader.h"

DataLoader::DataLoader() : weapon_data(Weapon_Number), engine_data(Engine_Number), bullet_data(Bullet_Number)
{
	GameData = new DataVessel;
}

DataLoader::~DataLoader()
{
	//lua_close(pLuaState);
	delete GameData;
	GameData = NULL;
}

void DataLoader::Close()
{
	delete rawJson;
}
DataLoader *DataLoader::getInstance()
{
	static DataLoader instance;
	return &instance;
}

DataVessel *DataLoader::GetGameData()
{
	return GameData;
}

template <typename T>
bool DataLoader::GetNumber(const char *varName, T &Dest)
{
	auto var = (*rawJson)[varName];
	if (var.isDouble())
		Dest = var.asDouble();
	else if (var.isInt())
		Dest = var.asInt();
	else
	{
		cout << "\n[C++]:ERROR:Invalid type!\n";
		return false;
	}
	return true;
}
bool DataLoader::GetString(const char *varName, string &Dest)
{
	auto var = (*rawJson)[varName];
	if (!var.isString())
	{
		cout << "\n[C++]:ERROR:Invalid type!\n";
		return false;
	}
	Dest = var.asString();
	return true;
}

template <typename T>
bool DataLoader::LoadNumArray(const char *arrayName, int MaxNum, T *Dest)
{
	auto var = (*rawJson)[arrayName];
	if (!var.isObject())
	{
		cout << "\n[C++]:ERROR:Invalid type!\n";
		return false;
	}
	for (int i = 0; i < MaxNum; i++)
	{
		auto val = var[i];
		if (val.isDouble())
			Dest[i] = val.asDouble();
		else if (val.isInt())
			Dest[i] = val.asInt();
		else
		{
			cout << "\n[C++]:ERROR:Invalid type of member in array!\n";
			return false;
		}
	}
	return true;
}

bool DataLoader::LoadStrArray(const char *arrayName, int MaxNum, string *Dest)
{
	auto var = (*rawJson)[arrayName];
	if (!var.isObject())
	{
		cout << "\n[C++]:ERROR:Invalid type!\n";
		return false;
	}
	for (int i = 0; i < MaxNum; i++)
		Dest[i] = var[i].asString();
	return true;
}

bool DataLoader::LoadDataFromJSON(const char *fileName)
{
	ifstream ifs(fileName);
	//打开游戏文件
	if (!ifs)
	{
		cout << "\n[C++]: ERROR: Problem with loading json config file!\n"
			 << endl;
		return false;
	}

	Json::Reader reader;
	reader.parse(ifs, *(rawJson = new Json::Value));

	//加载游戏数据

	//Weapon

	LoadStrArray("name_Weapon", Weapon_Number, GameData->name_Weapon);
	//LoadNumArray("damage_Weapon",Weapon_Number,GameData->damage_Weapon);
	LoadNumArray("Ammo_Weapon", Weapon_Number, GameData->Ammo_Weapon);
	LoadNumArray("coolingTime_Weapon", Weapon_Number, GameData->coolingTime_Weapon);
	LoadNumArray("inaccuracy_Weapon", Weapon_Number, GameData->inaccuracy_Weapon);
	LoadNumArray("rotationSpeed_Weapon", Weapon_Number, GameData->rotationSpeed_Weapon);

	LoadNumArray("radium_Weapon", Weapon_Number, GameData->radium_Weapon);

	GetNumber("coolingSpeed_AllWeapon", GameData->coolingSpeed_AllWeapon);

	GetNumber("burst_Shotgun", GameData->burst_Shotgun);
	GetNumber("gapRotation_Shotgun", GameData->gapRotation_Shotgun);

	GetNumber("coolingTime_Tiny_MineLayer", GameData->coolingTime_Tiny_MineLayer);
	GetNumber("ammoConsumption_Mine_MineLayer", GameData->ammoConsumption_Mine_MineLayer);
	//Bullet

	GetNumber("bounce_time", GameData->bounce_time);

	LoadStrArray("name_Bullet", Bullet_Number, GameData->name_Bullet);
	LoadNumArray("speed_Bullet", Bullet_Number, GameData->speed_Bullet);
	LoadNumArray("damage_Bullet", Bullet_Number, GameData->damage_Bullet);
	LoadNumArray("flyTime_Bullet", Bullet_Number, GameData->flyTime_Bullet);

	GetNumber("explodeR_RPGBall", GameData->explodeR_RPGBall);
	GetNumber("acceleration_RPGBall", GameData->acceleration_RPGBall);

	GetNumber("explodeR_Grenade", GameData->explodeR_Grenade);

	GetNumber("explodeR_Mine", GameData->explodeR_Mine);

	GetNumber("spinSpeed_TrackingMissile", GameData->spinSpeed);

	//Engine

	LoadStrArray("name_Engine", Engine_Number, GameData->name_Engine);
	LoadNumArray("maxSpeed_Engine", Engine_Number, GameData->maxSpeed_Engine);
	LoadNumArray("maxHp_Engine", Engine_Number, GameData->maxHp_Engine);
	LoadNumArray("rotationSpeed_Engine", Engine_Number, GameData->rotationSpeed_Engine);
	LoadNumArray("acceleration_Engine", Engine_Number, GameData->acceleration_Engine);

	LoadNumArray("radium_Engine", Engine_Number, GameData->radium_Engine);

	GetNumber("radium_Arsenal", GameData->radium_Arsenal);
	GetNumber("respawningTime_Arsenal", GameData->respawningTime_Arsenal);

	Close();

	//construct weapon,engine static data vector
	ConstructDataVector();

	return true;
}

void DataLoader::ConstructDataVector()
{
	//vector<WeaponData>::iterator iter;
	int i;
	for (i = 0; i < Weapon_Number; i++)
	{
		weapon_data.at(i).LoadStaticData((weapontypename)i);
	}
	for (i = 0; i < Engine_Number; i++)
	{
		engine_data.at(i).LoadStaticData((enginetypename)i);
	}
	for (i = 0; i < Bullet_Number; i++)
	{
		bullet_data.at(i).LoadStaticData((bullettypename)i);
	}
}

WeaponData &DataLoader::getWeaponData(weapontypename wtn)
{
	WeaponData &w = weapon_data.at((int)wtn);
	return w;
}
EngineData &DataLoader::getEngineData(enginetypename etn)
{
	EngineData &e = engine_data.at((int)etn);
	return e;
}
BulletData &DataLoader::getBulletData(bullettypename btn)
{
	BulletData &b = bullet_data.at((int)btn);
	return b;
}
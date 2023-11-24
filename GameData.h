#pragma once
#include <vector>
#include <iostream>
#include <DirectXMath.h>

//ゲームデータ管理
namespace GameData {

	void SetSpeed(int _spd);
	void AddSpeed(int _spd);
	int GetSpeed();
	void UpdateSpeed();
	std::string GetSpeedString();

	void SetTime(int _time);
	void AddTime(int _addT);
	void UpdateTimeString();
	int GetTime();
	std::string GetTimeString();

	void SetMeters(int _meters);
	void UpdateMeterString();
	std::string GetMeterString();
	void AddMeters(int _addM);
	int GetMeters();

	void SetHits(int _hits);
	void AddHits(int _addH);
	int GetHits();

	void SetHealth(int _health);
	void AddHealth(int _addHP);
	int GetHealth();

	void SetTempHealth(int _tempHealth);
	void AddTempHealth(int _addTHP);
	int GetTempHealth();

	int GetMaxHealth();

	void SetGamemode(int _gamemode);
	int GetGamemode();

	void Reset();
	void ParamCheck(int* _param, int _min, int _max);
}


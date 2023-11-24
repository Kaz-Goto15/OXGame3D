#include "GameData.h"
#include "Engine/Global.h"
#include "Engine/Debug.h"
#include <iostream>
#include <string>

namespace GameData {

	//ゲームモード	BASIC/ENDLESS
	static int gamemode;

	//最終スコア関連
	static int speed;
	static int time;
	static long long meters;
	static int hits;
	static std::string timeString, meterString, speedString;
	int tmp[5];

	//エンドレス用
	static int health, tempHealth, maxHealth;

	void SetSpeed(int _spd) {
		speed = _spd;
		UpdateSpeed();
	}
	void AddSpeed(int _spd) { 
		speed += _spd; 
		UpdateSpeed();
	}
	int GetSpeed() { return speed; }
	void UpdateSpeed() {
		tmp[0] = speed / 2;
		if (speed % 2 == 1) { tmp[1] = 5; }
		else tmp[1] = 0;

		speedString = std::to_string(tmp[0]) + ".";
		speedString += std::to_string(tmp[1]);
	}
	std::string GetSpeedString() { return speedString; }


	void SetTime(int _time) {
		time = _time;
		UpdateTimeString();
	}
	void AddTime(int _addT) {
		time += _addT; 
		UpdateTimeString();
	}
	void UpdateTimeString() {
		tmp[0] = time / 60;
		tmp[1] = (time - tmp[0] * 60) * 100 / 60;
		timeString = std::to_string(tmp[0]) + ".";
		if (tmp[1] < 10)timeString += "0";
		timeString += std::to_string(tmp[1]);
	}
	int GetTime() { return time; }
	std::string GetTimeString() { return timeString; }


	void SetMeters(int _meters) {
		meters = _meters;
		UpdateMeterString();
	}
	void AddMeters(int _addM) {
		meters += _addM;
		UpdateMeterString();
	}
	void UpdateMeterString() {
		tmp[0] = meters / 100;
		tmp[1] = (meters - tmp[0] * 100) * 100 / 100;
		meterString = std::to_string(tmp[0]) + ".";
		if (tmp[1] < 10)meterString += "0";
		meterString += std::to_string(tmp[1]);
	}
	int GetMeters() { return meters; }
	std::string GetMeterString() { return meterString; }


	void SetHits(int _hits) { hits = _hits; }
	void AddHits(int _addM) { hits += _addM; }
	int GetHits() { return hits; }

	void SetHealth(int _health) {
		health = _health;
		ParamCheck(&health, 0, maxHealth);
	}
	void AddHealth(int _addHP) {
		health += _addHP;
		ParamCheck(&health, 0, maxHealth);
	}
	int GetHealth() { return health; }

	void SetTempHealth(int _tempHealth) {
		tempHealth = _tempHealth;
		ParamCheck(&tempHealth, 0, maxHealth);
	}
	void AddTempHealth(int _addTHP) {
		tempHealth += _addTHP;
		ParamCheck(&tempHealth, 0, maxHealth);
	}
	int GetTempHealth() { return tempHealth; }

	int GetMaxHealth() { return maxHealth; }

	void SetGamemode(int _gamemode) { gamemode = _gamemode; };
	int GetGamemode() { return gamemode; };

	void Reset() {
		speed = 2;
		time = 1800;
		meters = 0;
		hits = 0;
		timeString = "30.00";
		meterString = "0.00";
		speedString = "1.0";

		health = 1000;
		tempHealth = 1000;
		maxHealth = 1000;
	}

	void ParamCheck(int* _param, int _min = 0, int _max = maxHealth) {
		if (*_param < _min)*_param = _min;
		if (*_param > _max)*_param = _max;
	}
}
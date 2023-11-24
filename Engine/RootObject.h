#pragma once
#include "GameObject.h"

//-----------------------------------------------------------
//一番トップに来るオブジェクト
//すべてのオブジェクトは、これの子孫になる
//-----------------------------------------------------------
class RootObject :	public GameObject
{
public:
	RootObject();
	~RootObject();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};


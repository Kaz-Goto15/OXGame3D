#pragma once
#include <string>
using std::string;

namespace ModelLoader {
	enum MODEL {
		DEFAULT,
		Cube,
		Cylinder,
		Hanger,
		Player,
		MAX,
	};
	void Init();
	int Load(MODEL model);
	void ChangeAnim(MODEL model, string animName,float speed = 1);
};


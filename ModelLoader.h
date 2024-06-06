#pragma once
#include <string>
using std::string;

namespace ModelLoader {
	enum MODEL {
		DEFAULT,
		Plane,
		Cube,
		Cylinder,
		Hanger,
		Player,
		COLOR_YELLOW,
		MAX,
	};
	void Init();
	int Load(MODEL model);
	void ChangeAnim(int handle, string animName,float speed = 1);
};


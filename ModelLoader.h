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
		MARK_O,
		MARK_X,
		MAX,
	};
	void Init();
	int Load(MODEL model);
	void ChangeAnim(int handle, string animName,float speed = 1);
};


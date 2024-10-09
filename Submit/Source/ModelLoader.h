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
		MARK_1,
		MARK_2,
		MARK_3,
		MARK_4,
		MARK_5,
		MARK_6,
		MARK_7,
		MARK_8,
		MARK_9,
		CubeSelectIndicator,
		MAX,
	};
	void Init();
	int Load(MODEL model);
	void ChangeAnim(int handle, string animName,float speed = 1);
};


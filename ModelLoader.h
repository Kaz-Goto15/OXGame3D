#pragma once
namespace ModelLoader {
	enum MODEL {
		DEFAULT,
		Cube,
		Cylinder,
		Hanger,
		Player
	};
	void Init();
	int Load(MODEL model);
};


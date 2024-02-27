#pragma once
namespace ModelLoader {
	enum MODEL {
		DEFAULT,
		Cube,
		Cylinder
	};
	void Init();
	int Load(MODEL model);
};


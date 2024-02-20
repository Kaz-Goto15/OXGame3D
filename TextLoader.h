#pragma once
#include <string>
namespace TextLoader {
	enum TEXT_MEDIA {
		DEFAULT,
		RE_32px,
		GAKUMARU_32px,
		GAKUMARU_16px,
		KUROKANE_AQUA_30px,
		KUROKANE_AQUA_35px,
		KUROKANE_AQUA_50px,
		KUROKANE_AQUA_64px,
		STICK_B_PURPLE_35px,
	};
	void Load(TEXT_MEDIA tm, std::string &fileName,  unsigned int &charWidth,  unsigned int &charHeight,  unsigned int &rowLength);
};


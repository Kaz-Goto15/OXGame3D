#pragma once
//éQçlÅFTweener: Yuichi Tateno, Emmanuel Oga http://code.google.com/p/tweener/
//      easing_tra:UndoFish https://www.nicovideo.jp/watch/sm20813281

namespace Easing
{
	enum Ease {
		LINEAR,
		IN_QUAD,
		OUT_QUAD,
		IN_OUT_QUAD,
		OUT_IN_QUAD,
		IN_CUBIC,
		OUT_CUBIC,
		IN_OUT_CUBIC,
		OUT_IN_CUBIC,
		IN_QUART,
		OUT_QUART,
		IN_OUT_QUART,
		OUT_IN_QUART,
		IN_QUINT,
		OUT_QUINT,
		IN_OUT_QUINT,
		OUT_IN_QUINT,
		IN_SINE,
		OUT_SINE,
		OUT_IN_SINE,
		IN_EXPO,
		OUT_EXPO,
		IN_OUT_EXPO,
		OUT_IN_EXPO,
		IN_CIRC,
		OUT_CIRC,
		IN_OUT_CIRC,
		OUT_IN_CIRC,
		IN_ELASTIC,
		OUT_ELASTIC,
		IN_OUT_ELASTIC,
		OUT_IN_ELASTIC,
		IN_BACK,
		OUT_BACK,
		IN_OUT_BACK,
		OUT_IN_BACK,
		IN_BOUNCE,
		OUT_BOUNCE,
		IN_OUT_BOUNCE,
		OUT_IN_BOUNCE
	};

	float Calc(Ease easeNo, float nowtime, float endTime, float begin, float end);
};


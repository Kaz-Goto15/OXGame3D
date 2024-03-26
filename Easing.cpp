#include "Easing.h"
#define _USE_MATH_DEFINES
#include <cmath>
using std::powf;
using std::sinf;
using std::cosf;
using std::sqrtf;
using std::abs;
using std::asinf;
float pi = static_cast<float>(M_PI);

namespace Easing {
	float time;
	float duration;
	float begin;
	float change;

	static const int NUM_0 = 0;
	static const int NUM_1 = 1;
	static const int NUM_2 = 2;
	static const int NUM_3 = 3;
	static const int NUM_4 = 4;
	static const int NUM_5 = 5;
	static const int NUM_10 = 10;
	static const float NUM_p5 = 0.5f;
	static const float NUM_p75 = 0.75f;
	static const float NUM_p001 = 0.001f;
	static const float NUM_p0005 = 0.0005f;
	static const float NUM_p3 = 0.3f;
	static const float NUM_1p5 = 1.5f;
	static const float NUM_2p75 = 2.75f;
	static const float NUM_7p5625 = 7.5625f;
	static const float NUM_p625 = 0.625;
	static const float NUM_2p5 = 2.5f;
	static const float NUM_2p25 = 2.25f;
	static const float NUM_2p625 = 2.625f;
	static const float NUM_p9375 = 0.9375f;
	static const float NUM_p984375 = 0.984375f;

	float CalcTBCD(Ease e, float _time, float _begin, float change, float _duration) {
		return Calc(e, _time, _duration, _begin, change + _begin);
	}

	//1
	float Linear() {
		return change * time / duration + begin;
	};

	//2
	float InQuad() {
		time /= duration;
		return change * powf(time, NUM_2) + begin;
	}

	//3
	float OutQuad() {
		time /= duration;
		return -change * time * (time - NUM_2) + begin;
	}

	//4
	float InOutQuad() {
		time = time / duration * NUM_2;
		if (time < NUM_1) {
			return(change / NUM_2 * powf(time, NUM_2) + begin);
		}
		else {
			return(-change / NUM_2 * ((time - NUM_1) * (time - NUM_3) - NUM_1) + begin);
		}
	}

	//5
	float OutInQuad() {
		if (time < duration / NUM_2) {
			return CalcTBCD(OUT_QUAD, time * NUM_2, begin, change / NUM_2, duration);
		}
		else {
			return CalcTBCD(IN_QUAD, (time * NUM_2) - duration, begin + change / NUM_2, change / NUM_2, duration);
		}
	}

	//6
	float InCubic() {
		time = time / duration;
		return (change * powf(time, NUM_3) + begin);
	}

	//7
	float OutCubic() {
		time = time / duration - NUM_1;
		return (change * (powf(time, NUM_3) + NUM_1) + begin);
	}

	//8
	float InOutCubic() {
		time = time / duration * NUM_2;
		if (time < NUM_1) {
			return (change / NUM_2 * time * time * time + begin);
		}
		else {
			time = time - NUM_2;
			return (change / NUM_2 * (time * time * time + NUM_2) + begin);
		}
	}

	//9
	float OutInCubic() {
		if (time < duration / NUM_2) {
			return CalcTBCD(OUT_CUBIC, time * NUM_2, begin, change / NUM_2, duration);
		}
		else {
			return CalcTBCD(IN_CUBIC, (time * NUM_2) - duration, begin + change / NUM_2, change / NUM_2, duration);
		}
	}

	//10
	float InQuart() {
		time = time / duration;
		return (change * powf(time, NUM_4) + begin);
	}

	//11
	float OutQuart() {
		time = time / duration - NUM_1;
		return (-change * (powf(time, NUM_4) - NUM_1) + begin);
	}

	//12
	float InOutQuart() {
		time = time / duration * NUM_2;
		if (time < NUM_1) {
			return (change / NUM_2 * powf(time, NUM_4) + begin);
		}
		else {
			time -= NUM_2;
			return (-change / NUM_2 * (powf(time, NUM_4) - NUM_2) + begin);
		}
	}

	//13
	float OutInQuart() {
		if (time < duration / NUM_2) {
			return CalcTBCD(OUT_QUART, time * NUM_2, begin, change / NUM_2, duration);
		}
		else {
			return CalcTBCD(IN_QUART, (time * NUM_2) - duration, begin + change / NUM_2, change / NUM_2, duration);
		}
	}

	//14
	float InQuint() {
		time = time / duration;
		return (change * powf(time, NUM_5) + begin);
	}

	//15
	float OutQuint() {
		time = time / duration - NUM_1;
		return (change * (powf(time, NUM_5) + NUM_1) + begin);
	}

	//16
	float InOutQuint() {
		time = time / duration * NUM_2;
		if (time < NUM_1) {
			return (change / NUM_2 * powf(time, NUM_5) + begin);
		}
		else {
			time = time - NUM_2;
			return (change / NUM_2 * (powf(time, NUM_5) + NUM_2) + begin);
		}
	}

	//17
	float OutInQuint() {
		if (time < duration / NUM_2) {
			return CalcTBCD(OUT_QUINT, time * NUM_2, begin, change / NUM_2, duration);
		}
		else {
			return CalcTBCD(IN_QUINT, (time * NUM_2) - duration, begin + change / NUM_2, change / NUM_2, duration);
		}
	}

	//18
	float InSine() {
		return (-change * cosf(time / duration * (pi / NUM_2)) + change + begin);
	}

	//19
	float OutSine() {
		return (change * sinf(time / duration * (pi / NUM_2)) + begin);
	}
	
	//20
	float InOutSine() {
		return (-change / NUM_2 * (cosf(pi * time / duration) - NUM_1) + begin);
	}

	//21
	float OutInSine() {
		if (time < duration / NUM_2) {
			return CalcTBCD(OUT_SINE, time * NUM_2, begin, change / NUM_2, duration);
		}
		else {
			return CalcTBCD(IN_SINE, (time * NUM_2) - duration, begin + change / NUM_2, change / NUM_2, duration);
		}
	}

	//22
	float InExpo() {
		if (time == NUM_0) {
			return (begin);
		}
		else {
			return (change * powf(NUM_2, NUM_10 * (time / duration - NUM_1)) + begin - change * NUM_p001);
		}
	}

	//23
	float OutExpo() {
		if (time == duration) {
			return (begin + change);
		}
		else {
			return (change * (NUM_1 + NUM_p001) * (-powf(NUM_2, -NUM_10 * time / duration) + NUM_1) + begin);
		}
	}

	//24
	float InOutExpo() {
		if (time == NUM_0) { return (begin); }
		if (time == duration) { return (begin + change); }
		time = time / duration * NUM_2;
		if (time < NUM_1) {
			return (change / NUM_2 * powf(NUM_2, NUM_10 * (time - NUM_1)) + begin - change * NUM_p0005);
		}
		else {
			time = time - NUM_1;
			return (change / NUM_2 * (NUM_1 + NUM_p0005) * (-powf(NUM_2, -NUM_10 * time) + NUM_2) + begin);
		}
	}

	//25
	float OutInExpo() {
		if (time < duration / NUM_2) {
			return CalcTBCD(OUT_EXPO, time * NUM_2, begin, change / NUM_2, duration);
		}
		else {
			return CalcTBCD(IN_EXPO, (time * NUM_2) - duration, begin + change / NUM_2, change / NUM_2, duration);
		}
	}

	//26
	float InCirc() {
		time = time / duration;
		return (-change * (sqrtf(NUM_1 - powf(time, NUM_2)) - NUM_1) + begin);
	}

	//27
	float OutCirc() {
		time = time / duration - NUM_1;
		return (change * sqrtf(NUM_1 - powf(time, NUM_2)) + begin);
	}

	//28
	float InOutCirc() {
		time = time / duration * NUM_2;
		if (time < NUM_1) {
			return (-change / NUM_2 * (sqrtf(NUM_1 - time * time) - NUM_1) + begin);
		}
		else {
			time = time - NUM_2;
			return (change / NUM_2 * (sqrtf(NUM_1 - time * time) + NUM_1) + begin);
		}
	}

	//29
	float OutInCirc() {
		if (time < duration / NUM_2) {
			return CalcTBCD(OUT_CIRC, time * NUM_2, begin, change / NUM_2, duration);
		}
		else {
			return CalcTBCD(IN_CIRC, (time * NUM_2) - duration, begin + change / NUM_2, change / NUM_2, duration);
		}
	}

	//30
	float InElastic() {
		if (time == NUM_0) return begin;
		time = time / duration;
		if (time == NUM_1) return (begin + change);
		float period = duration * NUM_p3;
		float shift;
		float amplitude = NUM_0;
		if (amplitude < abs(change)) {
			amplitude = change;
			shift = period / NUM_4;
		}
		else {
			shift = period / (NUM_2 * pi) * asinf(change / amplitude);
		}

		time--;

		return (-(amplitude * powf(NUM_2, NUM_10 * time) * sinf((time * duration - shift) * (NUM_2 * pi) / period)) + begin);
	}
	
	//31
	float OutElastic() {
		if (time == NUM_0) return begin;
		time = time / duration;
		if (time == NUM_1) return (begin + change);
		float period = duration * NUM_p3;
		float shift;
		float amplitude = NUM_0;
		if (amplitude < abs(change)) {
			amplitude = change;
			shift = period / NUM_4;
		}
		else {
			shift = period / (NUM_2 * pi) * asinf(change / amplitude);
		}
		return (amplitude * powf(NUM_2, -NUM_10 * time) * sinf((time * duration - shift) * (NUM_2 * pi) / period) + change + begin);
	}

	//32
	float InOutElastic() {
		if (time == NUM_0) return begin;

		time = time / duration * NUM_2;

		if (time == NUM_2) return (begin + change);

		float period = duration * (NUM_p3 * NUM_1p5);
		float amplitude = NUM_0;
		float shift;
		if (!amplitude || amplitude < abs(change)) {
			amplitude = change;
			shift = period / NUM_4;
		}
		else {
			shift = period / (NUM_2 * pi) * asinf(change / amplitude);
		}
		if (time < NUM_1) {
			time = time - NUM_1;
			return (-NUM_p5 * (amplitude * powf(NUM_2, NUM_10 * time) * sinf((time * duration - shift) * (NUM_2 * pi) / period)) + begin);
		}
		else {
			time = time - NUM_1;
			return (amplitude * powf(NUM_2, -NUM_10 * time) * sinf((time * duration - shift) * (NUM_2 * pi) / period) * NUM_p5 + change + begin);
		}
		 
	}

	//33
	float OutInElastic() {
		if (time < duration / NUM_2) {
			return CalcTBCD(OUT_ELASTIC, time * NUM_2, begin, change / NUM_2, duration);
		}
		else {
			return CalcTBCD(IN_ELASTIC, (time * NUM_2) - duration, begin + change / NUM_2, change / NUM_2, duration);
		}
	}

	//34
	static const float BACK_SHIFT = 1.70158f;
	float InBack() {
		time = time / duration;
		return (change * time * time * ((BACK_SHIFT + NUM_1) * time - BACK_SHIFT) + begin);
	}
	
	//35
	float OutBack() {
		time = time / duration - NUM_1;
		return (change * (time * time * ((BACK_SHIFT + NUM_1) * time + BACK_SHIFT) + NUM_1) + begin);
	}

	//36
	static const float IN_OUT_BACK_SHIFT = BACK_SHIFT * 1.525f;
	float InOutBack() {
		time = time / duration * NUM_2;
		if (time < NUM_1) {
			return (change / NUM_2 * (time * time * ((IN_OUT_BACK_SHIFT + NUM_1) * time - IN_OUT_BACK_SHIFT)) + begin);
		}
		else {
			time -= NUM_2;
			return (change / NUM_2 * (time * time * ((IN_OUT_BACK_SHIFT + NUM_1) * time + IN_OUT_BACK_SHIFT) + NUM_2) + begin);
		}
	}

	//37
	float OutInBack() {
		if (time < duration / NUM_2) {
			return CalcTBCD(OUT_BACK, time * NUM_2, begin, change / NUM_2, duration);
		}
		else {
			return CalcTBCD(IN_BACK, (time * NUM_2) - duration, begin + change / NUM_2, change / NUM_2, duration);
		}
	}

	//38
	float InBounce() {
		return (change - CalcTBCD(OUT_BOUNCE, duration - time, NUM_0, change, duration) + begin);
	}

	//39
	//2.5, 2.25, 2.625, 0.9375, 0.984375は一度しか使わない...が、可読性が終わる →可読性を説くならhalfとかmul等関数も導入するべきではないか
	//機能自体はTWEENERの移植になる都合上そもそも原来が数値指定であるため難しいところ
	//一旦全ての数値を排除した書き方をする
	float OutBounce() {
		time = time / duration;
		if (time < NUM_1 / NUM_2p75) {
			return (change * (NUM_7p5625 * time * time) + begin);
		}
		else {
			if (time < NUM_2 / NUM_2p75) {
				time = time - (NUM_1p5 / NUM_2p75);
				return (change * (NUM_7p5625 * time * time + NUM_p75) + begin);
			}
			else {
				if (time < (NUM_2p5) / NUM_2p75) {
					time = time - (NUM_2p25 / NUM_2p75);
					return (change * (NUM_7p5625 * time * time + NUM_p9375) + begin);
				}
				else {
					time = time - ((NUM_2 + NUM_p625) / NUM_2p75);
					return (change * (NUM_7p5625 * time * time + NUM_p984375) + begin);
				}
			}
		}
	}

	//40
	float InOutBounce() {
		if (time < duration / NUM_2) {
			return (CalcTBCD(IN_BOUNCE, time * NUM_2, NUM_0, change, duration) * NUM_p5 + begin);
		}
		else {
			return (CalcTBCD(OUT_BOUNCE, time * NUM_2 - duration, NUM_0, change, duration) * NUM_p5 + change * NUM_p5 + begin);
		}
	}
	
	//41
	float OutInBounce() {
		if (time < duration / NUM_2) {
			return CalcTBCD(OUT_BOUNCE, time * NUM_2, begin, change / NUM_2, duration);
		}
		else {
			return CalcTBCD(IN_BOUNCE, (time * NUM_2) - duration, begin + change / NUM_2, change / NUM_2, duration) + change;
		}
	}



	float Calc(int _easeNum, float _nowTime, float _endTime, float _begin, float _end) {
		if (_easeNum > NUM_0 && _easeNum < MAX) {
			return Calc(static_cast<Ease>(_easeNum), _nowTime, _endTime, _begin, _end);
		}
		else {
			return Calc(LINEAR, _nowTime, _endTime, _begin, _end);
		}
	}
	float Calc(Ease e, float _nowTime, float _endTime, float _begin, float _end)
	{
		time = _nowTime;
		duration = _endTime;
		begin = _begin;
		change = _end - _begin;

		switch (e)
		{
		case Ease::LINEAR:		return Linear();
		case Ease::IN_QUAD:		return InQuad();
		case Ease::OUT_QUAD:		return OutQuad();
		case Ease::IN_OUT_QUAD:	return InOutQuad();
		case Ease::OUT_IN_QUAD:	return OutInQuad();
		case Ease::IN_CUBIC:		return InCubic();
		case Ease::OUT_CUBIC:		return OutCubic();
		case Ease::IN_OUT_CUBIC:	return InOutCubic();
		case Ease::OUT_IN_CUBIC:	return OutInCubic();
		case Ease::IN_QUART:		return InQuart();
		case Ease::OUT_QUART:		return OutQuart();
		case Ease::IN_OUT_QUART:	return InOutQuart();
		case Ease::OUT_IN_QUART:	return OutInQuart();
		case Ease::IN_QUINT:		return InQuint();
		case Ease::OUT_QUINT:		return OutQuint();
		case Ease::IN_OUT_QUINT:	return InOutQuint();
		case Ease::OUT_IN_QUINT:	return OutInQuint();
		case Ease::IN_SINE:		return InSine();
		case Ease::OUT_SINE:		return OutSine();
		case Ease::IN_OUT_SINE:	return InOutSine();
		case Ease::OUT_IN_SINE:	return OutInSine();
		case Ease::IN_EXPO:		return InExpo();
		case Ease::OUT_EXPO:		return OutExpo();
		case Ease::IN_OUT_EXPO:	return InOutExpo();
		case Ease::OUT_IN_EXPO:	return OutInExpo();
		case Ease::IN_CIRC:		return InCirc();
		case Ease::OUT_CIRC:		return OutCirc();
		case Ease::IN_OUT_CIRC:	return InOutCirc();
		case Ease::OUT_IN_CIRC:	return OutInCirc();
		case Ease::IN_ELASTIC:	return InElastic();
		case Ease::OUT_ELASTIC:	return OutElastic();
		case Ease::IN_OUT_ELASTIC:return InOutElastic();
		case Ease::OUT_IN_ELASTIC:return OutInElastic();
		case Ease::IN_BACK:		return InBack();
		case Ease::OUT_BACK:		return OutBack();
		case Ease::IN_OUT_BACK:	return InOutBack();
		case Ease::OUT_IN_BACK:	return OutInBack();
		case Ease::IN_BOUNCE:		return InBounce();
		case Ease::OUT_BOUNCE:	return OutBounce();
		case Ease::IN_OUT_BOUNCE:	return InOutBounce();
		case Ease::OUT_IN_BOUNCE:	return OutInBounce();
		}
		return Linear();
	}

}
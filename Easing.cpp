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
		return change * powf(time, 2) + begin;
	}

	//3
	float OutQuad() {
		time /= duration;
		return -change * time * (time - 2) + begin;
	}

	//4
	float InOutQuad() {
		time = time / duration * 2;
		if (time < 1) {
			return(change / 2 * powf(time, 2) + begin);
		}
		else {
			return(-change / 2 * ((time - 1) * (time - 3) - 1) + begin);
		}
	}

	//5
	float OutInQuad() {
		if (time < duration / 2) {
			return CalcTBCD(OUT_QUAD, time * 2, begin, change / 2, duration);
		}
		else {
			return CalcTBCD(IN_QUAD, (time * 2) - duration, begin + change / 2, change / 2, duration);
		}
	}

	//6
	float InCubic() {
		time = time / duration;
		return (change * powf(time, 3) + begin);
	}

	//7
	float OutCubic() {
		time = time / duration - 1;
		return (change * (powf(time, 3) + 1) + begin);
	}

	//8
	float InOutCubic() {
		time = time / duration * 2;
		if (time < 1) {
			return (change / 2 * time * time * time + begin);
		}
		else {
			time = time - 2;
			return (change / 2 * (time * time * time + 2) + begin);
		}
	}

	//9
	float OutInCubic() {
		if (time < duration / 2) {
			return CalcTBCD(OUT_CUBIC, time * 2, begin, change / 2, duration);
		}
		else {
			return CalcTBCD(IN_CUBIC, (time * 2) - duration, begin + change / 2, change / 2, duration);
		}
	}

	//10
	float InQuart() {
		time = time / duration;
		return (change * powf(time, 4) + begin);
	}

	//11
	float OutQuart() {
		time = time / duration - 1;
		return (-change * (powf(time, 4) - 1) + begin);
	}

	//12
	float InOutQuart() {
		time = time / duration * 2;
		if (time < 1) {
			return (change / 2 * powf(time, 4) + begin);
		}
		else {
			time = time - 2;
			return (-change / 2 * (powf(time, 4) - 2) + begin);
		}
	}

	//13
	float OutInQuart() {
		if (time < duration / 2) {
			return CalcTBCD(OUT_QUART, time * 2, begin, change / 2, duration);
		}
		else {
			return CalcTBCD(IN_QUART, (time * 2) - duration, begin + change / 2, change / 2, duration);
		}
	}

	//14
	float InQuint() {
		time = time / duration;
		return (change * powf(time, 5) + begin);
	}

	//15
	float OutQuint() {
		time = time / duration - 1;
		return (change * (powf(time, 5) + 1) + begin);
	}

	//16
	float InOutQuint() {
		time = time / duration * 2;
		if (time < 1) {
			return (change / 2 * powf(time, 5) + begin);
		}
		else {
			time = time - 2;
			return (change / 2 * (powf(time, 5) + 2) + begin);
		}
	}

	//17
	float OutInQuint() {
		if (time < duration / 2) {
			return CalcTBCD(OUT_QUINT, time * 2, begin, change / 2, duration);
		}
		else {
			return CalcTBCD(IN_QUINT, (time * 2) - duration, begin + change / 2, change / 2, duration);
		}
	}

	//18
	float InSine() {
		return (-change * cosf(time / duration * (pi / 2)) + change + begin);
	}

	//19
	float OutSine() {
		return (change * sinf(time / duration * (pi / 2)) + begin);
	}
	
	//20
	float InOutSine() {
		return (-change / 2 * (cosf(pi * time / duration) - 1) + begin);
	}

	//21
	float OutInSine() {
		if (time < duration / 2) {
			return CalcTBCD(OUT_SINE, time * 2, begin, change / 2, duration);
		}
		else {
			return CalcTBCD(IN_SINE, (time * 2) - duration, begin + change / 2, change / 2, duration);
		}
	}

	//22
	float InExpo() {
		if (time == 0) {
			return (begin);
		}
		else {
			return (change * powf(2, 10 * (time / duration - 1)) + begin - change * 0.001f);
		}
	}

	//23
	float OutExpo() {
		if (time == duration) {
			return (begin + change);
		}
		else {
			return (change * 1.001f * (-powf(2, -10 * time / duration) + 1) + begin);
		}
	}

	//24
	float InOutExpo() {
		if (time == 0) { return (begin); }
		if (time == duration) { return (begin + change); }
		time = time / duration * 2;
		if (time < 1) {
			return (change / 2 * powf(2, 10 * (time - 1)) + begin - change * 0.0005f);
		}
		else {
			time = time - 1;
			return (change / 2 * 1.0005f * (-powf(2, -10 * time) + 2) + begin);
		}
	}

	//25
	float OutInExpo() {
		if (time < duration / 2) {
			return CalcTBCD(OUT_EXPO, time * 2, begin, change / 2, duration);
		}
		else {
			return CalcTBCD(IN_EXPO, (time * 2) - duration, begin + change / 2, change / 2, duration);
		}
	}

	//26
	float InCirc() {
		time = time / duration;
		return (-change * (sqrtf(1 - powf(time, 2)) - 1) + begin);
	}

	//27
	float OutCirc() {
		time = time / duration - 1;
		return (change * sqrtf(1 - powf(time, 2)) + begin);
	}

	//28
	float InOutCirc() {
		time = time / duration * 2;
		if (time < 1) {
			return (-change / 2 * (sqrtf(1 - time * time) - 1) + begin);
		}
		else {
			time = time - 2;
			return (change / 2 * (sqrtf(1 - time * time) + 1) + begin);
		}
	}

	//29
	float OutInCirc() {
		if (time < duration / 2) {
			return CalcTBCD(OUT_CIRC, time * 2, begin, change / 2, duration);
		}
		else {
			return CalcTBCD(IN_CIRC, (time * 2) - duration, begin + change / 2, change / 2, duration);
		}
	}

	//30
	float InElastic() {
		if (time == 0) return begin;
		time = time / duration;
		if (time == 1) return (begin + change);
		float period = duration * 0.3f;
		float shift;
		float amplitude = 0;
		if (amplitude < abs(change)) {
			amplitude = change;
			shift = period / 4;
		}
		else {
			shift = period / (2 * pi) * asinf(change / amplitude);
		}

		time--;

		return (-(amplitude * powf(2, 10 * time) * sinf((time * duration - shift) * (2 * pi) / period)) + begin);
	}
	
	//31
	float OutElastic() {
		if (time == 0) return begin;
		time = time / duration;
		if (time == 1) return (begin + change);
		float period = duration * 0.3f;
		float shift;
		float amplitude = 0;
		if (amplitude < abs(change)) {
			amplitude = change;
			shift = period / 4;
		}
		else {
			shift = period / (2 * pi) * asinf(change / amplitude);
		}
		return (amplitude * powf(2, -10 * time) * sinf((time * duration - shift) * (2 * pi) / period) + change + begin);
	}

	//32
	float InOutElastic() {
		if (time == 0) return begin;

		time = time / duration * 2;

		if (time == 2) return (begin + change);

		float period = duration * (0.3f * 1.5f);
		float amplitude = 0;
		float shift;
		if (!amplitude || amplitude < abs(change)) {
			amplitude = change;
			shift = period / 4;
		}
		else {
			shift = period / (2 * pi) * asinf(change / amplitude);
		}
		if (time < 1) {
			time = time - 1;
			return (-0.5f * (amplitude * powf(2, 10 * time) * sinf((time * duration - shift) * (2 * pi) / period)) + begin);
		}
		else {
			time = time - 1;
			return (amplitude * powf(2, -10 * time) * sinf((time * duration - shift) * (2 * pi) / period) * 0.5f + change + begin);
		}

	}

	//33
	float OutInElastic() {
		if (time < duration / 2) {
			return CalcTBCD(OUT_ELASTIC, time * 2, begin, change / 2, duration);
		}
		else {
			return CalcTBCD(IN_ELASTIC, (time * 2) - duration, begin + change / 2, change / 2, duration);
		}
	}

	//34
	float InBack() {
		float shift = 1.70158f;
		time = time / duration;
		return (change * time * time * ((shift + 1) * time - shift) + begin);
	}
	
	//35
	float OutBack() {
		float shift = 1.70158f;
		time = time / duration - 1;
		return (change * (time * time * ((shift + 1) * time + shift) + 1) + begin);
	}

	//36
	float InOutBack() {
		float shift = 1.70158f;
		shift = shift * 1.525f;

		time = time / duration * 2;
		if (time < 1) {
			return (change / 2 * (time * time * ((shift + 1) * time - shift)) + begin);
		}
		else {
			time = time - 2;
			return (change / 2 * (time * time * ((shift + 1) * time + shift) + 2) + begin);
		}
	}

	//37
	float OutInBack() {
		if (time < duration / 2) {
			return CalcTBCD(OUT_BACK, time * 2, begin, change / 2, duration);
		}
		else {
			return CalcTBCD(IN_BACK, (time * 2) - duration, begin + change / 2, change / 2, duration);
		}
	}

	//38
	float InBounce() {
		return (change - CalcTBCD(OUT_BOUNCE, duration - time, 0, change, duration) + begin);
	}

	//39
	float OutBounce() {
		time = time / duration;
		if (time < 1 / 2.75f) {
			return (change * (7.5625f * time * time) + begin);
		}
		else {
			if (time < 2 / 2.75f) {
				time = time - (1.5f / 2.75f);
				return (change * (7.5625f * time * time + 0.75f) + begin);
			}
			else {
				if (time < 2.5f / 2.75f) {
					time = time - (2.25f / 2.75f);
					return (change * (7.5625f * time * time + 0.9375f) + begin);
				}
				else {
					time = time - (2.625f / 2.75f);
					return (change * (7.5625f * time * time + 0.984375f) + begin);
				}
			}
		}
	}

	//40
	float InOutBounce() {
		if (time < duration / 2) {
			return (CalcTBCD(IN_BOUNCE, time * 2, 0, change, duration) * 0.5f + begin);
		}
		else {
			return (CalcTBCD(OUT_BOUNCE, time * 2 - duration, 0, change, duration) * 0.5f + change * 0.5f + begin);
		}
	}
	
	//41
	float OutInBounce() {
		if (time < duration / 2) {
			return CalcTBCD(OUT_BOUNCE, time * 2, begin, change / 2, duration);
		}
		else {
			return CalcTBCD(IN_BOUNCE, (time * 2) - duration, begin + change / 2, change / 2, duration) + change;
		}
	}



	float Calc(int _easeNum, float _nowTime, float _endTime, float _begin, float _end) {
		if (_easeNum > 0 && _easeNum < MAX) {
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
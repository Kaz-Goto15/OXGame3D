#include "Easing.h"
#define _USE_MATH_DEFINES
#include <cmath>

using std::pow;
using std::sin;
using std::cos;
using std::sqrt;
using std::abs;
using std::asin;


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
		return change * pow(time, 2) + begin;
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
			return(change / 2 * pow(time, 2) + begin);
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
		return (change * pow(time, 3) + begin);
	}

	//7
	float OutCubic() {
		time = time / duration - 1;
		return (change * (pow(time, 3) + 1) + begin);
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
		return (change * pow(time, 4) + begin);
	}

	//11
	float OutQuart() {
		time = time / duration - 1;
		return (-change * (pow(time, 4) - 1) + begin);
	}

	//12
	float InOutQuart() {
		time = time / duration * 2;
		if (time < 1) {
			return (change / 2 * pow(time, 4) + begin);
		}
		else {
			time = time - 2;
			return (-change / 2 * (pow(time, 4) - 2) + begin);
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
		return (change * pow(time, 5) + begin);
	}

	//15
	float OutQuint() {
		time = time / duration - 1;
		return (change * (pow(time, 5) + 1) + begin);
	}

	//16
	float InOutQuint() {
		time = time / duration * 2;
		if (time < 1) {
			return (change / 2 * pow(time, 5) + begin);
		}
		else {
			time = time - 2;
			return (change / 2 * (pow(time, 5) + 2) + begin);
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
		return (-change * cos(time / duration * (M_PI / 2)) + change + begin);
	}

	//19
	float OutSine() {
		return (change * sin(time / duration * (M_PI / 2)) + begin);
	}
	
	//20
	float InOutSine() {
		return (-change / 2 * (cos(M_PI * time / duration) - 1) + begin);
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
			return (change * pow(2, 10 * (time / duration - 1)) + begin - change * 0.001);
		}
	}

	//23
	float OutExpo() {
		if (time == duration) {
			return (begin + change);
		}
		else {
			return (change * 1.001 * (-pow(2, -10 * time / duration) + 1) + begin);
		}
	}

	//24
	float InOutExpo() {
		if (time == 0) { return (begin); }
		if (time == duration) { return (begin + change); }
		time = time / duration * 2;
		if (time < 1) {
			return (change / 2 * pow(2, 10 * (time - 1)) + begin - change * 0.0005);
		}
		else {
			time = time - 1;
			return (change / 2 * 1.0005 * (-pow(2, -10 * time) + 2) + begin);
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
		return (-change * (sqrt(1 - pow(time, 2)) - 1) + begin);
	}

	//27
	float OutCirc() {
		time = time / duration - 1;
		return (change * sqrt(1 - pow(time, 2)) + begin);
	}

	//28
	float InOutCirc() {
		time = time / duration * 2;
		if (time < 1) {
			return (-change / 2 * (sqrt(1 - time * time) - 1) + begin);
		}
		else {
			time = time - 2;
			return (change / 2 * (sqrt(1 - time * time) + 1) + begin);
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
		float p = duration * 0.3;
		float s;
		float a = 0;
			if (!a || a < abs(change)) {
				a = change;
				s = p / 4;
			}
			else {
				s = p / (2 * M_PI) * asin(change / a);
			}

			time--;

		return (-(a * pow(2, 10 * time) * sin((time * duration - s) * (2 * M_PI) / p)) + begin);
	}
	
	//31
	float OutElastic() {
		return 0;
	}
	float InOutElastic() {
		return 0;
	}
	float OutInElastic() {
		return 0;
	}
	float InBack() {
		return 0;
	}
	float OutBack() {
		return 0;
	}
	float InOutBack() {
		return 0;
	}
	float OutInBack() {
		return 0;
	}
	float InBounce() {
		return 0;
	}
	float OutBounce() {
		time = time / duration;
		if (time < 1 / 2.75) {
			return (change * (7.5625 * time * time) + begin);
		}
		else {
			if (time < 2 / 2.75) {
				time = time - (1.5 / 2.75);
				return (change * (7.5625 * time * time + 0.75) + begin);
			}
			else {
				if (time < 2.5 / 2.75) {
					time = time - (2.25 / 2.75);
					return (change * (7.5625 * time * time + 0.9375) + begin);
				}
				else {
					time = time - (2.625 / 2.75);
					return (change * (7.5625 * time * time + 0.984375) + begin);
				}
			}
		}
	}

	float InOutBounce() {
		if (time < duration / 2) {
			return (CalcTBCD(IN_BOUNCE, time * 2, 0, change, duration) * 0.5 + begin);
		}
		else {
			return (CalcTBCD(OUT_BOUNCE, time * 2 - duration, 0, change, duration) * 0.5 + change * 0.5 + begin);
		}
	}
	
	float OutInBounce() {
		if (time < duration / 2) {
			return CalcTBCD(OUT_BOUNCE, time * 2, begin, change / 2, duration);
		}
		else {
			return CalcTBCD(IN_BOUNCE, (time * 2) - duration, begin + change / 2, change / 2, duration);
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
		case Easing::LINEAR:		return Linear();
		case Easing::IN_QUAD:		return InQuad();
		case Easing::OUT_QUAD:		return OutQuad();
		case Easing::IN_OUT_QUAD:	return InOutQuad();
		case Easing::OUT_IN_QUAD:	return OutInQuad();
		case Easing::IN_CUBIC:		return InCubic();
		case Easing::OUT_CUBIC:		return OutCubic();
		case Easing::IN_OUT_CUBIC:	return InOutCubic();
		case Easing::OUT_IN_CUBIC:	return OutInCubic();
		case Easing::IN_QUART:		return InQuart();
		case Easing::OUT_QUART:		return OutQuart();
		case Easing::IN_OUT_QUART:	return InOutQuart();
		case Easing::OUT_IN_QUART:	return OutInQuart();
		case Easing::IN_QUINT:		return InQuint();
		case Easing::OUT_QUINT:		return OutQuint();
		case Easing::IN_OUT_QUINT:	return InOutQuint();
		case Easing::OUT_IN_QUINT:	return OutInQuint();
		case Easing::IN_SINE:		return InSine();
		case Easing::OUT_SINE:		return OutSine();
		case Easing::IN_OUT_SINE:	return InOutSine();
		case Easing::OUT_IN_SINE:	return OutInSine();
		case Easing::IN_EXPO:		return InExpo();
		case Easing::OUT_EXPO:		return OutExpo();
		case Easing::IN_OUT_EXPO:	return InOutExpo();
		case Easing::OUT_IN_EXPO:	return OutInExpo();
		case Easing::IN_CIRC:		return InCirc();
		case Easing::OUT_CIRC:		return OutCirc();
		case Easing::IN_OUT_CIRC:	return InOutCirc();
		case Easing::OUT_IN_CIRC:	return OutInCirc();
		case Easing::IN_ELASTIC:	return InElastic();
		case Easing::OUT_ELASTIC:	return OutElastic();
		case Easing::IN_OUT_ELASTIC:return InOutElastic();
		case Easing::OUT_IN_ELASTIC:return OutInElastic();
		case Easing::IN_BACK:		return InBack();
		case Easing::OUT_BACK:		return OutBack();
		case Easing::IN_OUT_BACK:	return InOutBack();
		case Easing::OUT_IN_BACK:	return OutInBack();
		case Easing::IN_BOUNCE:		return InBounce();
		case Easing::OUT_BOUNCE:	return OutBounce();
		case Easing::IN_OUT_BOUNCE:	return InOutBounce();
		case Easing::OUT_IN_BOUNCE:	return OutInBounce();
		}
		return Linear();
	}

}

/*

-- For all easing functions:
-- t = elapsed time
-- b = begin
-- c = change == ending - beginning
-- d = duration (total time)

local pow = math.pow
local sin = math.sin
local cos = math.cos
local pi = math.pi
local sqrt = math.sqrt
local abs = math.abs
local asin  = math.asin

local function linear(t, b, c, d)
  return c * t / d + b
  0.5,10,20,1
  return 20*0.5/1 + 10;
end

local function inQuad(t, b, c, d)
  t = t / d
  return c * pow(t, 2) + b
end

local function outQuad(t, b, c, d)
  t = t / d
  return -c * t * (t - 2) + b
end

local function inOutQuad(t, b, c, d)
  t = t / d * 2
  if t < 1 then
	return c / 2 * pow(t, 2) + b
  else
	return -c / 2 * ((t - 1) * (t - 3) - 1) + b
  end
end

local function outInQuad(t, b, c, d)
  if t < d / 2 then
	return outQuad (t * 2, b, c / 2, d)
  else
	return inQuad((t * 2) - d, b + c / 2, c / 2, d)
  end
end

local function inCubic (t, b, c, d)
  t = t / d
  return c * pow(t, 3) + b
end

local function outCubic(t, b, c, d)
  t = t / d - 1
  return c * (pow(t, 3) + 1) + b
end

local function inOutCubic(t, b, c, d)
  t = t / d * 2
  if t < 1 then
	return c / 2 * t * t * t + b
  else
	t = t - 2
	return c / 2 * (t * t * t + 2) + b
  end
end

local function outInCubic(t, b, c, d)
  if t < d / 2 then
	return outCubic(t * 2, b, c / 2, d)
  else
	return inCubic((t * 2) - d, b + c / 2, c / 2, d)
  end
end

local function inQuart(t, b, c, d)
  t = t / d
  return c * pow(t, 4) + b
end

local function outQuart(t, b, c, d)
  t = t / d - 1
  return -c * (pow(t, 4) - 1) + b
end

local function inOutQuart(t, b, c, d)
  t = t / d * 2
  if t < 1 then
	return c / 2 * pow(t, 4) + b
  else
	t = t - 2
	return -c / 2 * (pow(t, 4) - 2) + b
  end
end

local function outInQuart(t, b, c, d)
  if t < d / 2 then
	return outQuart(t * 2, b, c / 2, d)
  else
	return inQuart((t * 2) - d, b + c / 2, c / 2, d)
  end
end

local function inQuint(t, b, c, d)
  t = t / d
  return c * pow(t, 5) + b
end

local function outQuint(t, b, c, d)
  t = t / d - 1
  return c * (pow(t, 5) + 1) + b
end

local function inOutQuint(t, b, c, d)
  t = t / d * 2
  if t < 1 then
	return c / 2 * pow(t, 5) + b
  else
	t = t - 2
	return c / 2 * (pow(t, 5) + 2) + b
  end
end

local function outInQuint(t, b, c, d)
  if t < d / 2 then
	return outQuint(t * 2, b, c / 2, d)
  else
	return inQuint((t * 2) - d, b + c / 2, c / 2, d)
  end
end

local function inSine(t, b, c, d)
  return -c * cos(t / d * (pi / 2)) + c + b
end

local function outSine(t, b, c, d)
  return c * sin(t / d * (pi / 2)) + b
end

local function inOutSine(t, b, c, d)
  return -c / 2 * (cos(pi * t / d) - 1) + b
end

local function outInSine(t, b, c, d)
  if t < d / 2 then
	return outSine(t * 2, b, c / 2, d)
  else
	return inSine((t * 2) -d, b + c / 2, c / 2, d)
  end
end

local function inExpo(t, b, c, d)
  if t == 0 then
	return b
  else
	return c * pow(2, 10 * (t / d - 1)) + b - c * 0.001
  end
end

local function outExpo(t, b, c, d)
  if t == d then
	return b + c
  else
	return c * 1.001 * (-pow(2, -10 * t / d) + 1) + b
  end
end

local function inOutExpo(t, b, c, d)
  if t == 0 then return b end
  if t == d then return b + c end
  t = t / d * 2
  if t < 1 then
	return c / 2 * pow(2, 10 * (t - 1)) + b - c * 0.0005
  else
	t = t - 1
	return c / 2 * 1.0005 * (-pow(2, -10 * t) + 2) + b
  end
end

local function outInExpo(t, b, c, d)
  if t < d / 2 then
	return outExpo(t * 2, b, c / 2, d)
  else
	return inExpo((t * 2) - d, b + c / 2, c / 2, d)
  end
end

local function inCirc(t, b, c, d)
  t = t / d
  return(-c * (sqrt(1 - pow(t, 2)) - 1) + b)
end

local function outCirc(t, b, c, d)
  t = t / d - 1
  return(c * sqrt(1 - pow(t, 2)) + b)
end

local function inOutCirc(t, b, c, d)
  t = t / d * 2
  if t < 1 then
	return -c / 2 * (sqrt(1 - t * t) - 1) + b
  else
	t = t - 2
	return c / 2 * (sqrt(1 - t * t) + 1) + b
  end
end

local function outInCirc(t, b, c, d)
  if t < d / 2 then
	return outCirc(t * 2, b, c / 2, d)
  else
	return inCirc((t * 2) - d, b + c / 2, c / 2, d)
  end
end

local function inElastic(t, b, c, d, a, p)
  if t == 0 then return b end

  t = t / d

  if t == 1  then return b + c end

  if not p then p = d * 0.3 end

  local s

  if not a or a < abs(c) then
	a = c
	s = p / 4
  else
	s = p / (2 * pi) * asin(c/a)
  end

  t = t - 1

  return -(a * pow(2, 10 * t) * sin((t * d - s) * (2 * pi) / p)) + b
end

-- a: amplitud
-- p: period
local function outElastic(t, b, c, d, a, p)
  if t == 0 then return b end

  t = t / d

  if t == 1 then return b + c end

  if not p then p = d * 0.3 end

  local s

  if not a or a < abs(c) then
	a = c
	s = p / 4
  else
	s = p / (2 * pi) * asin(c/a)
  end

  return a * pow(2, -10 * t) * sin((t * d - s) * (2 * pi) / p) + c + b
end

-- p = period
-- a = amplitud
local function inOutElastic(t, b, c, d, a, p)
  if t == 0 then return b end

  t = t / d * 2

  if t == 2 then return b + c end

  if not p then p = d * (0.3 * 1.5) end
  if not a then a = 0 end

  if not a or a < abs(c) then
	a = c
	s = p / 4
  else
	s = p / (2 * pi) * asin(c / a)
  end

  if t < 1 then
	t = t - 1
	return -0.5 * (a * pow(2, 10 * t) * sin((t * d - s) * (2 * pi) / p)) + b
  else
	t = t - 1
	return a * pow(2, -10 * t) * sin((t * d - s) * (2 * pi) / p ) * 0.5 + c + b
  end
end

-- a: amplitud
-- p: period
local function outInElastic(t, b, c, d, a, p)
  if t < d / 2 then
	return outElastic(t * 2, b, c / 2, d, a, p)
  else
	return inElastic((t * 2) - d, b + c / 2, c / 2, d, a, p)
  end
end

local function inBack(t, b, c, d, s)
  if not s then s = 1.70158 end
  t = t / d
  return c * t * t * ((s + 1) * t - s) + b
end

local function outBack(t, b, c, d, s)
  if not s then s = 1.70158 end
  t = t / d - 1
  return c * (t * t * ((s + 1) * t + s) + 1) + b
end

local function inOutBack(t, b, c, d, s)
  if not s then s = 1.70158 end
  s = s * 1.525
  t = t / d * 2
  if t < 1 then
	return c / 2 * (t * t * ((s + 1) * t - s)) + b
  else
	t = t - 2
	return c / 2 * (t * t * ((s + 1) * t + s) + 2) + b
  end
end

local function outInBack(t, b, c, d, s)
  if t < d / 2 then
	return outBack(t * 2, b, c / 2, d, s)
  else
	return inBack((t * 2) - d, b + c / 2, c / 2, d, s)
  end
end

local function outBounce(t, b, c, d)
  t = t / d
  if t < 1 / 2.75 then
	return c * (7.5625 * t * t) + b
  elseif t < 2 / 2.75 then
	t = t - (1.5 / 2.75)
	return c * (7.5625 * t * t + 0.75) + b
  elseif t < 2.5 / 2.75 then
	t = t - (2.25 / 2.75)
	return c * (7.5625 * t * t + 0.9375) + b
  else
	t = t - (2.625 / 2.75)
	return c * (7.5625 * t * t + 0.984375) + b
  end
end

local function inBounce(t, b, c, d)
  return c - outBounce(d - t, 0, c, d) + b
end

local function inOutBounce(t, b, c, d)
  if t < d / 2 then
	return inBounce(t * 2, 0, c, d) * 0.5 + b
  else
	return outBounce(t * 2 - d, 0, c, d) * 0.5 + c * .5 + b
  end
end

local function outInBounce(t, b, c, d)
  if t < d / 2 then
	return outBounce(t * 2, b, c / 2, d)
  else
	return inBounce((t * 2) - d, b + c / 2, c / 2, d)
  end
end

*/


/*
floatime outQuad(){
  time = time / duration;
  return ( -change * time * (time - 2) + begin );
}

floatime inOutQuad(){
  time = time / duration * 2;
  if( time < 1 ){
	return ( change / 2 * pow(time, 2) + begin );
  }else {
	return ( -change / 2 * ((time - 1) * (time - 3) - 1) + begin );
  }
}

floatime outInQuad(){
  if( time < duration / 2 ){
	return ( outQuad (time * 2, begin, change / 2, duration) );
  }else {
	return ( inQuad((time * 2) - duration, begin + change / 2, change / 2, duration) );
  }
}

floatime inCubic (){
  time = time / duration;
  return ( change * pow(time, 3) + begin );
}

floatime outCubic(){
  time = time / duration - 1;
  return ( change * (pow(time, 3) + 1) + begin );
}

floatime inOutCubic(){
  time = time / duration * 2;
  if( time < 1 ){
	return ( change / 2 * time * time * time + begin );
  }else {
	time = time - 2;
	return ( change / 2 * (time * time * time + 2) + begin );
  }
}

floatime outInCubic(){
  if( time < duration / 2 ){
	return ( outCubic(time * 2, begin, change / 2, duration) );
  }else {
	return ( inCubic((time * 2) - duration, begin + change / 2, change / 2, duration) );
  }
}

floatime inQuart(){
  time = time / duration;
  return ( change * pow(time, 4) + begin );
}

floatime outQuart(){
  time = time / duration - 1;
  return ( -change * (pow(time, 4) - 1) + begin );
}

floatime inOutQuart(){
  time = time / duration * 2;
  if( time < 1 ){
	return ( change / 2 * pow(time, 4) + begin );
  }else {
	time = time - 2;
	return ( -change / 2 * (pow(time, 4) - 2) + begin );
  }
}

floatime outInQuart(){
  if( time < duration / 2 ){
	return ( outQuart(time * 2, begin, change / 2, duration) );
  }else {
	return ( inQuart((time * 2) - duration, begin + change / 2, change / 2, duration) );
  }
}

floatime inQuint(){
  time = time / duration;
  return ( change * pow(time, 5) + begin );
}

floatime outQuint(){
  time = time / duration - 1;
  return ( change * (pow(time, 5) + 1) + begin );
}

floatime inOutQuint(){
  time = time / duration * 2;
  if( time < 1 ){
	return ( change / 2 * pow(time, 5) + begin );
  }else {
	time = time - 2;
	return ( change / 2 * (pow(time, 5) + 2) + begin );
  }
}

floatime outInQuint(){
  if( time < duration / 2 ){
	return ( outQuint(time * 2, begin, change / 2, duration) );
  }else {
	return ( inQuint((time * 2) - duration, begin + change / 2, change / 2, duration) );
  }
}

floatime inSine(){
  return ( -change * cos(time / duration * (M_PI / 2)) + change + begin );
}

floatime outSine(){
  return ( change * sin(time / duration * (M_PI / 2)) + begin );
}

floatime inOutSine(){
  return ( -change / 2 * (cos(M_PI * time / duration) - 1) + begin );
}

floatime outInSine(){
  if( time < duration / 2 ){
	return ( outSine(time * 2, begin, change / 2, duration) );
  }else {
	return ( inSine((time * 2) -duration, begin + change / 2, change / 2, duration) );
  }
}

floatime inExpo(){
  if( time == 0 ){
	return ( begin );
  }else {
	return ( change * pow(2, 10 * (time / duration - 1)) + begin - change * 0.001 );
  }
}

floatime outExpo(){
  if( time == duration ){
	return ( begin + change );
  }else {
	return ( change * 1.001 * (-pow(2, -10 * time / duration) + 1) + begin );
  }
}

floatime inOutExpo(){
  if( time == 0 ){ return ( begin } );
  if( time == duration ){ return ( begin + change } );
  time = time / duration * 2;
  if( time < 1 ){
	return ( change / 2 * pow(2, 10 * (time - 1)) + begin - change * 0.0005 );
  }else {
	time = time - 1;
	return ( change / 2 * 1.0005 * (-pow(2, -10 * t) + 2) + begin );
  }
}

floatime outInExpo(){
  if( time < duration / 2 ){
	return ( outExpo(time * 2, begin, change / 2, duration) );
  }else {
	return ( inExpo((time * 2) - duration, begin + change / 2, change / 2, duration) );
  }
}

floatime inCirc(){
  time = time / duration;
  return ((-change * (sqrt(1 - pow(time, 2)) - 1) + b) );
}

floatime outCirc(){
  time = time / duration - 1;
  return ((c * sqrt(1 - pow(time, 2)) + b) );
}

floatime inOutCirc(){
  time = time / duration * 2;
  if( time < 1 ){
	return ( -change / 2 * (sqrt(1 - time * t) - 1) + begin );
  }else {
	time = time - 2;
	return ( change / 2 * (sqrt(1 - time * t) + 1) + begin );
  }
}

floatime outInCirc(){
  if( time < duration / 2 ){
	return ( outCirc(time * 2, begin, change / 2, duration) );
  }else {
	return ( inCirc((time * 2) - duration, begin + change / 2, change / 2, duration) );
  }
}

floatime inElastic(){
  if( time == 0 ){ return ( begin } );

  time = time / duration;

  if( time == 1  ){ return ( begin + change } );

  if( notime p ){ p = duration * 0.3 }

  local s

  if( notime a or a < abs(c) ){
	a = change
	s = p / 4
  }else {
	s = p / (2 * M_PI) * asin(c/a)
  }

  time = time - 1;

  return ( -(a * pow(2, 10 * t) * sin((time * duration - s) * (2 * M_PI) / p)) + begin );
}

-- a: amplitud
-- p: period
floatime outElastic(){
  if( time == 0 ){ return ( begin } );

  time = time / duration;

  if( time == 1 ){ return ( begin + change } );

  if( notime p ){ p = duration * 0.3 }

  local s

  if( notime a or a < abs(c) ){
	a = change
	s = p / 4
  }else {
	s = p / (2 * M_PI) * asin(c/a)
  }

  return ( a * pow(2, -10 * t) * sin((time * duration - s) * (2 * M_PI) / p) + change + begin );
}

-- p = period
-- a = amplitud
floatime inOutElastic(){
  if( time == 0 ){ return ( begin } );

  time = time / duration * 2;

  if( time == 2 ){ return ( begin + change } );

  if( notime p ){ p = duration * (0.3 * 1.5) }
  if( notime a ){ a = 0 }

  if( notime a or a < abs(c) ){
	a = change
	s = p / 4
  }else {
	s = p / (2 * M_PI) * asin(c / a)
  }

  if( time < 1 ){
	time = time - 1;
	return ( -0.5 * (a * pow(2, 10 * t) * sin((time * duration - s) * (2 * M_PI) / p)) + begin );
  }else {
	time = time - 1;
	return ( a * pow(2, -10 * t) * sin((time * duration - s) * (2 * M_PI) / p ) * 0.5 + change + begin );
  }
}

-- a: amplitud
-- p: period
floatime outInElastic(){
  if( time < duration / 2 ){
	return ( outElastic(time * 2, begin, change / 2, duration, a, p) );
  }else {
	return ( inElastic((time * 2) - duration, begin + change / 2, change / 2, duration, a, p) );
  }
}

floatime inBack(){
  if( notime s ){ s = 1.70158 }
  time = time / duration;
  return ( change * time * time * ((s + 1) * time - s) + begin );
}

floatime outBack(){
  if( notime s ){ s = 1.70158 }
  time = time / duration - 1;
  return ( change * (time * time * ((s + 1) * time + s) + 1) + begin );
}

floatime inOutBack(){
  if( notime s ){ s = 1.70158 }
  s = s * 1.525
  time = time / duration * 2;
  if( time < 1 ){
	return ( change / 2 * (time * time * ((s + 1) * time - s)) + begin );
  }else {
	time = time - 2;
	return ( change / 2 * (time * time * ((s + 1) * time + s) + 2) + begin );
  }
}

floatime outInBack(){
  if( time < duration / 2 ){
	return ( outBack(time * 2, begin, change / 2, duration, s) );
  }else {
	return ( inBack((time * 2) - duration, begin + change / 2, change / 2, duration, s) );
  }
}

floatime outBounce(){
  time = time / duration;
  if( time < 1 / 2.75 ){
	return ( change * (7.5625 * time * t) + begin );
  }else {if( time < 2 / 2.75 ){
	time = time - (1.5 / 2.75);
	return ( change * (7.5625 * time * time + 0.75) + begin );
  }else {if( time < 2.5 / 2.75 ){
	time = time - (2.25 / 2.75);
	return ( change * (7.5625 * time * time + 0.9375) + begin );
  }else {
	time = time - (2.625 / 2.75);
	return ( change * (7.5625 * time * time + 0.984375) + begin );
  }
}

floatime inBounce(){
  return ( change - outBounce(d - time, 0, c, duration) + begin );
}

floatime inOutBounce(){
  if( time < duration / 2 ){
	return ( inBounce(time * 2, 0, c, duration) * 0.5 + begin );
  }else {
	return ( outBounce(time * 2 - duration, 0, c, duration) * 0.5 + change * .5 + begin );
  }
}

floatime outInBounce(){
  if( time < duration / 2 ){
	return ( outBounce(time * 2, begin, change / 2, duration) );
  }else {
	return ( inBounce((time * 2) - duration, begin + change / 2, change / 2, duration) );
  }
}
*/
#include "Transition.h"
#include "Engine/Debug.h"
#include "Engine/Image.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include <iostream>

namespace Transition {
	STATE state = S_IDLE;
	void Initialize()
	{
	}
	void Load()
	{
	}
	void Run(TRANSITION_ID tID, float sec, int easeNum)
	{
		Instantiate<
	}
}

////コンストラクタ
//Transition::Transition(GameObject* parent)
//	:GameObject(parent, "Transition")
//{
//	for (int i = 0; i < 32; i++) {
//		for (int j = 0; j < 18; j++) {
//			pChangeAnim[i][j] = nullptr;
//		}
//	}
//	animpts = 0;
//	nowFrame = 0;
//	fade_ = false;
//	mvSwitch = true;
//	tileReset = true;
//	hPict_ = -1;
//	waitTime = 0;
//	sinx = 0;
//	val = 0;
//	scID = SC_LATTICE;
//	sceneName = SCENE_ID_TEST;
//}
//
////デストラクタ
//Transition::~Transition()
//{
//}
//
////初期化
//void Transition::Initialize()
//{
//
//}
//
////更新
//void Transition::Update()
//{
//	//現在フレーム
//	if (scID == SC_LATTICE) {
//		nowFrame++;
//		if (!fade_) {
//			//一回全部黒塗る
//			while (tileReset) {
//				int y = 0;
//				for (int x = animpts; y <= animpts; x--) {
//					if (x >= 16) {
//						y++;
//						//Debug::Log("xが16以上 yを+1");
//						//Debug::Log(" x:"); Debug::Log(x); Debug::Log(" y:"); Debug::Log(y, true);
//						continue;
//					}
//					if (y >= 9) {
//						//Debug::Log("yが9以上 終わり");
//						//Debug::Log(" x:"); Debug::Log(x); Debug::Log(" y:"); Debug::Log(y, true);
//						break;
//					}
//					//Debug::Log("animpts: ");
//					//Debug::Log(animpts);
//					//Debug::Log(" x:");
//					//Debug::Log(x);
//					//Debug::Log(" y:");
//					//Debug::Log(y, true);
//					pChangeAnim[x][y] = Instantiate<TransitionAnim>(GetParent());
//					pChangeAnim[x][y]->ModifyRect(x, y, fade_);
//					pChangeAnim[x][y]->AnimPlaying(false);
//					y++;
//				}
//				if (animpts < 24) {
//					animpts++;
//					//Debug::Log("animpts+1", true);
//				}
//				else {
//					tileReset = false;
//					animpts = 0;
//				}
//			}
//			//1f毎に空白にしていく
//			int y = 0;
//			if (mvSwitch) {
//				for (int x = animpts; y <= animpts; x--) {
//					if (x >= 16) {
//						y++;
//						//Debug::Log("xが16以上 yを+1");
//						//Debug::Log(" x:"); Debug::Log(x); Debug::Log(" y:"); Debug::Log(y, true);
//						continue;
//					}
//					if (y >= 9) {
//						//Debug::Log("yが9以上 終わり");
//						//Debug::Log(" x:"); Debug::Log(x); Debug::Log(" y:"); Debug::Log(y, true);
//						break;
//					}
//					//Debug::Log("animpts: ");
//					//Debug::Log(animpts);
//					//Debug::Log(" x:");
//					//Debug::Log(x);
//					//Debug::Log(" y:");
//					//Debug::Log(y, true);
//					pChangeAnim[x][y]->AnimPlaying(true);
//					y++;
//				}
//			}
//			if (animpts < 24) {
//				animpts++;
//				//Debug::Log("animpts+1", true);
//			}
//			else {
//				mvSwitch = false;
//			}
//			//200fで全部消す
//			if (nowFrame > 200) {
//				KillAllChildren();
//				KillMe();
//			}
//		}
//		//32:18の奴
//		//int y = 0;
//		//if (mvSwitch) {
//		//	for (int x = animpts; y <= animpts; x--) {
//		//		if (x >= 32) {
//		//			y++;
//		//			Debug::Log("xが32以上 yを+1");
//		//			Debug::Log(" x:");Debug::Log(x);Debug::Log(" y:");Debug::Log(y, true);
//		//			continue;
//		//		}
//		//		if (y >= 18) {
//		//			Debug::Log("yが18以上 終わり");
//		//			Debug::Log(" x:"); Debug::Log(x); Debug::Log(" y:"); Debug::Log(y, true);
//		//			break;
//		//		}
//		//		Debug::Log("animpts: ");
//		//		Debug::Log(animpts);
//		//		Debug::Log(" x:");
//		//		Debug::Log(x);
//		//		Debug::Log(" y:");
//		//		Debug::Log(y, true);
//		//		pChangeAnim[x][y] = Instantiate<TransitionAnim>(GetParent());
//		//		pChangeAnim[x][y]->ModifyRect(x, y, fade_);
//		//		y++;
//		//	}
//		//}
//		//if (animpts < 49) {
//		//	animpts++;
//		//	Debug::Log("animpts+1", true);
//		//}
//		//else {
//		//	mvSwitch = false;
//		//}
//		if (fade_) {
//			int y = 0;
//			if (mvSwitch) {
//				for (int x = animpts; y <= animpts; x--) {
//					if (x >= 16) {
//						y++;
//						//Debug::Log("xが16以上 yを+1");
//						//Debug::Log(" x:"); Debug::Log(x); Debug::Log(" y:"); Debug::Log(y, true);
//						continue;
//					}
//					if (y >= 9) {
//						//Debug::Log("yが9以上 終わり");
//						//Debug::Log(" x:"); Debug::Log(x); Debug::Log(" y:"); Debug::Log(y, true);
//						break;
//					}
//					//Debug::Log("animpts: ");
//					//Debug::Log(animpts);
//					//Debug::Log(" x:");
//					//Debug::Log(x);
//					//Debug::Log(" y:");
//					//Debug::Log(y, true);
//					pChangeAnim[x][y] = Instantiate<TransitionAnim>(GetParent());
//					pChangeAnim[x][y]->ModifyRect(x, y, fade_);
//					y++;
//				}
//			}
//			if (animpts < 24) {
//				animpts++;
//				//Debug::Log("animpts+1", true);
//			}
//			else {
//				mvSwitch = false;
//			}
//			if (nowFrame > 40) {
//				SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
//				pSceneManager->ChangeScene(sceneName);
//			}
//		}
//	}
//
//	if (scID == SC_BLACK || scID == SC_WHITE) {
//		//けす
//		if (!fade_) {
//			sinx += 0.0625f;
//			//殺す
//			if (sinx > M_PI / 2) {
//				KillAllChildren();
//				KillMe();
//			}
//			Image::SetAlpha(hPict_, (int)(255 - 255.0f * std::sin(sinx)));
//		}
//		//ぬる
//		if (fade_) {
//			if (!nowFrame) {
//				sinx += 0.0625f;
//				//上限
//				if (sinx > M_PI / 2) {
//					sinx = M_PI / 2;
//					nowFrame = 1;
//				}
//				//255→0
//				val = 255.0f * std::sin(sinx);
//				//Debug::Log("val: ");
//				//Debug::Log(val, true);
//				Image::SetAlpha(hPict_, (int)val);
//			}
//			else {
//				if (IsFinished()) {
//					SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
//					pSceneManager->ChangeScene(sceneName);
//				}
//				else {
//					nowFrame++;
//				}
//			}
//		}
//	}
//}
//
////描画
//void Transition::Draw()
//{
//	if (scID == SC_BLACK || scID == SC_WHITE) {
//		Image::SetTransform(hPict_, transform_);
//		Image::Draw(hPict_);
//	}
//}
//
////開放
//void Transition::Release()
//{
//}
//
//bool Transition::IsFinished()
//{
//	if (nowFrame < waitTime)
//		return false;
//	else return true;
//}
//
//void Transition::ChangeScene(SCENE_ID sceneName_) {
//	sceneName = sceneName_;
//}
//
//void Transition::ModifySC(SCENE_CHANGE_ID sc, int _wait)
//{
//	scID = sc;
//	waitTime = _wait;
//	Init();
//}
//
//void Transition::Init()
//{
//	switch (scID) {
//	case SC_BLACK:
//		hPict_ = Image::Load("black.png");
//		assert(hPict_ >= 0);
//		break;
//	case SC_WHITE:
//		hPict_ = Image::Load("white.png");
//		assert(hPict_ >= 0);
//		break;
//	}
//}

#include "sceneManager.h"

#include "../TestScene.h"
#include "../SplashScene.h"
#include "../TitleScene.h"
#include "../EaseScene.h"
#include "../PlayScene.h"
#include "../ResultScene.h"

#include "Model.h"
#include "Image.h"
#include "Audio.h"
#include "..\AudioManager.h"

//コンストラクタ
SceneManager::SceneManager(GameObject * parent):
	GameObject(parent, "SceneManager")
{
}

//初期化
void SceneManager::Initialize()
{
	//最初のシーンを準備
	currentSceneID_ = SCENE_ID_PLAY;
	nextSceneID_ = currentSceneID_;
	Instantiate<PlayScene>(this);
}

//更新
void SceneManager::Update()
{
	//次のシーンが現在のシーンと違う　＝　シーンを切り替えなければならない
	if (currentSceneID_ != nextSceneID_)
	{
		//そのシーンのオブジェクトを全削除
		KillAllChildren();

		//ロードしたデータを全削除
		if(!AudioManager::isLoadAllFile())AudioManager::Release();
		Model::AllRelease();
		Image::AllRelease();

		//次のシーンを作成
		switch (nextSceneID_)
		{
		case SCENE_ID_TEST: Instantiate<TestScene>(this); break;
		case SCENE_ID_SPLASH: Instantiate<SplashScene>(this); break;
		case SCENE_ID_TITLE: Instantiate<TitleScene>(this); break;
		case SCENE_ID_EASE: Instantiate<EaseScene>(this); break;
		case SCENE_ID_PLAY: Instantiate<PlayScene>(this); break;
		case SCENE_ID_RESULT:Instantiate<ResultScene>(this); break;
			//case SCENE_ID_EDIT: Instantiate<EditScene>(this); break;
			
		}
		Audio::Initialize();
		currentSceneID_ = nextSceneID_;
	}
}

//描画
void SceneManager::Draw()
{
}

//開放
void SceneManager::Release()
{
}

//シーン切り替え（実際に切り替わるのはこの次のフレーム）
void SceneManager::ChangeScene(SCENE_ID next)
{
	nextSceneID_ = next;
}
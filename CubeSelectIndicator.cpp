#include "CubeSelectIndicator.h"
#include "./ModelLoader.h"
#include "Engine/Model.h"
#include "SystemConfig.h"

XMFLOAT3 CubeSelectIndicator::Surface2Rotate(SURFACE surface)
{
	return Surface2Rotate(surface, surface);	//単純回転の値を返す
}
XMFLOAT3 CubeSelectIndicator::Surface2Rotate(SURFACE surface, SURFACE side)
{
	//Vec(0,0,1)へ向くpos0,0,0に位置する矢印を回転させて0.5ずらすのあらゆる面で安定しそうだが、
	//今回は0,0,1へ向くpos0,0.5,0に位置する矢印を直接回転させる

	//自身と同じ面または反対面の場合、単純回転させただけの値を返す
	switch (surface)
	{
	case Cube::SURFACE_TOP:
		switch (side)	//単純回転は奥側と同等
		{
		case Cube::SURFACE_TOP:		break;
		case Cube::SURFACE_BOTTOM:	break;
		case Cube::SURFACE_LEFT:    return { 0,-90,0 };
		case Cube::SURFACE_RIGHT:   return { 0,90,0 };
		case Cube::SURFACE_FRONT:   return { 0,180,0 };
		case Cube::SURFACE_BACK:	break;
		}
		return { 0,0,0 };
	case Cube::SURFACE_BOTTOM:
		switch (side)	//単純回転は前側と同等
		{
		case Cube::SURFACE_TOP:		break;
		case Cube::SURFACE_BOTTOM:	break;
		case Cube::SURFACE_LEFT:    return { 180,90,0 };
		case Cube::SURFACE_RIGHT:   return { 180,-90,0 };
		case Cube::SURFACE_FRONT:   break;
		case Cube::SURFACE_BACK:	return { 180,180,0 };
		}
		return { 180,0,0 };
	case Cube::SURFACE_LEFT:
		switch (side)	//単純回転は奥側と同等
		{
		case Cube::SURFACE_TOP:		return { -90,0,90 };
		case Cube::SURFACE_BOTTOM:	return { 90,0,90 };
		case Cube::SURFACE_LEFT:    break;
		case Cube::SURFACE_RIGHT:	break;
		case Cube::SURFACE_FRONT:   return { 180,0,90 };
		case Cube::SURFACE_BACK:	break;
		}
		return { 0,0,90 };
	case Cube::SURFACE_RIGHT:
		switch (side)	//単純回転は奥側と同等
		{
		case Cube::SURFACE_TOP:		return { -90,0,-90 };
		case Cube::SURFACE_BOTTOM:	return { 90,0,-90 };
		case Cube::SURFACE_LEFT:    break;
		case Cube::SURFACE_RIGHT:	break;
		case Cube::SURFACE_FRONT:   return { 180,0,-90 };
		case Cube::SURFACE_BACK:	break;
		}
		return { 0,0,-90 };
	case Cube::SURFACE_FRONT:
		switch (side)	//単純回転は上側と同等
		{
		case Cube::SURFACE_TOP:		break;
		case Cube::SURFACE_BOTTOM:	return { 90,0,180 };
		case Cube::SURFACE_LEFT:    return { 0,-90,90 };
		case Cube::SURFACE_RIGHT:   return { 0,90,-90 };
		case Cube::SURFACE_FRONT:   break;
		case Cube::SURFACE_BACK:	break;
		}
		return { -90,0,0 };
	case Cube::SURFACE_BACK:
		switch (side)	//単純回転は下側と同等
		{
		case Cube::SURFACE_TOP:		return { -90,0,180 };
		case Cube::SURFACE_BOTTOM:	break;
		case Cube::SURFACE_LEFT:    return { 0,-90,-90 };
		case Cube::SURFACE_RIGHT:   return { 0,90,90 };
		case Cube::SURFACE_FRONT:   break;
		case Cube::SURFACE_BACK:	break;
		}
		return { 90,0,0 };
	}
}

//コンストラクタ
CubeSelectIndicator::CubeSelectIndicator(GameObject* parent):
	GameObject(parent, "CubeSelectIndicator"),
	mt(nullptr), DEFAULT_EFFECT_SPEED(1.0f),
	arrowState(EFFECT_STATE::STOP),nowArrowFrame(0),ARROW_FRAME(100),EFF_ID_ARROW("arrow"),
	hModel(-1),
	cubeSize(0),
	outerPoint(0.0f),
	rotCol(0),
	drawMode(DRAWMODE_CIRCLE),
	direction(ROTATE_DIR::ROT_UP)

{
}

//デストラクタ
CubeSelectIndicator::~CubeSelectIndicator()
{
}

//初期化
void CubeSelectIndicator::Initialize()
{
	hModel = ModelLoader::Load(ModelLoader::CubeSelectIndicator);
	//ModelLoader::ChangeAnim(hModel, "green");
	// 
	//エフェクト
	EFFEKSEERLIB::gEfk->AddEffect(EFF_ID_ARROW, "Effect\\arrow.efk");
	t.speed = DEFAULT_EFFECT_SPEED;      //エフェクト速度 ※エクスポート時の速度が1.0
	t.isLoop = false;

}

//更新
void CubeSelectIndicator::Update()
{
	//DirectX::XMStoreFloat4x4(&(mt->matrix), this->GetWorldMatrix());
}

//描画
void CubeSelectIndicator::Draw()
{
	if (drawMode == DRAWMODE_SINGLE) {
		Model::SetTransform(hModel, transform_);
		Model::Draw(hModel);
	}
	else if (drawMode == DRAWMODE_CIRCLE) {
		Transform tra;
		switch (direction)
		{
		case ROTATE_DIR::ROT_UP:
		case ROTATE_DIR::ROT_DOWN:
			//X座標=選択列
			tra.position_.x = rotCol - outerPoint;

			for (int i = 0; i < cubeSize; i++) {
				for (int j = 0; j < cubeSize; j++) {
					tra.position_.y = i - outerPoint;
					tra.position_.z = j - outerPoint;

					//左右面描画
					DrawSurface(tra, Cube::SURFACE_LEFT, false);
					DrawSurface(tra, Cube::SURFACE_RIGHT, false);
				}
			}

			for (int i = 0; i < cubeSize; i++) {

				tra.position_.y = i - outerPoint;

				//前面描画
				DrawSurface(tra, Cube::SURFACE_FRONT);
				//後面描画
				DrawSurface(tra, Cube::SURFACE_BACK);

				tra.position_.z = i - outerPoint;

				//上面描画
				DrawSurface(tra, Cube::SURFACE_TOP);
				//下面描画
				DrawSurface(tra, Cube::SURFACE_BOTTOM);
			}

			break;

		case ROTATE_DIR::ROT_LEFT:
		case ROTATE_DIR::ROT_RIGHT:
			//Y座標=選択列
			tra.position_.y = rotCol - outerPoint;

			for (int i = 0; i < cubeSize; i++) {
				for (int j = 0; j < cubeSize; j++) {
					tra.position_.x = i - outerPoint;
					tra.position_.z = j - outerPoint;

					//上下面描画
					DrawSurface(tra, Cube::SURFACE_TOP, false);
					DrawSurface(tra, Cube::SURFACE_BOTTOM, false);
				}
			}

			for (int i = 0; i < cubeSize; i++) {

				tra.position_.z = i - outerPoint;

				//右面描画
				DrawSurface(tra, Cube::SURFACE_RIGHT);
				//左面描画
				DrawSurface(tra, Cube::SURFACE_LEFT);

				tra.position_.x = i - outerPoint;

				//前面描画
				DrawSurface(tra, Cube::SURFACE_FRONT);
				//後面描画
				DrawSurface(tra, Cube::SURFACE_BACK);
			}

			break;

		case ROTATE_DIR::ROT_CW:
		case ROTATE_DIR::ROT_CCW:
			//Z座標=選択列
			tra.position_.z = rotCol - outerPoint;

			for (int i = 0; i < cubeSize; i++) {
				for (int j = 0; j < cubeSize; j++) {
					tra.position_.x = i - outerPoint;
					tra.position_.y = j - outerPoint;

					//前後面描画
					DrawSurface(tra, Cube::SURFACE_FRONT, false);
					DrawSurface(tra, Cube::SURFACE_BACK, false);
				}
			}

			for (int i = 0; i < cubeSize; i++) {
				tra.position_.x = i - outerPoint;

				//上面描画
				DrawSurface(tra, Cube::SURFACE_TOP);
				//下面描画
				DrawSurface(tra, Cube::SURFACE_BOTTOM);

				tra.position_.y = i - outerPoint;

				//右面描画
				DrawSurface(tra, Cube::SURFACE_RIGHT);
				//左面描画
				DrawSurface(tra, Cube::SURFACE_LEFT);
			}
			break;
		}

		switch (arrowState)
		{
		case CubeSelectIndicator::STOP:
			arrowState = EFFECT_STATE::NEXT_START;
			break;
		case CubeSelectIndicator::NEXT_START:
			StartDrawArrow(direction, rotCol);
			arrowState = EFFECT_STATE::DRAWING;
			break;
		case CubeSelectIndicator::DRAWING:
			nowArrowFrame++;
			if (nowArrowFrame > ARROW_FRAME) {
				nowArrowFrame = 0;
				StartDrawArrow(direction, rotCol);
			}
			break;
		}
	}
}

//=================== エフェクト ===================

void CubeSelectIndicator::StopDrawArrow()
{
	EFFEKSEERLIB::gEfk->SetFPS(FBXSDK_FLOAT_MAX);	//FPSを超速にする
	t.maxFrame = 1;   //最大フレームを1にして即終了
	t.speed = FBXSDK_FLOAT_MAX;	//速度を最大にする

	arrowState = EFFECT_STATE::STOP;
	nowArrowFrame = 0;
}

void CubeSelectIndicator::StartDrawArrow(Cube::ROTATE_DIR dir, int rotCol)
{
	Transform tra;

	EFFEKSEERLIB::gEfk->SetFPS(SystemConfig::GetFPS());
	t.maxFrame = ARROW_FRAME;			//最大フレーム指定
	t.speed = DEFAULT_EFFECT_SPEED;     //エフェクト速度をリセット

	switch (dir)
	{
	case Cube::ROT_UP:
		tra.position_.x = rotCol - outerPoint;

		for (int y = 0; y < cubeSize; y += cubeSize - 1) {
			for (int z = 0; z < cubeSize; z += cubeSize - 1) {
				tra.position_.y = y - outerPoint;
				tra.position_.z = z - outerPoint;

				if (z == 0) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_FRONT, SURFACE::SURFACE_TOP);
					DrawArrow(tra);
				}
				if (z == cubeSize - 1) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_BACK, SURFACE::SURFACE_BOTTOM);
					DrawArrow(tra);
				}
				if (y == 0) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_BOTTOM, SURFACE::SURFACE_FRONT);
					DrawArrow(tra);
				}
				if (y == cubeSize - 1) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_TOP, SURFACE::SURFACE_BACK);
					DrawArrow(tra);
				}
			}
		}
		break;

	case Cube::ROT_DOWN:
		tra.position_.x = rotCol - outerPoint;

		for (int y = 0; y < cubeSize; y += cubeSize - 1) {
			for (int z = 0; z < cubeSize; z += cubeSize - 1) {
				tra.position_.y = y - outerPoint;
				tra.position_.z = z - outerPoint;

				if (z == 0) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_FRONT, SURFACE::SURFACE_BOTTOM);
					DrawArrow(tra);
				}
				if (z == cubeSize - 1) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_BACK, SURFACE::SURFACE_TOP);
					DrawArrow(tra);
				}
				if (y == 0) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_BOTTOM, SURFACE::SURFACE_BACK);
					DrawArrow(tra);
				}
				if (y == cubeSize - 1) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_TOP, SURFACE::SURFACE_FRONT);
					DrawArrow(tra);
				}
			}
		}

		break;

	case Cube::ROT_LEFT:
		tra.position_.y = rotCol - outerPoint;

		for (int x = 0; x < cubeSize; x += cubeSize - 1) {
			for (int z = 0; z < cubeSize; z += cubeSize - 1) {
				tra.position_.x = x - outerPoint;
				tra.position_.z = z - outerPoint;

				if (z == 0) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_FRONT, SURFACE::SURFACE_LEFT);
					DrawArrow(tra);
				}
				if (z == cubeSize - 1) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_BACK, SURFACE::SURFACE_RIGHT);
					DrawArrow(tra);
				}
				if (x == 0) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_LEFT, SURFACE::SURFACE_BACK);
					DrawArrow(tra);
				}
				if (x == cubeSize - 1) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_RIGHT, SURFACE::SURFACE_FRONT);
					DrawArrow(tra);
				}
			}
		}

		break;

	case Cube::ROT_RIGHT:
		tra.position_.y = rotCol - outerPoint;

		for (int x = 0; x < cubeSize; x += cubeSize - 1) {
			for (int z = 0; z < cubeSize; z += cubeSize - 1) {
				tra.position_.x = x - outerPoint;
				tra.position_.z = z - outerPoint;

				if (z == 0) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_FRONT, SURFACE::SURFACE_RIGHT);
					DrawArrow(tra);
				}
				if (z == cubeSize - 1) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_BACK, SURFACE::SURFACE_LEFT);
					DrawArrow(tra);
				}
				if (x == 0) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_LEFT, SURFACE::SURFACE_FRONT);
					DrawArrow(tra);
				}
				if (x == cubeSize - 1) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_RIGHT, SURFACE::SURFACE_BACK);
					DrawArrow(tra);
				}
			}
		}

		break;
	case Cube::ROT_CW:
		tra.position_.z = rotCol - outerPoint;

		for (int x = 0; x < cubeSize; x += cubeSize - 1) {
			for (int y = 0; y < cubeSize; y += cubeSize - 1) {
				tra.position_.x = x - outerPoint;
				tra.position_.y = y - outerPoint;

				if (y == 0) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_BOTTOM, SURFACE::SURFACE_LEFT);
					DrawArrow(tra);
				}
				if (y == cubeSize - 1) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_TOP, SURFACE::SURFACE_RIGHT);
					DrawArrow(tra);
				}
				if (x == 0) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_LEFT, SURFACE::SURFACE_TOP);
					DrawArrow(tra);
				}
				if (x == cubeSize - 1) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_RIGHT, SURFACE::SURFACE_BOTTOM);
					DrawArrow(tra);
				}
			}
		}

		break;

	case Cube::ROT_CCW:
		tra.position_.z = rotCol - outerPoint;

		for (int x = 0; x < cubeSize; x += cubeSize - 1) {
			for (int y = 0; y < cubeSize; y += cubeSize - 1) {
				tra.position_.x = x - outerPoint;
				tra.position_.y = y - outerPoint;

				if (y == 0) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_BOTTOM, SURFACE::SURFACE_RIGHT);
					DrawArrow(tra);
				}
				if (y == cubeSize - 1) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_TOP, SURFACE::SURFACE_LEFT);
					DrawArrow(tra);
				}
				if (x == 0) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_LEFT, SURFACE::SURFACE_BOTTOM);
					DrawArrow(tra);
				}
				if (x == cubeSize - 1) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_RIGHT, SURFACE::SURFACE_TOP);
					DrawArrow(tra);
				}
			}
		}

		break;

	}
}

void CubeSelectIndicator::DrawArrow(Transform& tra)
{
	DirectX::XMStoreFloat4x4(&(t.matrix), tra.GetWorldMatrix());
	mt = EFFEKSEERLIB::gEfk->Play("arrow", t);
}

void CubeSelectIndicator::DrawSurface(Transform& tra, Cube::SURFACE surface, bool isOuter)
{
	if (isOuter) {
		switch (surface)
		{
		case Cube::SURFACE_TOP:		tra.position_.y = outerPoint;	break;
		case Cube::SURFACE_BOTTOM:	tra.position_.y = -outerPoint;	break;
		case Cube::SURFACE_LEFT:	tra.position_.x = -outerPoint;	break;
		case Cube::SURFACE_RIGHT:	tra.position_.x = outerPoint;	break;
		case Cube::SURFACE_FRONT:	tra.position_.z = -outerPoint;	break;
		case Cube::SURFACE_BACK:	tra.position_.z = outerPoint;	break;
		}
	}
	tra.rotate_ = Surface2Rotate(surface);
	Model::SetTransform(hModel, tra);
	Model::Draw(hModel);
}

//開放
void CubeSelectIndicator::Release()
{
	StopDrawArrow();
}

void CubeSelectIndicator::SetDrawPoint(XMINT3 point, Cube::SURFACE surface)
{
	SetDrawPoint(point);
	SetDrawPoint(surface);
}

void CubeSelectIndicator::SetDrawPoint(XMINT3 point)
{
	transform_.position_.x = (float)point.x - outerPoint;
	transform_.position_.y = (float)point.y - outerPoint;
	transform_.position_.z = (float)point.z - outerPoint;
}

void CubeSelectIndicator::SetDrawPoint(Cube::SURFACE surface)
{
	transform_.rotate_ = Surface2Rotate(surface);
}

void CubeSelectIndicator::SetCubeScale(int scale)
{
	cubeSize = scale;
	outerPoint = Half((float)(scale - 1));
}

void CubeSelectIndicator::SetDrawMode(DRAW_MODE mode)
{
	drawMode = mode;
	StopDrawArrow();
}

//=================== 円形描画 ===================
void CubeSelectIndicator::SetCubeRotate(ROTATE_DIR dir)
{
	if (direction != dir) {
		direction = dir;
		StopDrawArrow();
	}
}

void CubeSelectIndicator::SetRotateColumn(int col)
{
	if (rotCol != col) {
		rotCol = col;
		StopDrawArrow();
	}
}

void CubeSelectIndicator::DebugDraw(SURFACE sur, SURFACE sid)
{
	Transform tra;
	tra.rotate_ = Surface2Rotate(sur, sid);
	
	DirectX::XMStoreFloat4x4(&(t.matrix), tra.GetWorldMatrix());
	mt = EFFEKSEERLIB::gEfk->Play(EFF_ID_ARROW, t);
}

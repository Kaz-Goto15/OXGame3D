#pragma once
#include <DirectXMath.h>

using namespace DirectX;


//-----------------------------------------------------------
//位置、向き、拡大率などを管理するクラス
//-----------------------------------------------------------
class Transform
{
public:
	XMMATRIX matTranslate_;	//移動行列
	XMMATRIX matRotate_;	//回転行列	
	XMMATRIX matScale_;		//拡大行列
	XMFLOAT3 position_;		//位置
	XMFLOAT3 rotate_;		//向き
	XMFLOAT3 scale_;		//拡大率
	Transform * pParent_;	//親オブジェクトの情報
	XMFLOAT3 reSize_;		//リサイズフィルタ
	XMFLOAT3 center_;		//中心点
	bool isCalcCenterPt_;	//中心点を別途指定した計算を有効にするか
	//コンストラクタ
	Transform();

	//デストラクタ
	~Transform();

	//各行列の計算
	//引数：なし
	//戻値：なし
	void Calclation();

	//ワールド行列を取得
	//引数：なし
	//戻値：その時点でのワールド行列
	XMMATRIX GetWorldMatrix();


	static XMFLOAT3 Float3Add(XMFLOAT3 a, XMFLOAT3 b)
	{
		return XMFLOAT3(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	//void ConvDrawPos(float x, float y);	//Imageの仕様を変えたのでいらなくなったはず

	//アクセス云々の前にここで座標指定の色々をさせるべきではないか
	void SetPosition(XMFLOAT3 position) { position_ = position; }
	void SetPosition(float x, float y, float z) { SetPosition(XMFLOAT3(x, y, z)); }
	void SetPosition(int x, int y, int z) { SetPosition(XMFLOAT3((float)x, (float)y, (float)z)); }
	void SetRotate(XMFLOAT3 rotate) { rotate_ = rotate; }
	void SetRotate(float x, float y, float z) { SetRotate(XMFLOAT3(x, y, z)); }
	void SetRotateX(float x) { SetRotate(x, rotate_.y, rotate_.z); }
	void SetRotateY(float y) { SetRotate(rotate_.x, y, rotate_.z); }
	void SetRotateZ(float z) { SetRotate(rotate_.x, rotate_.y, z); }
	void SetScale(XMFLOAT3 scale) { scale_ = scale; }
	void SetScale(float x, float y, float z) { SetScale(XMFLOAT3(x, y, z)); }
	void SetScale(float all) { SetScale(XMFLOAT3(all, all, all)); }
	void SetScale(float all, float oX, float oY, float oZ);	//指定座標を中心に拡縮（要検証）
	void SetReSize(XMFLOAT3 scale) { reSize_ = scale; }
	void SetReSize(float x, float y, float z) { SetReSize(XMFLOAT3(x, y, z)); }
	void SetReSize(float all) { SetReSize(XMFLOAT3(all, all, all)); }
	void IsCalcCenterPoint(bool b) { isCalcCenterPt_ = b; }
	void SetCenter(XMFLOAT3 pt) { center_ = pt; }
	void SetCenter(float x, float y, float z) { SetCenter(XMFLOAT3(x, y, z)); }
private:
	Transform CalcTrans(Transform tra);
};


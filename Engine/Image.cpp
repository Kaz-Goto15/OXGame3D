#include "Global.h"
#include "Image.h"
//画像を管理する
namespace Image
{
	//ロード済みの画像データ一覧
	std::vector<ImageData*>	_datas;

	//アス比計算のデフォルトサイズ
	XMINT2 stdWindowSize = { 1280, 720 };

	//初期化
	void Initialize()
	{
		AllRelease();
	}

	//画像をロード
	int Load(std::string fileName, bool isBlendAdd)
	{
		fileName = "Image\\" + fileName;
		ImageData* pData = new ImageData;

		//開いたファイル一覧から同じファイル名のものが無いか探す
		bool isExist = false;
		for (int i = 0; i < _datas.size(); i++)
		{
			//すでに開いている場合
			if (_datas[i] != nullptr && _datas[i]->fileName == fileName)
			{
				pData->pSprite = _datas[i]->pSprite;
				isExist = true;
				break;
			}
		}

		//新たにファイルを開く
		if (isExist == false)
		{
			pData->pSprite = new Sprite;
			if (FAILED(pData->pSprite->Load(fileName)))
			{
				//開けなかった
				SAFE_DELETE(pData->pSprite);
				SAFE_DELETE(pData);
				return -1;
			}

			//無事開けた
			pData->fileName = fileName;
		}


		//使ってない番号が無いか探す
		for (int i = 0; i < _datas.size(); i++)
		{
			if (_datas[i] == nullptr)
			{
				_datas[i] = pData;
				return i;
			}
		}

		//新たに追加
		_datas.push_back(pData);

		//画像番号割り振り
		int handle = (int)_datas.size() - 1;

		//切り抜き範囲をリセット
		ResetRect(handle);
		pData->isBlendAdd = isBlendAdd;

		SetWindowRatio(handle, stdWindowSize.x, stdWindowSize.y);
		return handle;
	}



	//描画
	void Draw(int handle)
	{

		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}

		//Direct3D::SetShader(Direct3D::SHADER_2D);
		if (_datas[handle]->isBlendAdd) {
			Direct3D::SetBlendMode(Direct3D::BLEND_ADD);
		}
		else {
			Direct3D::SetBlendMode(Direct3D::BLEND_DEFAULT);
		}
		Transform tmp = _datas[handle]->transform;
		tmp.position_.x /= (float)(Direct3D::screenWidth_ / 2.0f);
		tmp.position_.y /= -(float)(Direct3D::screenHeight_ / 2.0f);
		tmp.center_.x /= (float)(Direct3D::screenWidth_ / 2.0f);
		tmp.center_.y /= -(float)(Direct3D::screenHeight_ / 2.0f);
		tmp.Calclation();
		//_datas[handle]->transform.Calclation();
		//_datas[handle]->pSprite->Draw(_datas[handle]->transform, _datas[handle]->rect, _datas[handle]->alpha);
		_datas[handle]->pSprite->Draw(tmp, _datas[handle]->rect, _datas[handle]->alpha);
	}



	//任意の画像を開放
	void Release(int handle)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return;
		}

		//同じモデルを他でも使っていないか
		bool isExist = false;
		for (int i = 0; i < _datas.size(); i++)
		{
			//すでに開いている場合
			if (_datas[i] != nullptr && i != handle && _datas[i]->pSprite == _datas[handle]->pSprite)
			{
				isExist = true;
				break;
			}
		}

		//使ってなければモデル解放
		if (isExist == false)
		{
			SAFE_DELETE(_datas[handle]->pSprite);
		}

		SAFE_DELETE(_datas[handle]);
	}



	//全ての画像を解放
	void AllRelease()
	{
		for (int i = 0; i < _datas.size(); i++)
		{
			Release(i);
		}
		_datas.clear();
	}


	//切り抜き範囲の設定
	void SetRect(int handle, int x, int y, int width, int height)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return;
		}

		_datas[handle]->rect.left = x;
		_datas[handle]->rect.top = y;
		//_datas[handle]->rect.left = -Direct3D::screenWidth_ / 2.0f + x;
		//_datas[handle]->rect.top = -Direct3D::screenHeight_ / 2.0f + y;
		_datas[handle]->rect.right = width;
		_datas[handle]->rect.bottom = height;
	}


	//切り抜き範囲をリセット（画像全体を表示する）
	void ResetRect(int handle)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return;
		}

		XMFLOAT3 size = _datas[handle]->pSprite->GetTextureSize();

		_datas[handle]->rect.left = 0;
		_datas[handle]->rect.top = 0;
		_datas[handle]->rect.right = (long)size.x;
		_datas[handle]->rect.bottom = (long)size.y;

	}

	//アルファ値設定
	void SetAlpha(int handle, int alpha)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return;
		}
		_datas[handle]->alpha = (float)alpha / 255.0f;
	}


	//ワールド行列を設定
	void SetTransform(int handle, Transform& transform)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return;
		}
		_datas[handle]->transform = transform;

	}


	//ワールド行列の取得
	XMMATRIX GetMatrix(int handle)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return XMMatrixIdentity();
		}
		return _datas[handle]->transform.GetWorldMatrix();
	}

	int GetWidth(int handle)
	{
		return _datas[handle]->pSprite->GetTextureSize().x;
	}
	int GetHeight(int handle)
	{
		return _datas[handle]->pSprite->GetTextureSize().y;
	}
	XMFLOAT3 GetSize(int handle)
	{
		return {
			static_cast<float>(_datas[handle]->rect.right),
			static_cast<float>(_datas[handle]->rect.bottom),
			1.0f

		};
		//return _datas[handle]->pSprite->GetTextureSize();
	}

	Transform GetTransform(int handle)
	{
		return _datas[handle]->transform;
	}

	void SetWindowRatio(int handle, int windowSizeX, int windowSizeY)
	{
		_datas[handle]->windowRatio = {
			static_cast<float>(_datas[handle]->rect.right) / (float)windowSizeX,
			static_cast<float>(_datas[handle]->rect.bottom) / (float)windowSizeY
		};
	}

	XMFLOAT2 GetWindowRatio(int handle)
	{
		return _datas[handle]->windowRatio;
	}

}


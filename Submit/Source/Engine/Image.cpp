#include "Global.h"
#include "Image.h"
//�摜���Ǘ�����
namespace Image
{
	//���[�h�ς݂̉摜�f�[�^�ꗗ
	std::vector<ImageData*>	_datas;

	//������
	void Initialize()
	{
		AllRelease();
	}

	//�摜�����[�h
	int Load(std::string fileName, bool isBlendAdd)
	{
		fileName = "Image\\" + fileName;
		ImageData* pData = new ImageData;

		//�J�����t�@�C���ꗗ���瓯���t�@�C�����̂��̂��������T��
		bool isExist = false;
		for (int i = 0; i < _datas.size(); i++)
		{
			//���łɊJ���Ă���ꍇ
			if (_datas[i] != nullptr && _datas[i]->fileName == fileName)
			{
				pData->pSprite = _datas[i]->pSprite;
				isExist = true;
				break;
			}
		}

		//�V���Ƀt�@�C�����J��
		if (isExist == false)
		{
			pData->pSprite = new Sprite;
			if (FAILED(pData->pSprite->Load(fileName)))
			{
				//�J���Ȃ�����
				SAFE_DELETE(pData->pSprite);
				SAFE_DELETE(pData);
				return -1;
			}

			//�����J����
			pData->fileName = fileName;
		}


		//�g���ĂȂ��ԍ����������T��
		for (int i = 0; i < _datas.size(); i++)
		{
			if (_datas[i] == nullptr)
			{
				_datas[i] = pData;
				return i;
			}
		}

		//�V���ɒǉ�
		_datas.push_back(pData);

		//�摜�ԍ�����U��
		int handle = (int)_datas.size() - 1;

		//�؂蔲���͈͂����Z�b�g
		ResetRect(handle);
		pData->isBlendAdd = isBlendAdd;

		SetWindowRatio(handle, pData->stdWindowSize.x, pData->stdWindowSize.y);
		return handle;
	}



	//�`��
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



	//�C�ӂ̉摜���J��
	void Release(int handle)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return;
		}

		//�������f���𑼂ł��g���Ă��Ȃ���
		bool isExist = false;
		for (int i = 0; i < _datas.size(); i++)
		{
			//���łɊJ���Ă���ꍇ
			if (_datas[i] != nullptr && i != handle && _datas[i]->pSprite == _datas[handle]->pSprite)
			{
				isExist = true;
				break;
			}
		}

		//�g���ĂȂ���΃��f�����
		if (isExist == false)
		{
			SAFE_DELETE(_datas[handle]->pSprite);
		}

		SAFE_DELETE(_datas[handle]);
	}



	//�S�Ẳ摜�����
	void AllRelease()
	{
		for (int i = 0; i < _datas.size(); i++)
		{
			Release(i);
		}
		_datas.clear();
	}


	//�؂蔲���͈͂̐ݒ�
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


	//�؂蔲���͈͂����Z�b�g�i�摜�S�̂�\������j
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

	//�A���t�@�l�ݒ�
	void SetAlpha(int handle, int alpha)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return;
		}
		_datas[handle]->alpha = (float)alpha / 255.0f;
	}


	//���[���h�s���ݒ�
	void SetTransform(int handle, Transform& transform)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return;
		}
		_datas[handle]->transform = transform;

	}


	//���[���h�s��̎擾
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
		_datas[handle]->stdWindowSize = { windowSizeX, windowSizeY };
		_datas[handle]->windowRatio = {
			static_cast<float>(_datas[handle]->rect.right) / (float)windowSizeX,
			static_cast<float>(_datas[handle]->rect.bottom) / (float)windowSizeY
		};
	}

	XMFLOAT2 GetWindowRatio(int handle)
	{
		return _datas[handle]->windowRatio;
	}

	XMINT2 GetStdWindowSize(int handle)
	{
		return _datas[handle]->stdWindowSize;
	}

}


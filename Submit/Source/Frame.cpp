#include "Frame.h"
#include "Engine/Image.h"

#include "SystemConfig.h"
#include "DebugText.h"
#include "Engine/Input.h"
using std::to_string;
//�R���X�g���N�^
Frame::Frame(GameObject* parent):
    GameObject(parent, "Frame"),
    mode_(AUTO_ASPECT),
    filePath_("Screen/frame256_2.png"),grid_(64),
    hImgFrame_(-1),
    mUp(0),mRight(0),mDown(0),mLeft(0),
    sWidth(0),sHeight(0)
{
}

//�f�X�g���N�^
Frame::~Frame()
{
}

//������
void Frame::Initialize()
{
    Init();
}

//�X�V
void Frame::Update()
{
    //if (Input::IsKey(DIK_W))transform_.position_.y--;
    //if (Input::IsKey(DIK_S))transform_.position_.y++;
    //if (Input::IsKey(DIK_A))transform_.position_.x--;
    //if (Input::IsKey(DIK_D))transform_.position_.x++;
    //if (Input::IsKeyDown(DIK_E))UpdateDrawData();
    if (SystemConfig::IsResized() && mode_ != AUTO_ASPECT) {
        UpdateDrawData();
    }
}

//�`��
void Frame::Draw() {}
//�J��
void Frame::Release() {}

void Frame::DrawFrame()
{
    for (int h = FRAME_H::H_TOP; h < FRAME_H::H_MAX; h++) {
        for (int w = FRAME_W::W_LEFT; w < FRAME_W::W_MAX; w++) {
            Image::SetRect(hImgFrame_, w * grid_, h * grid_, grid_, grid_);
            Image::SetTransform(hImgFrame_, tra[h][w]);
            Image::Draw(hImgFrame_);
        }
    }
}

void Frame::ChangeTheme(std::string _filePath, int _grid)
{
    filePath_ = _filePath;
    grid_ = _grid;
    Init();
}

void Frame::ChangeMode(MODE _mode, int value1, int value2, int value3, int value4)
{
    mode_ = _mode;

    switch (_mode)
    {
    case Frame::AUTO_ASPECT:
        ChangeMode(_mode, (float)value1, (float)value2,(float)value3,(float)value4);
        return;

    case Frame::CONST_MARGIN:
        mUp = value1;
        mRight = value2;
        mDown = value3;
        mLeft = value4;
        break;

    case Frame::CONST_SIZE:
        sWidth = value1;
        sHeight = value2;
        break;
    }

    UpdateDrawData();
}

void Frame::ChangeMode(MODE _mode, float xRatio, float yRatio, float posX, float posY)
{
    mode_ = _mode;

    switch (_mode)
    {
    case Frame::AUTO_ASPECT:
        transform_.scale_.x = xRatio;
        transform_.scale_.y = yRatio;
        transform_.position_.x = posX;
        transform_.position_.y = posY;
        break;

    case Frame::CONST_MARGIN:
    case Frame::CONST_SIZE:
        ChangeMode(_mode, (int)xRatio, (int)yRatio, (int)posX, (int)posY);
        return;
    }

    UpdateDrawData();
}

void Frame::Init()
{
    hImgFrame_ = Image::Load(filePath_);
    UpdateDrawData();
}

void Frame::UpdateDrawData()
{
    const int DEFAULT_SCALE = 1;
    using namespace SystemConfig;
    XMINT2 stdWindowSize = Image::GetStdWindowSize(hImgFrame_);

    switch (mode_)
    {
    case Frame::AUTO_ASPECT:
        

        /*
        AB-2C=D 1280*0.5-64*2=512 D=resize
        E=D/2+C/2 =288
        E=AB/2-C/2 = 1280*0.5/2-32=288
        
        //3x3�������Ă��邽�ߒP���ɉ�ʃT�C�Y�ύX�ɔ����������̊g�嗦�ύX���s�����...
        //�������΂��̊g�嗦=(��ʃT�C�Y*�N���X�g�嗦-2*�O���b�h)/�O���b�h
        */ 
        //frame�\�z

        for (int y = FRAME_H::H_TOP; y < FRAME_H::H_MAX; y++) {

            for (int x = FRAME_W::W_LEFT; x < FRAME_W::W_MAX; x++) {
                switch (y) {
                case FRAME_H::H_TOP:
                    tra[y][x].position_.y = -Half(stdWindowSize.y * transform_.scale_.y - grid_) + transform_.position_.y;
                    tra[y][x].scale_.y = DEFAULT_SCALE;
                    break;
                case FRAME_H::H_CENTER:
                    tra[y][x].position_.y = transform_.position_.y;
                    tra[y][x].scale_.y = (stdWindowSize.y *transform_.scale_.y - grid_ - grid_) / (float)grid_;
                    break;
                case FRAME_H::H_BOTTOM:
                    tra[y][x].position_.y = Half(stdWindowSize.y * transform_.scale_.y - grid_) + transform_.position_.y;
                    tra[y][x].scale_.y = DEFAULT_SCALE;
                    break;
                }

                switch (x) {
                case FRAME_W::W_LEFT:
                    tra[y][x].position_.x = -Half(stdWindowSize.x * transform_.scale_.x - grid_) + transform_.position_.x;
                    tra[y][x].scale_.x = DEFAULT_SCALE;
                    break;
                case FRAME_W::W_CENTER:
                    tra[y][x].position_.x = transform_.position_.x;
                    tra[y][x].scale_.x = (stdWindowSize.x * transform_.scale_.x - grid_ - grid_) / (float)grid_;
                    break;
                case FRAME_W::W_RIGHT:
                    tra[y][x].position_.x = Half(stdWindowSize.x * transform_.scale_.x - grid_) + transform_.position_.x;
                    tra[y][x].scale_.x = DEFAULT_SCALE;
                    break;
                }
            }
        }
        break;
    case Frame::CONST_MARGIN:

        //frame�\�z
        for (int y = FRAME_H::H_TOP; y < FRAME_H::H_MAX; y++) {

            for (int x = FRAME_W::W_LEFT; x < FRAME_W::W_MAX; x++) {
                switch (y) {
                case FRAME_H::H_TOP:
                    tra[y][x].position_.y = mUp + Half(-windowHeight + grid_);
                    tra[y][x].scale_.y = DEFAULT_SCALE;
                    break;
                case FRAME_H::H_CENTER:
                    tra[y][x].position_.y = Half(mUp - mDown);
                    tra[y][x].scale_.y = (float)(windowHeight - (mUp + mDown + grid_ + grid_)) / (float)grid_;
                    break;
                case FRAME_H::H_BOTTOM:
                    tra[y][x].position_.y = -mDown + Half(windowHeight - grid_);
                    tra[y][x].scale_.y = DEFAULT_SCALE;
                    break;
                }

                switch (x) {
                case FRAME_W::W_LEFT:
                    tra[y][x].position_.x = mLeft + Half(-windowWidth + grid_);
                    tra[y][x].scale_.x = DEFAULT_SCALE;
                    break;
                case FRAME_W::W_CENTER:
                    tra[y][x].position_.x = Half(mLeft - mRight);
                    tra[y][x].scale_.x = (float)(windowWidth - (mRight + mLeft + grid_ + grid_)) / (float)grid_;
                    break;
                case FRAME_W::W_RIGHT:
                    tra[y][x].position_.x = -mRight + Half(windowWidth - grid_);
                    tra[y][x].scale_.x = DEFAULT_SCALE;
                    break;
                }

                //��ʃT�C�Y�ύX�ɑΉ����邽�߂̕ϊ����� ���݉�ʃT�C�Y/��T�C�Y������
                tra[y][x].position_.x /= ((float)SystemConfig::windowWidth / (float)stdWindowSize.x);
                tra[y][x].position_.y /= ((float)SystemConfig::windowHeight / (float)stdWindowSize.y);
                tra[y][x].scale_.x /= ((float)SystemConfig::windowWidth / (float)stdWindowSize.x);
                tra[y][x].scale_.y /= ((float)SystemConfig::windowHeight / (float)stdWindowSize.y);

            }
        }
        break;

    case Frame::CONST_SIZE:

        break;
    }
}
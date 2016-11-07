/*****************************************************************************/
/*!
@file   TitleScene.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "../Framework/Manager.h"
#include "TitleScene.h"
#include "../Game/GameScene.h"


using namespace Framework;
using namespace Framework::Input;
using namespace Game;


/*  �ÓI�ϐ��錾
******************************************************************************/


TitleCamera*                Game::TitleScene::pCamera;
Framework::Sprite*          Game::TitleScene::pSprite;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

TitleScene::TitleScene()
{
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

TitleScene::~TitleScene()
{
}

/******************************************************************************
@brief  ������
******************************************************************************/

void TitleScene::Init(void)
{

    pCamera = new TitleCamera;
    Manager::GetRenderer()->SetCamera(pCamera);

    pSprite = Sprite::Create(
        // ���W
        Vector2((float)Manager::GetWindow()->GetWidth()/2, (float)Manager::GetWindow()->GetHeight()/2),
        // �T�C�Y
        Vector2((float)Manager::GetWindow()->GetWidth(), (float)Manager::GetWindow()->GetHeight()),
        // �F
        Color(255, 255, 255, 255),
        // ���W
        "data/TEXTURE/Title/jk_kick.bmp"
        );

    Manager::GetSound()->Play("BGM1", true);
    Manager::GetDebug()->Add("Title");
}

/******************************************************************************
@brief  �I������
******************************************************************************/

void TitleScene::Uninit(void)
{
    SAFE_DELETE(pCamera);
    SAFE_DELETE(pSprite);
    Manager::GetSound()->Stop();
    Manager::GetDebug()->Delete("Title");
}

/******************************************************************************
@brief  �X�V����
******************************************************************************/

void TitleScene::Update(void)
{
    //pCamera->Update();
    if (Manager::GetKeyboard()->Trigger('9'))
    {
        GameScene *pGameScene = new GameScene;
        Manager::SetFade(Fade::FADE_OUT, pGameScene);
    }
}

/******************************** ���������܂� *******************************/

/*****************************************************************************/
/*!
@file   TitleScene.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "../Framework/Manager.h"
#include "TitleScene.h"
#include "../Game/GameScene.h"


using namespace Framework;
using namespace Framework::Input;
using namespace Game;


/*  静的変数宣言
******************************************************************************/


TitleCamera*                Game::TitleScene::pCamera;
Framework::Sprite*          Game::TitleScene::pSprite;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/

TitleScene::TitleScene()
{
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

TitleScene::~TitleScene()
{
}

/******************************************************************************
@brief  初期化
******************************************************************************/

void TitleScene::Init(void)
{

    pCamera = new TitleCamera;
    Manager::GetRenderer()->SetCamera(pCamera);

    pSprite = Sprite::Create(
        // 座標
        Vector2((float)Manager::GetWindow()->GetWidth()/2, (float)Manager::GetWindow()->GetHeight()/2),
        // サイズ
        Vector2((float)Manager::GetWindow()->GetWidth(), (float)Manager::GetWindow()->GetHeight()),
        // 色
        Color(255, 255, 255, 255),
        // 座標
        "data/TEXTURE/Title/jk_kick.bmp"
        );

    Manager::GetSound()->Play("BGM1", true);
    Manager::GetDebug()->Add("Title");
}

/******************************************************************************
@brief  終了処理
******************************************************************************/

void TitleScene::Uninit(void)
{
    SAFE_DELETE(pCamera);
    SAFE_DELETE(pSprite);
    Manager::GetSound()->Stop();
    Manager::GetDebug()->Delete("Title");
}

/******************************************************************************
@brief  更新処理
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

/******************************** 実装ここまで *******************************/

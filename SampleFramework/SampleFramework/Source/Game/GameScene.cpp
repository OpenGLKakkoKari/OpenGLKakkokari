/*****************************************************************************/
/*!
@file   GameScene.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "GameScene.h"
#include "GameCamera.h"
#include "Character/Player.h"
#include "Character/Computer.h"
#include "MeshField.h"
#include "Plant.h"
#include "../Title/TitleScene.h"
#include "../Framework/Manager.h"
#include "../Framework/File/Reader/EffectReader.h"
#include "../Framework/File/Reader/TextReader.h"
#include "../Framework/Math/Random.h"
#include "../Framework/Math/Math.h"
#include "../Framework/Sprite.h"
#include "../Framework/Effect/Effect.h"


using namespace Framework;
using namespace Game;
using namespace Framework::File;
using namespace Math;


/*  静的変数宣言
******************************************************************************/


GameCamera*                 Game::GameScene::pCamera;
Character**                 Game::GameScene::pCharacter;
Framework::Stage*           Game::GameScene::pStage;
Framework::Sprite*          Game::GameScene::pBackground;
Framework::Polygon*         Game::GameScene::pPolygon;
Framework::Effect*          Game::GameScene::pEffect;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/

GameScene::GameScene()
{
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

GameScene::~GameScene()
{
}

/******************************************************************************
@brief  初期化
******************************************************************************/

void GameScene::Init(void)
{
    pStage = TextReader::LoadStage("data/SCRIPT/stage1.txt");

    //pMeshfield = new MeshField(16, 16);
    //pGrass = Grass::Create("data/TEXTURE/grass512.png", Vector3(0.0f, 25.0f, 300.0f), Vector2(100.0f, 50.0f));

    pCamera = new GameCamera;
    Manager::GetRenderer()->SetCamera(pCamera);


    pCharacter = new Character*[CHARACTER_MAX];
    pCharacter[0] = new Player;
    pCharacter[1] = new Computer;

    pBackground = Sprite::Create(
        // 座標
        Vector2((float)Manager::GetWindow()->GetWidth() / 16 * 8, (float)Manager::GetWindow()->GetHeight() / 16),
        // 大きさ
        Vector2((float)Manager::GetWindow()->GetWidth() / 4, (float)Manager::GetWindow()->GetHeight() / 8),
        // 色
        Color(255, 255, 255, 255),
        // テクスチャファイル名
        "data/TEXTURE/Game/score_logo.png");

    pPolygon = Polygon::Create(
        Vector3(0.0f, 0.0f, -50.0f),
        Vector2(100.0f, 100.0f),
        Color(255, 0, 0, 255),
        // テクスチャファイル名
        "data/TEXTURE/Game/score_logo.png");
    
    pPolygon->SetType(DrawObject::TYPE_ALPHAMESH);

    pEffect = EffectReader::LoadEffect("data/EFFECT/explosion.effect");
    pEffect->Pause();
    pEffect->SetLoop(true);
    pEffect->SetPosition(Vector3(0.0f, 0.0f, 1000.0f));


    Manager::GetDebug()->Add("Game");
}

/******************************************************************************
@brief  終了処理
******************************************************************************/

void GameScene::Uninit(void)
{
    SAFE_DELETE(pCamera);
    
    for (int i = 0; i < 2; i++)
    {
        SAFE_DELETE(pCharacter[i]);
    }
    SAFE_DELETE_ARRAY(pCharacter);

    SAFE_DELETE(pStage);
    SAFE_DELETE(pBackground);
    SAFE_DELETE(pPolygon);
    SAFE_DELETE(pEffect);
    Manager::GetSound()->Stop();
    Manager::GetDebug()->Delete("Game");
}

/******************************************************************************
@brief  更新処理
******************************************************************************/

void GameScene::Update(void)
{

    if (Manager::GetKeyboard()->Trigger('9'))
    {
        TitleScene *pTitleScene = new TitleScene;
        Manager::SetFade(Fade::FADE_OUT, pTitleScene);
    }
    if (Manager::GetKeyboard()->Trigger('1'))
    {
        pEffect->Play();
    }
}

/******************************** 実装ここまで *******************************/

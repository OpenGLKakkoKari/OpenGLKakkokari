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
#include "MeshField.h"
#include "Plant.h"
#include "Timer.h"
#include "../Title/TitleScene.h"
#include "../Framework/Manager.h"
#include "../Framework/File/Reader/TextReader.h"
#include "../Framework/Math/Random.h"
#include "../Framework/Math/Math.h"
#include "../Framework/Collision/OBB.h"
#include "../Framework/Sprite.h"
#include "Explosion.h"


using namespace Framework;
using namespace Game;
using namespace Framework::File;
using namespace Math;


/*  静的変数宣言
******************************************************************************/


GameCamera*                 Game::GameScene::pCamera;
Player**                    Game::GameScene::pPlayer;
MeshField*                  Game::GameScene::pMeshField;
Timer*                      Game::GameScene::pTimer;
Framework::Stage*           Game::GameScene::pStage;
Framework::Sprite*          Game::GameScene::pBackground;
Framework::Polygon*         Game::GameScene::pPolygon;
Framework::Model*           Game::GameScene::pModel;
Framework::OBB*             Game::GameScene::pOBB;
Explosion*                  Game::GameScene::pExplosion;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/

GameScene::GameScene()
{
    Manager::GetDebug()->Add("Game");
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

GameScene::~GameScene()
{
    Manager::GetDebug()->Delete("Game");
}

/******************************************************************************
@brief  初期化
******************************************************************************/

void GameScene::Init(void)
{
    pStage = TextReader::LoadStage("data/SCRIPT/stage1.txt");

    //pMeshfield = new MeshField(16, 16);
    //pGrass = Grass::Create("data/TEXTURE/grass512.png", Vector3(0.0f, 25.0f, 300.0f), Vector2(100.0f, 50.0f));

	//タイマー
	pTimer = new Timer;
	pTimer->Init();
	
    pPlayer = new Player*[CHARACTER_MAX];
    pPlayer[0] = new Player;
	pPlayer[0]->Init() ;

    pCamera = new GameCamera;
    Manager::GetRenderer()->SetCamera(pCamera);


    pExplosion = new Explosion;
    pExplosion->Init();

    //pMeshField = new MeshField("data/TEXTURE/Field/asphalt001.jpg", 2048, 2048, Vector2(10000.0f, 10000.0f), NULL);

    //pBackground = Sprite::Create(
    //    // 座標
    //    Vector2((float)Manager::GetWindow()->GetWidth() / 16 * 8, (float)Manager::GetWindow()->GetHeight() / 16),
    //    // 大きさ
    //    Vector2((float)Manager::GetWindow()->GetWidth() / 4, (float)Manager::GetWindow()->GetHeight() / 8),
    //    // 色
    //    Color(255, 255, 255, 255),
    //    // テクスチャファイル名
    //    "data/TEXTURE/Field/skydome000.bmp");

    //pPolygon = Polygon::Create(
    //    Vector3(0.0f, 0.0f, -50.0f),
    //    Vector2(100.0f, 100.0f),
    //    Color(255, 0, 0, 255),
    //    // テクスチャファイル名
    //    "data/TEXTURE/Game/score_logo.png");

    //pPolygon->SetType(DrawObject::TYPE_ALPHAMESH);

    //pModel = Model::Load("data/MODEL/skydome.x");
    //pModel->SetPosition(Vector3(100.0f, 0.0f, 100.0f));
    pModel = Model::CreateBox(Vector3(200.0f, 200.0f, 200.0f));
    pModel->SetUse(false);

    //pOBB = OBB::Create(pModel->pMesh, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));



}

/******************************************************************************
@brief  終了処理
******************************************************************************/

void GameScene::Uninit(void)
{
    SAFE_DELETE(pCamera);
    
    for (int i = 0; i < 1; i++)
    {
        SAFE_DELETE(pPlayer[i]);
    }
    SAFE_DELETE_ARRAY(pPlayer);

    SAFE_DELETE(pStage);
    SAFE_DELETE(pBackground);
    SAFE_DELETE(pPolygon);
    SAFE_DELETE(pModel);
    SAFE_DELETE(pOBB);
    SAFE_DELETE(pTimer);
    SAFE_DELETE(pExplosion);
    Manager::GetSound()->Stop();
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

    if (Manager::GetJoystick()->Trigger(Input::Joystick::BUTTON_0))
    {
        Manager::GetSound()->Play("SE1");
    }
    if (Manager::GetJoystick()->Trigger(Input::Joystick::BUTTON_1))
    {
        Manager::GetSound()->Play("SE2");
    }
    if (Manager::GetJoystick()->Trigger(Input::Joystick::BUTTON_2))
    {
        Manager::GetSound()->Play("SE3");
    }
    if (Manager::GetJoystick()->Trigger(Input::Joystick::BUTTON_3))
    {
        Manager::GetSound()->Play("SE4");
    }
    if (Manager::GetJoystick()->Trigger(Input::Joystick::BUTTON_4))
    {
        Manager::GetSound()->Play("SE5");
    }

    if (Manager::GetKeyboard()->Trigger('5'))
    {
        Vector3 playerPos = pPlayer[0]->GetPosition();
        pExplosion->Create(Vector3(playerPos.x, playerPos.y + 100.0f, playerPos.z));
    }
}

/******************************** 実装ここまで *******************************/

/******************************************************************************
/*!
@file   Skybox.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Skybox.h"
#include "GameScene.h"
#include "Character/Player.h"
#include "../Framework/Manager.h"
#include "../Framework/Mesh/Model.h"
#include "../Framework/Math/Math.h"


using namespace Game;
using namespace Framework;
using namespace Framework::Math;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/

Skybox::Skybox() : pBox(NULL)
{
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

Skybox::~Skybox()
{
    SAFE_DELETE(pBox);
}

/******************************************************************************
@brief  初期化処理
******************************************************************************/

void Skybox::Init(void)
{
    pBox = SkyboxModel::Load("data/MODEL/skydome.x");
    //pBox = SkyboxModel::CreateSkybox(Vector3(20000.0f, 20000.0f, 20000.0f));
}

/******************************************************************************
@brief  更新処理
******************************************************************************/

void Skybox::Update(void)
{
    rot_.y += ToRad(0.015f);
    //pBox->SetRotation(rot_);

    Player* pPlayer = reinterpret_cast<Player*>(GameScene::GetCharacter(0));
    Vector3 playerPos = pPlayer->GetPosition();
    pBox->SetPosition(playerPos);
}

/******************************************************************************
@brief  スカイボックス作成
@param  FileName        テクスチャのファイル名
@return Skybox*         生成したスカイボックス
******************************************************************************/

Skybox* Skybox::Create(const char* FileName)
{
    Skybox* pSkybox = new Skybox;
    pSkybox->Init();
    //pSkybox->SetTexture(FileName);
    return pSkybox;
}

/******************************** 実装ここまで *******************************/

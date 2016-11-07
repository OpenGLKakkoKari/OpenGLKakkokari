/*****************************************************************************/
/*!
@file   Computer.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Computer.h"
#include "../../Framework/Manager.h"
#include "../../Framework/StateManager.h"
#include "../../Framework/Collision/OBB.h"
#include "../../Framework/Math/Math.h"
#include "../../Framework/Mesh/SkinMeshModel.h"
#include "../GameScene.h"


using Game::Computer;
using Framework::Model;
using Framework::Vector2;
using Framework::Vector3;
using Framework::Color;
using Framework::Manager;
using namespace Framework;
using namespace Framework::Math;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/

Computer::Computer()
{
    pSkinMeshModel = SkinMeshModel::Load("data/MODEL/jk_master3.model");
    pSkinMeshModel->SetMotion(Motion::WALKING);

    pos_ = Vector3(0.0f, 0.0f, 0.0f);

    pSkinMeshModel->SetFrame(0);
    pSkinMeshModel->SetPosition(pos_);
    pSkinMeshModel->SetRotation(rot_);
    pSkinMeshModel->SetScale(scale_);
    pSkinMeshModel->Update();

    // トゥイーカに登録
    Manager::GetDebug()->Add("Game/Computer");
    Manager::GetDebug()->SetDirectory("Game/Computer");
    Manager::GetDebug()->Add("pos", &pSkinMeshModel->pos_);
    //Manager::GetDebug()->Add("OBBdir", &pOBB->len);
    //Manager::GetDebug()->Add("ModelNum", &pSkinMeshModel->ModelNum);
    //Manager::GetDebug()->Add("MotionNum", &pSkinMeshModel->MotionNum);
    //Manager::GetDebug()->Add("PartsNum", &pSkinMeshModel->PartsNum);
    //Manager::GetDebug()->Add("ActiveMotionIndex", &pSkinMeshModel->ActiveMotionIndex);

}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

Computer::~Computer()
{
}

/******************************************************************************
@brief  更新処理
******************************************************************************/

void Computer::Update(void)
{
    pos_.z -= 0.1f;

    pSkinMeshModel->SetPosition(pos_);
    pSkinMeshModel->SetRotation(rot_);
    pSkinMeshModel->SetScale(scale_);

    //pSkinMeshModel->NextFrame();
    //pSkinMeshModel->Update();
}

/******************************** 実装ここまで *******************************/

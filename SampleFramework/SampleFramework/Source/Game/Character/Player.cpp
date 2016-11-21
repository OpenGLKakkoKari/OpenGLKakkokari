/*****************************************************************************/
/*!
@file   Player.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Player.h"
#include "CharacterStateManager.h"
#include "CharacterStateNeutral.h"
#include "../GameCamera.h"
#include "../../Framework/Manager.h"
#include "../../Framework/Collision/OBB.h"
#include "../../Framework/Math/Math.h"
#include "../../Framework/Mesh/SkinMeshModel.h"
#include "../GameScene.h"


using Game::Player;
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

Player::Player()
{
    pSkinMeshModel_ = SkinMeshModel::Load("data/MODEL/jk_master3.model");
    pSkinMeshModel_->SetMotion(1);
    pOBB_ = OBB::Create(pSkinMeshModel_->pMesh, pos_, rot_);
    pState_ = new CharacterStateManager;
    pState_->SetState(new CharacterStateNeutral(this));

    pos_.x = 0.0f;
    pos_.y = 50.0f;
    pos_.z = -200.0f;

    traVec = Vector3(0.0f, 0.0f, 0.0f);
    rotVec = Vector3(0.0f, 0.0f, 0.0f);
    rotAim = Vector3(0.0f, 0.0f, 0.0f);
    traUnit = Vector3(1.5f, 1.5f, 1.5f);
    rotUnit = Vector3(0.03f, 0.03f, 0.03f);
    traIner = Vector3(0.1f, 0.1f, 0.1f);
    rotIner = Vector3(0.9f, 0.9f, 0.9f);

    pSkinMeshModel_->pMotionList[Motion::NEUTRAL].loop = true;
    pSkinMeshModel_->pMotionList[Motion::WALKING].loop = true;
    pSkinMeshModel_->pMotionList[Motion::JUMPING].loop = false;
    pSkinMeshModel_->pMotionList[Motion::LANDING].loop = false;
    pSkinMeshModel_->pMotionList[Motion::MELEE].loop = false;

    pSkinMeshModel_->SetMotion(Motion::NEUTRAL);
    pSkinMeshModel_->SetFrame(0);
    pSkinMeshModel_->SetPosition(pos_);
    pSkinMeshModel_->SetRotation(rot_);
    pSkinMeshModel_->SetScale(scale_);
    pSkinMeshModel_->Update();

    // トゥイーカに登録
    Manager::GetDebug()->Add("Game/Player");
    Manager::GetDebug()->SetDirectory("Game/Player");
    Manager::GetDebug()->Add("pos", &pSkinMeshModel_->pos_);
    //Manager::GetDebug()->Add("OBBdir", &pOBB->len);
    //Manager::GetDebug()->Add("ModelNum", &pSkinMeshModel->ModelNum);
    //Manager::GetDebug()->Add("MotionNum", &pSkinMeshModel->MotionNum);
    //Manager::GetDebug()->Add("PartsNum", &pSkinMeshModel->PartsNum);
    //Manager::GetDebug()->Add("ActiveMotionIndex", &pSkinMeshModel->ActiveMotionIndex);

}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

Player::~Player()
{
    SAFE_DELETE(pState_)
}

/******************************************************************************
@brief  更新処理
******************************************************************************/

void Player::Update(void)
{
    Vector3 cameraRot = GameScene::GetCamera()->GetRotation();
    float unit = 5.0f;
    if (Manager::GetKeyboard()->Press('Q'))
    {
        unit = 1.0f;
    }

    if (pState_)
    {
        pState_->Update();
    }

    if (Manager::GetKeyboard()->Press('A') &&
        Manager::GetKeyboard()->Press('W'))
    { // 左上移動
        rotAim.y = cameraRot.y + -0.2f;
        traVec.x -= sinf(rotAim.y) * unit;
        traVec.z -= cosf(rotAim.y) * unit;
    }
    else if (Manager::GetKeyboard()->Press('D') &&
        Manager::GetKeyboard()->Press('W'))
    { // 右上移動
        rotAim.y = cameraRot.y + 0.2f;
        traVec.x -= sinf(rotAim.y) * unit;
        traVec.z -= cosf(rotAim.y) * unit;
    }
    else if (Manager::GetKeyboard()->Press('A') &&
        Manager::GetKeyboard()->Press('S'))
    { // 左下移動
        rotAim.y = cameraRot.y + -_PI / 4 * 3;
        traVec.x -= sinf(rotAim.y) * unit;
        traVec.z -= cosf(rotAim.y) * unit;
    }
    else if (Manager::GetKeyboard()->Press('D') &&
        Manager::GetKeyboard()->Press('S'))
    { // 右下移動
        rotAim.y = cameraRot.y + _PI / 4 * 3;
        traVec.x -= sinf(rotAim.y) * unit;
        traVec.z -= cosf(rotAim.y) * unit;
    }
    else if (Manager::GetKeyboard()->Press('W'))
    { // 上移動
        rotAim.y = cameraRot.y;
        traVec.x -= sinf(rotAim.y) * unit;
        traVec.z -= cosf(rotAim.y) * unit;
    }
    else if (Manager::GetKeyboard()->Press('S'))
    { // 下移動
        rotAim.y = cameraRot.y;
        traVec.x += sinf(rotAim.y) * unit;
        traVec.z += cosf(rotAim.y) * unit;
    }
    else if (Manager::GetKeyboard()->Press('A'))
    { // 左移動
        rotAim.y = cameraRot.y - 0.2f;
    }
    else if (Manager::GetKeyboard()->Press('D'))
    { // 右移動
        rotAim.y = cameraRot.y + 0.2f;
    }

    pos_.x += traVec.x;
    pos_.y += traVec.y;
    pos_.z += traVec.z;

    traVec.x += -traVec.x * traIner.x;
    traVec.z += -traVec.z * traIner.z;

    rotVec.y = rotAim.y - rot_.y;

    if (rotVec.y > _PI)
        rotVec.y -= _2PI;
    else if (rotVec.y < -_PI)
        rotVec.y += _2PI;

    rotVec.y += -rotVec.y * rotIner.y;
    rot_.y += rotVec.y;


    // 座標を範囲内に収める
    if (pos_.y <= 0.0f)
    {
        traVec.y = 0.0f;
    }
    pos_ = Vector3(
        Range<float>::Clamp(pos_.x, -3000.0f, 3000.0f),
        Range<float>::Clamp(pos_.y,     0.0f, 3000.0f),
        Range<float>::Clamp(pos_.z, -3000.0f, 3000.0f)
        );

    NormalizeRadian(&rot_.y);
    NormalizeRadian(&rotAim.y);

    // モデルの更新

    pSkinMeshModel_->SetPosition(pos_);
    pSkinMeshModel_->SetRotation(rot_);
    pSkinMeshModel_->SetScale(scale_);

    pSkinMeshModel_->NextFrame();
    pSkinMeshModel_->Update();

    // OBBの更新
    pOBB_->UpdateLength(pSkinMeshModel_->pMesh->pVertex, pSkinMeshModel_->pMesh->vertexNum);
    pOBB_->pos = pos_;
    pOBB_->pBox->SetPosition(pos_);
    pOBB_->pBox->SetRotation(rot_);

    Manager::GetDebug()->Print("ActiveMotionIndex : %d\n", pSkinMeshModel_->activeMotionIndex);
    Manager::GetDebug()->Print("frame : %d\n", pSkinMeshModel_->pMotionList[pSkinMeshModel_->activeMotionIndex].frame);
    //Manager::GetDebug()->Print("frameMax : %d\n", pSkinMeshModel->MotionList[pSkinMeshModel->ActiveMotionIndex].frameMax);
}

/******************************** 実装ここまで *******************************/

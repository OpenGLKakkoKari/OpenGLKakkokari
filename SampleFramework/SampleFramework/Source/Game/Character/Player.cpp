/*****************************************************************************/
/*!
@file   Player.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Player.h"
#include "../GameCamera.h"
#include "../../Framework/Manager.h"
#include "../../Framework/StateManager.h"
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
    pSkinMeshModel = SkinMeshModel::Load("data/MODEL/jk_master3.model");
    pSkinMeshModel->SetMotion(1);
    pOBB = OBB::Create(pSkinMeshModel->pMesh, pos_, rot_);

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

    pSkinMeshModel->pMotionList[Motion::NEUTRAL].loop = true;
    pSkinMeshModel->pMotionList[Motion::WALKING].loop = true;
    pSkinMeshModel->pMotionList[Motion::JUMPING].loop = false;
    pSkinMeshModel->pMotionList[Motion::LANDING].loop = false;
    pSkinMeshModel->pMotionList[Motion::KICK].loop = false;

    pSkinMeshModel->SetMotion(Motion::NEUTRAL);
    pSkinMeshModel->SetFrame(0);
    pSkinMeshModel->SetPosition(pos_);
    pSkinMeshModel->SetRotation(rot_);
    pSkinMeshModel->SetScale(scale_);
    pSkinMeshModel->Update();

    // トゥイーカに登録
    Manager::GetDebug()->Add("Game/Player");
    Manager::GetDebug()->SetDirectory("Game/Player");
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

Player::~Player()
{
}

/******************************************************************************
@brief  更新処理
******************************************************************************/

void Player::Update(void)
{
    Vector3 cameraRot = GameScene::GetCamera()->GetRotation();
    static bool onGOld = false;
    float unit = 1.0f;



    // 接地しているかどうか
    if (pos_.y <= 0.0f)
        onGround = true;
    else
        onGround = false;

    // 重力
    traVec.y -= 0.5f;

    if (pState)
    {
        pState->Update();
    }

    // キック
    if (onGround && Manager::GetKeyboard()->Trigger(VK_RETURN) && !action)
    {
        action = true;
        pSkinMeshModel->SetMotion(Motion::KICK);
        pSkinMeshModel->SetFrame(0);
    }
    if (pSkinMeshModel->activeMotionIndex == Motion::KICK &&
        pSkinMeshModel->pMotionList[Motion::KICK].frame >= pSkinMeshModel->pMotionList[Motion::KICK].frameMax - 1)
    {
        action = false;
        pSkinMeshModel->SetMotion(Motion::NEUTRAL);
        pSkinMeshModel->SetFrame(0);
    }
    if (!action)
    {
        // 着地したかどうか
        if (onGround && !onGOld)
        {
            pSkinMeshModel->SetMotion(Motion::LANDING);
            pSkinMeshModel->SetFrame(0);
        }
        // ジャンプ
        else if (onGround && Manager::GetKeyboard()->Press(VK_SPACE))
        {
            traVec.y += 20.0f;
            pSkinMeshModel->SetMotion(Motion::JUMPING);
            pSkinMeshModel->SetFrame(0);
        }
        // 歩き
        else if ((Manager::GetKeyboard()->Press('W') ||
            Manager::GetKeyboard()->Press('S') ||
            Manager::GetKeyboard()->Press('A') ||
            Manager::GetKeyboard()->Press('D')) &&
            pSkinMeshModel->activeMotionIndex != Motion::JUMPING
            )
        {
            if (pSkinMeshModel->activeMotionIndex == Motion::NEUTRAL)
            {
                pSkinMeshModel->SetMotion(Motion::WALKING);
                pSkinMeshModel->SetFrame(0);
            }
            else
            {
                pSkinMeshModel->SetMotion(Motion::WALKING);
            }
        }
        // 着地が終わったらニュートラル
        else if (pSkinMeshModel->activeMotionIndex == Motion::LANDING &&
                 pSkinMeshModel->pMotionList[Motion::LANDING].frame >= pSkinMeshModel->pMotionList[Motion::LANDING].frameMax - 1)
        {
            pSkinMeshModel->SetMotion(Motion::NEUTRAL);
        }

        // ニュートラル
        else if (pSkinMeshModel->activeMotionIndex != Motion::LANDING && pSkinMeshModel->activeMotionIndex != Motion::JUMPING)
        {
            pSkinMeshModel->SetMotion(Motion::NEUTRAL);
        }

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
    //traVec.y += -traVec.y * traIner.y;
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
        pos_.y = 0.0f;
    }
    if (pos_.x < -3000.0f)
        pos_.x = -3000.0f;
    if (pos_.x > 3000.0f)
        pos_.x = 3000.0f;
    if (pos_.z < -3000.0f)
        pos_.z = -3000.0f;
    if (pos_.z > 3000.0f)
        pos_.z = 3000.0f;

    // 角度を範囲内に収める
    if (rot_.y > _PI)
    {      
        rot_.y -= _PI * 2;
    }      
    if (rot_.y < -_PI)
    {      
        rot_.y += _PI * 2;
    }
    if (rotAim.y > _PI)
    {
        rotAim.y -= _PI * 2;
    }
    if (rotAim.y < -_PI)
    {
        rotAim.y += _PI * 2;
    }

    pSkinMeshModel->SetPosition(pos_);
    pSkinMeshModel->SetRotation(rot_);
    pSkinMeshModel->SetScale(scale_);

    pSkinMeshModel->NextFrame();
    pSkinMeshModel->Update();

    onGOld = onGround;

    // OBBの更新
    pOBB->pos = pos_;
    pOBB->UpdateLength(pSkinMeshModel->pMesh->pVertex, pSkinMeshModel->pMesh->vertexNum);

    Manager::GetDebug()->Print("ActiveMotionIndex : %d\n", pSkinMeshModel->activeMotionIndex);
    Manager::GetDebug()->Print("frame : %d\n", pSkinMeshModel->pMotionList[pSkinMeshModel->activeMotionIndex].frame);
    //Manager::GetDebug()->Print("frameMax : %d\n", pSkinMeshModel->MotionList[pSkinMeshModel->ActiveMotionIndex].frameMax);
}

/******************************** 実装ここまで *******************************/

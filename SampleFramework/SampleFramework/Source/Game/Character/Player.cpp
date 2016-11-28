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
#include "../../Framework/Math/Math.h"
#include "../GameScene.h"


using namespace Game;
using namespace Framework;
using namespace Framework::Math;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/

Player::Player()
{
    pModel_ = Model::Load("data/MODEL/hajime.x");

    // トゥイーカに登録
    //Manager::GetDebug()->Add("Game/Player");
    //Manager::GetDebug()->SetDirectory("Game/Player");
    //Manager::GetDebug()->Add("pos", &pSkinMeshModel_->pos_);
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
	SAFE_DELETE(pModel_)
}

/******************************************************************************
@brief  更新処理
******************************************************************************/

void Player::Update(void)
{
//試作
	//カメラの角度を受け取り
    Vector3 cameraRot = GameScene::GetCamera()->GetRotation();
<<<<<<< HEAD

	float unit = 5.0f;

	if (Manager::GetKeyboard()->Press('Q'))
    {
        unit = 1.0f;
    }

    if (pState_)
    {
        pState_->Update();
    }
=======
	const float MODEL_MOVE = 3.0f;
>>>>>>> 45a17be7d208e8618ed49dd142766dee4a7bcbfe

    if (Manager::GetKeyboard()->Press('A') &&
        Manager::GetKeyboard()->Press('W'))
    { // 左上移動
		
		pos_.x -= sinf( _PI / 4 + cameraRot.y ) * MODEL_MOVE ;
		pos_.z += cosf( _PI / 4 + cameraRot.y ) * MODEL_MOVE ;
    }
    else if (Manager::GetKeyboard()->Press('D') &&
        Manager::GetKeyboard()->Press('W'))
    { // 右上移動
		pos_.x += sinf( ( _PI / 4 ) * 3 + cameraRot.y ) * MODEL_MOVE ;
		pos_.z -= cosf( ( _PI / 4 ) * 3 + cameraRot.y ) * MODEL_MOVE ;
    }
    else if (Manager::GetKeyboard()->Press('A') &&
        Manager::GetKeyboard()->Press('S'))
    { // 左下移動
		pos_.x -= sinf( ( _PI / 4 ) * 3 + cameraRot.y ) * MODEL_MOVE ;
		pos_.z += cosf( ( _PI / 4 ) * 3 + cameraRot.y ) * MODEL_MOVE ;
    }
    else if (Manager::GetKeyboard()->Press('D') &&
        Manager::GetKeyboard()->Press('S'))
    { // 右下移動
		pos_.x += sinf( _PI / 4 + cameraRot.y ) * MODEL_MOVE ;
		pos_.z -= cosf( _PI / 4 + cameraRot.y ) * MODEL_MOVE ;
    }
    else if (Manager::GetKeyboard()->Press('W'))
    { // 上移動
		pos_.x += sinf( _PI + cameraRot.y ) * MODEL_MOVE ;
		pos_.z -= cosf( _PI + cameraRot.y ) * MODEL_MOVE ;
    }
    else if (Manager::GetKeyboard()->Press('S'))
    { // 下移動
		pos_.x -= sinf( _PI + cameraRot.y ) * MODEL_MOVE ;
		pos_.z += cosf( _PI + cameraRot.y ) * MODEL_MOVE ;
    }
    else if (Manager::GetKeyboard()->Press('A'))
    { // 左移動
		pos_.x -= sinf( _PI / 2 + cameraRot.y ) * MODEL_MOVE ;
		pos_.z += cosf( _PI / 2 + cameraRot.y ) * MODEL_MOVE ;
    }
    else if (Manager::GetKeyboard()->Press('D'))
    { // 右移動
		pos_.x += sinf( _PI / 2 + cameraRot.y ) * MODEL_MOVE ;
		pos_.z -= cosf( _PI / 2 + cameraRot.y ) * MODEL_MOVE ;
    }



	Manager::GetDebug()->Print("cameraRot : %f\n", cameraRot.y);
    //pos_.x += traVec.x;
    //pos_.y += traVec.y;
    //pos_.z += traVec.z;

    //traVec.x += -traVec.x * traIner.x;
    //traVec.z += -traVec.z * traIner.z;

    //rotVec.y = rotAim.y - rot_.y;

    //if (rotVec.y > _PI)
    //    rotVec.y -= _2PI;
    //else if (rotVec.y < -_PI)
    //    rotVec.y += _2PI;

    //rotVec.y += -rotVec.y * rotIner.y;
    //rot_.y += rotVec.y;
//
//    NormalizeRadian(&rot_.y);
//    NormalizeRadian(&rotAim.y);
//

    pos_ = Vector3(
        Range<float>::Clamp(pos_.x, -3000.0f, 3000.0f),
        Range<float>::Clamp(pos_.y,     0.0f, 3000.0f),
        Range<float>::Clamp(pos_.z, -3000.0f, 3000.0f)
        );
    // モデルの更新
    pModel_->SetPosition(pos_);
    pModel_->SetRotation(rot_);
    pModel_->SetScale(scale_);

<<<<<<< HEAD
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

//ベース
	////カメラの角度を受け取り
 //   Vector3 cameraRot = GameScene::GetCamera()->GetRotation();
	//float unit = 5.0f;

	//if (Manager::GetKeyboard()->Press('Q'))
 //   {
 //       unit = 1.0f;
 //   }

 //   if (pState_)
 //   {
 //       pState_->Update();
 //   }

 //   if (Manager::GetKeyboard()->Press('A') &&
 //       Manager::GetKeyboard()->Press('W'))
 //   { // 左上移動
 //       rotAim.y = cameraRot.y + -0.2f;
 //       traVec.x -= sinf(rotAim.y) * unit;
 //       traVec.z -= cosf(rotAim.y) * unit;
 //   }
 //   else if (Manager::GetKeyboard()->Press('D') &&
 //       Manager::GetKeyboard()->Press('W'))
 //   { // 右上移動
 //       rotAim.y = cameraRot.y + 0.2f;
 //       traVec.x -= sinf(rotAim.y) * unit;
 //       traVec.z -= cosf(rotAim.y) * unit;
 //   }
 //   else if (Manager::GetKeyboard()->Press('A') &&
 //       Manager::GetKeyboard()->Press('S'))
 //   { // 左下移動
 //       rotAim.y = cameraRot.y + -_PI / 4 * 3;
 //       traVec.x -= sinf(rotAim.y) * unit;
 //       traVec.z -= cosf(rotAim.y) * unit;
 //   }
 //   else if (Manager::GetKeyboard()->Press('D') &&
 //       Manager::GetKeyboard()->Press('S'))
 //   { // 右下移動
 //       rotAim.y = cameraRot.y + _PI / 4 * 3;
 //       traVec.x -= sinf(rotAim.y) * unit;
 //       traVec.z -= cosf(rotAim.y) * unit;
 //   }
 //   else if (Manager::GetKeyboard()->Press('W'))
 //   { // 上移動
 //       rotAim.y = cameraRot.y;
 //       traVec.x -= sinf(rotAim.y) * unit;
 //       traVec.z -= cosf(rotAim.y) * unit;
 //   }
 //   else if (Manager::GetKeyboard()->Press('S'))
 //   { // 下移動
 //       rotAim.y = cameraRot.y;
 //       traVec.x += sinf(rotAim.y) * unit;
 //       traVec.z += cosf(rotAim.y) * unit;
 //   }
 //   else if (Manager::GetKeyboard()->Press('A'))
 //   { // 左移動
 //       rotAim.y = cameraRot.y - 0.2f;
 //   }
 //   else if (Manager::GetKeyboard()->Press('D'))
 //   { // 右移動
 //       rotAim.y = cameraRot.y + 0.2f;
 //   }

 //   pos_.x += traVec.x;
 //   pos_.y += traVec.y;
 //   pos_.z += traVec.z;

 //   traVec.x += -traVec.x * traIner.x;
 //   traVec.z += -traVec.z * traIner.z;

 //   rotVec.y = rotAim.y - rot_.y;

 //   if (rotVec.y > _PI)
 //       rotVec.y -= _2PI;
 //   else if (rotVec.y < -_PI)
 //       rotVec.y += _2PI;

 //   rotVec.y += -rotVec.y * rotIner.y;
 //   rot_.y += rotVec.y;


 //   // 座標を範囲内に収める
 //   if (pos_.y <= 0.0f)
 //   {
 //       traVec.y = 0.0f;
 //   }
 //   pos_ = Vector3(
 //       Range<float>::Clamp(pos_.x, -3000.0f, 3000.0f),
 //       Range<float>::Clamp(pos_.y,     0.0f, 3000.0f),
 //       Range<float>::Clamp(pos_.z, -3000.0f, 3000.0f)
 //       );

 //   NormalizeRadian(&rot_.y);
 //   NormalizeRadian(&rotAim.y);

 //   // モデルの更新

 //   pSkinMeshModel_->SetPosition(pos_);
 //   pSkinMeshModel_->SetRotation(rot_);
 //   pSkinMeshModel_->SetScale(scale_);

 //   pSkinMeshModel_->NextFrame();
 //   pSkinMeshModel_->Update();

 //   // OBBの更新
 //   pOBB_->UpdateLength(pSkinMeshModel_->pMesh->pVertex, pSkinMeshModel_->pMesh->vertexNum);
 //   pOBB_->pos = pos_;
 //   pOBB_->pBox->SetPosition(pos_);
 //   pOBB_->pBox->SetRotation(rot_);

 //   Manager::GetDebug()->Print("ActiveMotionIndex : %d\n", pSkinMeshModel_->activeMotionIndex);
 //   Manager::GetDebug()->Print("frame : %d\n", pSkinMeshModel_->pMotionList[pSkinMeshModel_->activeMotionIndex].frame);
 //   //Manager::GetDebug()->Print("frameMax : %d\n", pSkinMeshModel->MotionList[pSkinMeshModel->ActiveMotionIndex].frameMax);
=======
>>>>>>> 45a17be7d208e8618ed49dd142766dee4a7bcbfe
}

/******************************** 実装ここまで *******************************/

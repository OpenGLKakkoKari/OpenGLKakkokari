/*****************************************************************************/
/*!
@file   Player.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Player.h"
#include "Player1Controller.h"
#include "Player2Controller.h"
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
	: pModel_(NULL), pOBBPlayer_(NULL), pOBBAttack_(NULL), pController_(NULL)
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
	SAFE_DELETE(pOBBPlayer_)
	SAFE_DELETE(pOBBAttack_)
	SAFE_DELETE(pController_)
}

/******************************************************************************
@brief  更新処理
******************************************************************************/

void Player::Init ( void )
{
	pOBBPlayer_ = OBB::Create ( pModel_ ->pMesh, pos_ , rot_ ) ;
	pOBBAttack_ = OBB::Create ( Vector3(50,50,50), Vector3(pos_.x,pos_.y+100,pos_.z-50) , rot_ ) ;


	//変数初期化
	t_ = 0 ;
	bJump_ = false ;
}

/******************************************************************************
@brief  更新処理
******************************************************************************/

void Player::Update(void)
{
    Vector3 cameraRot = GameScene::GetCamera()->GetRotation();
	const float MODEL_MOVE = 3.0f;	//移動量

	//ジャンプで使う変数
	const float Vo = 50.0f ;		//初速度
	const float gravity = -2.0f ;	//重力

    if (pController_->IsLeft() &&
        pController_->IsUp())
    { // 左上移動
		
		pos_.x -= sinf( _PI / 4 + cameraRot.y ) * MODEL_MOVE ;
		pos_.z += cosf( _PI / 4 + cameraRot.y ) * MODEL_MOVE ;
    }
    else if (pController_->IsRight() &&
        pController_->IsUp())
    { // 右上移動
		pos_.x += sinf( ( _PI / 4 ) * 3 + cameraRot.y ) * MODEL_MOVE ;
		pos_.z -= cosf( ( _PI / 4 ) * 3 + cameraRot.y ) * MODEL_MOVE ;
    }
	else if (pController_->IsLeft() &&
        pController_->IsDown())
    { // 左下移動
		pos_.x -= sinf( ( _PI / 4 ) * 3 + cameraRot.y ) * MODEL_MOVE ;
		pos_.z += cosf( ( _PI / 4 ) * 3 + cameraRot.y ) * MODEL_MOVE ;
    }
    else if (pController_->IsRight() &&
        pController_->IsDown())
    { // 右下移動
		pos_.x += sinf( _PI / 4 + cameraRot.y ) * MODEL_MOVE ;
		pos_.z -= cosf( _PI / 4 + cameraRot.y ) * MODEL_MOVE ;
    }
    else if (pController_->IsUp())
    { // 上移動
		pos_.x += sinf( _PI + cameraRot.y ) * MODEL_MOVE ;
		pos_.z -= cosf( _PI + cameraRot.y ) * MODEL_MOVE ;
    }
    else if (pController_->IsDown())
    { // 下移動
		pos_.x -= sinf( _PI + cameraRot.y ) * MODEL_MOVE ;
		pos_.z += cosf( _PI + cameraRot.y ) * MODEL_MOVE ;
    }
    else if (pController_->IsLeft())
    { // 左移動
		pos_.x -= sinf( _PI / 2 + cameraRot.y ) * MODEL_MOVE ;
		pos_.z += cosf( _PI / 2 + cameraRot.y ) * MODEL_MOVE ;
    }
	else if (pController_->IsRight())
    { // 右移動
		pos_.x += sinf( _PI / 2 + cameraRot.y ) * MODEL_MOVE ;
		pos_.z -= cosf( _PI / 2 + cameraRot.y ) * MODEL_MOVE ;
    }

	//ジャンプ
	if (pController_->IsJump())
	{
		bJump_ = true ;
	}

	//ジャンプ中なら
	if ( bJump_ )
	{
		//速度計算
		float v = Vo + gravity * t_ ;

		pos_.y += v ;

		t_ ++ ;

		//着地したら
		if ( pos_.y <= 0.0f )
		{
			bJump_ = false ;
			t_ = 0 ;
		}
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

	pOBBPlayer_->pos = pos_ ;
	pOBBPlayer_->pBox->SetPosition(pos_);

	pOBBAttack_->pos = Vector3(pos_.x,pos_.y+150,pos_.z-50) ;
	pOBBAttack_->pBox->SetPosition(Vector3(pos_.x,pos_.y+100,pos_.z-50));

}

/******************************************************************************
@brief  更新処理
******************************************************************************/

Player* Player::Create(int index)
{
	Player* pPlayer = new Player;
	pPlayer->Init();
	
	switch(index)
	{
	case 0:		pPlayer->SetController(new Player1Controller);	break;
	case 1:		pPlayer->SetController(new Player2Controller);	break;
	case 2:		pPlayer->SetController(new Player1Controller);	break;
	case 3:		pPlayer->SetController(new Player1Controller);	break;
	default:	break;
	}

	return pPlayer;
}

/******************************** 実装ここまで *******************************/

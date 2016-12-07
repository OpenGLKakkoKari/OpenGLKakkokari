/*****************************************************************************/
/*!
@file   Player.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Player.h"
#include "../GameCamera.h"
#include "../../Framework/Manager.h"
#include "../../Framework/Math/Math.h"
#include "../GameScene.h"


using namespace Game;
using namespace Framework;
using namespace Framework::Math;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

Player::Player()
{
    pModel_ = Model::Load("data/MODEL/hajime.x");

    // �g�D�C�[�J�ɓo�^
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
@brief  �f�X�g���N�^
******************************************************************************/

Player::~Player()
{
	SAFE_DELETE(pModel_)
}

/******************************************************************************
@brief  �X�V����
******************************************************************************/

void Player::Init ( void )
{
	//bJump = false ;
}

/******************************************************************************
@brief  �X�V����
******************************************************************************/

void Player::Update(void)
{
    Vector3 cameraRot = GameScene::GetCamera()->GetRotation();
	const float MODEL_MOVE = 3.0f;	//�ړ���

	//�W�����v�Ŏg���ϐ�
	const float Vo = 50.0f ;		//�����x
	const float gravity = -2.0f ;	//�d��
	static int t = 0 ;				//����
	static bool bJump = false ;		//�W�����v�����ǂ���


    if (Manager::GetKeyboard()->Press('A') &&
        Manager::GetKeyboard()->Press('W'))
    { // ����ړ�
		
		pos_.x -= sinf( _PI / 4 + cameraRot.y ) * MODEL_MOVE ;
		pos_.z += cosf( _PI / 4 + cameraRot.y ) * MODEL_MOVE ;
    }
    else if (Manager::GetKeyboard()->Press('D') &&
        Manager::GetKeyboard()->Press('W'))
    { // �E��ړ�
		pos_.x += sinf( ( _PI / 4 ) * 3 + cameraRot.y ) * MODEL_MOVE ;
		pos_.z -= cosf( ( _PI / 4 ) * 3 + cameraRot.y ) * MODEL_MOVE ;
    }
    else if (Manager::GetKeyboard()->Press('A') &&
        Manager::GetKeyboard()->Press('S'))
    { // �����ړ�
		pos_.x -= sinf( ( _PI / 4 ) * 3 + cameraRot.y ) * MODEL_MOVE ;
		pos_.z += cosf( ( _PI / 4 ) * 3 + cameraRot.y ) * MODEL_MOVE ;
    }
    else if (Manager::GetKeyboard()->Press('D') &&
        Manager::GetKeyboard()->Press('S'))
    { // �E���ړ�
		pos_.x += sinf( _PI / 4 + cameraRot.y ) * MODEL_MOVE ;
		pos_.z -= cosf( _PI / 4 + cameraRot.y ) * MODEL_MOVE ;
    }
    else if (Manager::GetKeyboard()->Press('W'))
    { // ��ړ�
		pos_.x += sinf( _PI + cameraRot.y ) * MODEL_MOVE ;
		pos_.z -= cosf( _PI + cameraRot.y ) * MODEL_MOVE ;
    }
    else if (Manager::GetKeyboard()->Press('S'))
    { // ���ړ�
		pos_.x -= sinf( _PI + cameraRot.y ) * MODEL_MOVE ;
		pos_.z += cosf( _PI + cameraRot.y ) * MODEL_MOVE ;
    }
    else if (Manager::GetKeyboard()->Press('A'))
    { // ���ړ�
		pos_.x -= sinf( _PI / 2 + cameraRot.y ) * MODEL_MOVE ;
		pos_.z += cosf( _PI / 2 + cameraRot.y ) * MODEL_MOVE ;
    }
    else if (Manager::GetKeyboard()->Press('D'))
    { // �E�ړ�
		pos_.x += sinf( _PI / 2 + cameraRot.y ) * MODEL_MOVE ;
		pos_.z -= cosf( _PI / 2 + cameraRot.y ) * MODEL_MOVE ;
    }

	//�W�����v
	if (Manager::GetKeyboard()->Trigger('J'))
	{
		bJump = true ;
	}

	//�W�����v���Ȃ�
	if ( bJump )
	{
		//���x�v�Z
		float v = Vo + gravity * t ;

		pos_.y += v ;

		t ++ ;

		//���n������
		if ( pos_.y <= 0.0f )
		{
			bJump = false ;
			t = 0 ;
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
    // ���f���̍X�V
    pModel_->SetPosition(pos_);
    pModel_->SetRotation(rot_);
    pModel_->SetScale(scale_);

}

/******************************** ���������܂� *******************************/

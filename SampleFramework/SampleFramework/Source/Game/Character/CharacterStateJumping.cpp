/*****************************************************************************/
/*!
@file   CharacterStateJumping.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "CharacterStateJumping.h"
#include "CharacterStateLanding.h"
#include "Player.h"
#include "../GameScene.h"
#include "../../Framework/Manager.h"
#include "../../Framework/Mesh/SkinMeshModel.h"

using namespace Framework;
using namespace Game;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

CharacterStateJumping::CharacterStateJumping(Character* pOwner)
    : CharacterState(pOwner)
{
    name_ = STATE_JUMPING;
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

CharacterStateJumping::~CharacterStateJumping()
{
}

/******************************************************************************
@brief  ����������
******************************************************************************/

void CharacterStateJumping::Init(void)
{
}

/******************************************************************************
@brief  �I������
******************************************************************************/

void CharacterStateJumping::Uninit(void)
{
}

/******************************************************************************
@brief  �X�V����
******************************************************************************/

void CharacterStateJumping::Update(void)
{
    // �d��
    pOwner_->traVec.y -= 0.5f;

    // �ڒn�����璅�n���[�V�����Ɉڍs
    if (pOwner_->IsLanding())
    {
        pOwner_->SetMotion(Motion::LANDING);
        pOwner_->SetState(new CharacterStateLanding(pOwner_));
    }
}

/******************************** ���������܂� *******************************/

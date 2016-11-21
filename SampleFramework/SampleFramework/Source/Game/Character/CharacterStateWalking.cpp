/*****************************************************************************/
/*!
@file   CharacterStateWalking.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "CharacterStateNeutral.h"
#include "CharacterStateMelee.h"
#include "CharacterStateWalking.h"
#include "CharacterStateJumping.h"
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

CharacterStateWalking::CharacterStateWalking(Character* pOwner)
    : CharacterState(pOwner)
{
    name_ = STATE_WALKING;
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

CharacterStateWalking::~CharacterStateWalking()
{
}

/******************************************************************************
@brief  ����������
******************************************************************************/

void CharacterStateWalking::Init(void)
{
}

/******************************************************************************
@brief  �I������
******************************************************************************/

void CharacterStateWalking::Uninit(void)
{
}

/******************************************************************************
@brief  �X�V����
******************************************************************************/

void CharacterStateWalking::Update(void)
{
    // �L�b�N
    if (Manager::GetKeyboard()->Trigger(VK_RETURN))
    {
        pOwner_->SetMotion(Motion::MELEE);
        pOwner_->SetState(new CharacterStateMelee(pOwner_));
    }
    // �W�����v
    else if (Manager::GetKeyboard()->Trigger(VK_SPACE))
    {
        pOwner_->traVec.y += 20.0f;
        pOwner_->SetMotion(Motion::JUMPING);
        pOwner_->SetState(new CharacterStateJumping(pOwner_));
    }

    else if (!Manager::GetKeyboard()->Press('W') &&
        !Manager::GetKeyboard()->Press('S') &&
        !Manager::GetKeyboard()->Press('A') &&
        !Manager::GetKeyboard()->Press('D')
        )
    {
        pOwner_->SetMotion(Motion::NEUTRAL);
        pOwner_->SetState(new CharacterStateNeutral(pOwner_));
    }
}

/******************************** ���������܂� *******************************/

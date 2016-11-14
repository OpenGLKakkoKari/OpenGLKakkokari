/*****************************************************************************/
/*!
@file   CharacterStateNeutral.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "CharacterStateNeutral.h"
#include "CharacterStateMelee.h"
#include "CharacterStateJumping.h"
#include "CharacterStateWalking.h"
#include "../GameScene.h"
#include "Player.h"
#include "../../Framework/Manager.h"

using namespace Framework;
using namespace Game;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

CharacterStateNeutral::CharacterStateNeutral(Character* pOwner)
    : CharacterState(pOwner)
{
    name_ = STATE_NEUTRAL;
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

CharacterStateNeutral::~CharacterStateNeutral()
{
}

/******************************************************************************
@brief  ����������
******************************************************************************/

void CharacterStateNeutral::Init(void)
{
}

/******************************************************************************
@brief  �I������
******************************************************************************/

void CharacterStateNeutral::Uninit(void)
{
}

/******************************************************************************
@brief  �X�V����
******************************************************************************/

void CharacterStateNeutral::Update(void)
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
    // �ړ�
    else if (Manager::GetKeyboard()->Press('W') ||
        Manager::GetKeyboard()->Press('S') ||
        Manager::GetKeyboard()->Press('A') ||
        Manager::GetKeyboard()->Press('D')
        )
    {
        pOwner_->SetMotion(Motion::WALKING);
        pOwner_->SetState(new CharacterStateWalking(pOwner_));
    }
}

/******************************** ���������܂� *******************************/

/*****************************************************************************/
/*!
@file   CharacterStateShooting.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "CharacterStateNeutral.h"
#include "CharacterStateShooting.h"
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

CharacterStateShooting::CharacterStateShooting(Character* pOwner)
    : CharacterState(pOwner)
{
    name_ = STATE_SHOOTING;
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

CharacterStateShooting::~CharacterStateShooting()
{
}

/******************************************************************************
@brief  ����������
******************************************************************************/

void CharacterStateShooting::Init(void)
{
}

/******************************************************************************
@brief  �I������
******************************************************************************/

void CharacterStateShooting::Uninit(void)
{
}

/******************************************************************************
@brief  �X�V����
******************************************************************************/

void CharacterStateShooting::Update(void)
{
    if (pOwner_->IsMotionEnd(Motion::SHOOTING))
    {
        pOwner_->SetMotion(Motion::NEUTRAL);
        pOwner_->SetState(new CharacterStateNeutral(pOwner_));
    }
}

/******************************** ���������܂� *******************************/

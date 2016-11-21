/*****************************************************************************/
/*!
@file   CharacterStateMelee.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "CharacterStateNeutral.h"
#include "CharacterStateMelee.h"
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

CharacterStateMelee::CharacterStateMelee(Character* pOwner)
    : CharacterState(pOwner)
{
    name_ = STATE_MELEE;
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

CharacterStateMelee::~CharacterStateMelee()
{
}

/******************************************************************************
@brief  ����������
******************************************************************************/

void CharacterStateMelee::Init(void)
{
}

/******************************************************************************
@brief  �I������
******************************************************************************/

void CharacterStateMelee::Uninit(void)
{
}

/******************************************************************************
@brief  �X�V����
******************************************************************************/

void CharacterStateMelee::Update(void)
{
    if (pOwner_->IsMotionEnd(Motion::MELEE))
    {
        pOwner_->SetMotion(Motion::NEUTRAL);
        pOwner_->SetState(new CharacterStateNeutral(pOwner_));
    }
}

/******************************** ���������܂� *******************************/

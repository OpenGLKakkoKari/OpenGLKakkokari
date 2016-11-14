/*****************************************************************************/
/*!
@file   CharacterStateLanding.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "CharacterStateLanding.h"
#include "CharacterStateNeutral.h"
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

CharacterStateLanding::CharacterStateLanding(Character* pOwner)
    : CharacterState(pOwner)
{
    name_ = STATE_LANDING;
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

CharacterStateLanding::~CharacterStateLanding()
{
}

/******************************************************************************
@brief  ����������
******************************************************************************/

void CharacterStateLanding::Init(void)
{
}

/******************************************************************************
@brief  �I������
******************************************************************************/

void CharacterStateLanding::Uninit(void)
{
}

/******************************************************************************
@brief  �X�V����
******************************************************************************/

void CharacterStateLanding::Update(void)
{
    if (pOwner_->IsMotionEnd(Motion::LANDING))
    {
        pOwner_->SetMotion(Motion::NEUTRAL);
        pOwner_->SetState(new CharacterStateNeutral(pOwner_));
    }
}

/******************************** ���������܂� *******************************/

/*****************************************************************************/
/*!
@file   CharacterStateShooting.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "CharacterStateNeutral.h"
#include "CharacterStateShooting.h"
#include "Player.h"
#include "../GameScene.h"
#include "../../Framework/Manager.h"
#include "../../Framework/Mesh/SkinMeshModel.h"

using namespace Framework;
using namespace Game;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/

CharacterStateShooting::CharacterStateShooting(Character* pOwner)
    : CharacterState(pOwner)
{
    name_ = STATE_SHOOTING;
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

CharacterStateShooting::~CharacterStateShooting()
{
}

/******************************************************************************
@brief  初期化処理
******************************************************************************/

void CharacterStateShooting::Init(void)
{
}

/******************************************************************************
@brief  終了処理
******************************************************************************/

void CharacterStateShooting::Uninit(void)
{
}

/******************************************************************************
@brief  更新処理
******************************************************************************/

void CharacterStateShooting::Update(void)
{
    if (pOwner_->IsMotionEnd(Motion::SHOOTING))
    {
        pOwner_->SetMotion(Motion::NEUTRAL);
        pOwner_->SetState(new CharacterStateNeutral(pOwner_));
    }
}

/******************************** 実装ここまで *******************************/

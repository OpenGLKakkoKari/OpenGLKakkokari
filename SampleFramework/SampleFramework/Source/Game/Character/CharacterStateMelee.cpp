/*****************************************************************************/
/*!
@file   CharacterStateMelee.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "CharacterStateNeutral.h"
#include "CharacterStateMelee.h"
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

CharacterStateMelee::CharacterStateMelee(Character* pOwner)
    : CharacterState(pOwner)
{
    name_ = STATE_MELEE;
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

CharacterStateMelee::~CharacterStateMelee()
{
}

/******************************************************************************
@brief  初期化処理
******************************************************************************/

void CharacterStateMelee::Init(void)
{
}

/******************************************************************************
@brief  終了処理
******************************************************************************/

void CharacterStateMelee::Uninit(void)
{
}

/******************************************************************************
@brief  更新処理
******************************************************************************/

void CharacterStateMelee::Update(void)
{
    if (pOwner_->IsMotionEnd(Motion::MELEE))
    {
        pOwner_->SetMotion(Motion::NEUTRAL);
        pOwner_->SetState(new CharacterStateNeutral(pOwner_));
    }
}

/******************************** 実装ここまで *******************************/

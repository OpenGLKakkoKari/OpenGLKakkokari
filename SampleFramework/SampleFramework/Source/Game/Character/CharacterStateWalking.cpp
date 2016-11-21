/*****************************************************************************/
/*!
@file   CharacterStateWalking.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
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


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/

CharacterStateWalking::CharacterStateWalking(Character* pOwner)
    : CharacterState(pOwner)
{
    name_ = STATE_WALKING;
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

CharacterStateWalking::~CharacterStateWalking()
{
}

/******************************************************************************
@brief  初期化処理
******************************************************************************/

void CharacterStateWalking::Init(void)
{
}

/******************************************************************************
@brief  終了処理
******************************************************************************/

void CharacterStateWalking::Uninit(void)
{
}

/******************************************************************************
@brief  更新処理
******************************************************************************/

void CharacterStateWalking::Update(void)
{
    // キック
    if (Manager::GetKeyboard()->Trigger(VK_RETURN))
    {
        pOwner_->SetMotion(Motion::MELEE);
        pOwner_->SetState(new CharacterStateMelee(pOwner_));
    }
    // ジャンプ
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

/******************************** 実装ここまで *******************************/

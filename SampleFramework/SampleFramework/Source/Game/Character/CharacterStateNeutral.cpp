/*****************************************************************************/
/*!
@file   CharacterStateNeutral.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
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


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/

CharacterStateNeutral::CharacterStateNeutral(Character* pOwner)
    : CharacterState(pOwner)
{
    name_ = STATE_NEUTRAL;
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

CharacterStateNeutral::~CharacterStateNeutral()
{
}

/******************************************************************************
@brief  初期化処理
******************************************************************************/

void CharacterStateNeutral::Init(void)
{
}

/******************************************************************************
@brief  終了処理
******************************************************************************/

void CharacterStateNeutral::Uninit(void)
{
}

/******************************************************************************
@brief  更新処理
******************************************************************************/

void CharacterStateNeutral::Update(void)
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
    // 移動
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

/******************************** 実装ここまで *******************************/

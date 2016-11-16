/*****************************************************************************/
/*!
@file   CharacterStateJumping.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "CharacterStateJumping.h"
#include "CharacterStateLanding.h"
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

CharacterStateJumping::CharacterStateJumping(Character* pOwner)
    : CharacterState(pOwner)
{
    name_ = STATE_JUMPING;
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

CharacterStateJumping::~CharacterStateJumping()
{
}

/******************************************************************************
@brief  初期化処理
******************************************************************************/

void CharacterStateJumping::Init(void)
{
}

/******************************************************************************
@brief  終了処理
******************************************************************************/

void CharacterStateJumping::Uninit(void)
{
}

/******************************************************************************
@brief  更新処理
******************************************************************************/

void CharacterStateJumping::Update(void)
{
    // 重力
    pOwner_->traVec.y -= 0.5f;

    // 接地したら着地モーションに移行
    if (pOwner_->IsLanding())
    {
        pOwner_->SetMotion(Motion::LANDING);
        pOwner_->SetState(new CharacterStateLanding(pOwner_));
    }
}

/******************************** 実装ここまで *******************************/

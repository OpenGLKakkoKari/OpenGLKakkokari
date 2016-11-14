/*****************************************************************************/
/*!
@file   CharacterStateLanding.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "CharacterStateLanding.h"
#include "CharacterStateNeutral.h"
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

CharacterStateLanding::CharacterStateLanding(Character* pOwner)
    : CharacterState(pOwner)
{
    name_ = STATE_LANDING;
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

CharacterStateLanding::~CharacterStateLanding()
{
}

/******************************************************************************
@brief  初期化処理
******************************************************************************/

void CharacterStateLanding::Init(void)
{
}

/******************************************************************************
@brief  終了処理
******************************************************************************/

void CharacterStateLanding::Uninit(void)
{
}

/******************************************************************************
@brief  更新処理
******************************************************************************/

void CharacterStateLanding::Update(void)
{
    if (pOwner_->IsMotionEnd(Motion::LANDING))
    {
        pOwner_->SetMotion(Motion::NEUTRAL);
        pOwner_->SetState(new CharacterStateNeutral(pOwner_));
    }
}

/******************************** 実装ここまで *******************************/

/*****************************************************************************/
/*!
@file   Fade.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Fade.h"
#include "../Game/GameScene.h"
#include "Manager.h"
#include "Math\Math.h"
#include <math.h>


using namespace Game;
using namespace Framework;
using namespace Framework::Math;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/

Fade::Fade() : nowFade(FADE_IN), nextScene_(NULL)
{
    SetFrame(30);
    SetPriority(-1);

    color = Color(0, 0, 0, 255);
    SetPosition(Vector2((float)Manager::GetWindow()->GetWidth() / 2, (float)Manager::GetWindow()->GetHeight() / 2));
    SetScale(Vector2((float)Manager::GetWindow()->GetWidth(), (float)Manager::GetWindow()->GetHeight()));
    SetColor(color);
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

Fade::~Fade()
{
}

/******************************************************************************
@brief  フェード更新処理
******************************************************************************/

void Fade::Update(void)
{

    // フェードイン
    if (nowFade == FADE_IN)
    {
        color.a -= unit;

        if (color.a <= 0 + unit)
        {
            color.a = 0;
            nowFade = FADE_NONE;
        }
    }
    // フェードアウト
    else if (nowFade == FADE_OUT)
    {
        color.a += unit;

        if (color.a >= 255 - unit)
        {
            color.a = 255;
            nowFade = FADE_IN;

            Manager::SetScene(nextScene_);
        }
    }

    SetColor(color);
}

/******************************************************************************
@brief  フェード設定処理
@param  fadeType    フェードの種類
@param  nextState   移行するステート
******************************************************************************/

void Fade::SetFade(Type fadeType, Scene* nextScene)
{
    nowFade = fadeType;
    nextScene_ = nextScene;
}

/******************************** 実装ここまで *******************************/

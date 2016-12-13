/*****************************************************************************/
/*!
@file   Explosion.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Explosion.h"
#include <math.h>
#include "../Framework/Math/Math.h"
#include "../Framework/Manager.h"
#include "../Framework/AnimationBillboard.h"


using namespace Framework;
using namespace Framework::Math;
using namespace Game;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/

Explosion::Explosion() : frameMax(10)
{
    for (int i = 0; i < BILLBOARD_NUM; i++)
    {
        frameCount[i] = 0;
        pBillboard[i] = NULL;
    }
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

Explosion::~Explosion()
{
    for (int i = 0; i < BILLBOARD_NUM; i++)
    {
        SAFE_DELETE(pBillboard[i])
    }
}

/******************************************************************************
@brief  初期化処理
******************************************************************************/

void Explosion::Init(void)
{
    for (int i = 0; i < BILLBOARD_NUM; i++)
    {
        pBillboard[i] = AnimationBillboard::Create(
            // 座標
            Vector3(300.0f, 100.0f, 0.0f),
            // サイズ
            Vector2(200.0f, 200.0f),
            // 色
            Color(255, 255, 255, 255),
            // ビルボードの種類
            Billboard::BILLBOARD_DEFAULT,
            // アニメーションデータ
            AnimationData(8, 1, 8),
            // ファイル名
            "data/TEXTURE/explosion000.png"
            );
        pBillboard[i]->SetUse(false);
    }
}

/******************************************************************************
@brief  描画処理
******************************************************************************/

void Explosion::Update(void)
{
    for (int i = 0; i < BILLBOARD_NUM; i++)
    {
        if (pBillboard[i]->IsUsed())
        {
            frameCount[i]++;
            if (frameCount[i] > frameMax)
            {
                frameCount[i] = 0;
                pBillboard[i]->NextPattern();
            }

            if (pBillboard[i]->IsAnimationEnd())
            {
                pBillboard[i]->SetUse(false);
                pBillboard[i]->SetPattern(0);
            }

        }
    }


}
/******************************************************************************
@brief  描画処理
@param  pos             座標
******************************************************************************/

void Explosion::Create(const Vector3& pos)
{
    for (int i = 0; i < BILLBOARD_NUM; i++)
    {
        if (!pBillboard[i]->IsUsed())
        {
            pBillboard[i]->SetUse(true);
            pBillboard[i]->SetPosition(pos);
            break;
        }
    }
}

/******************************** 実装ここまで *******************************/

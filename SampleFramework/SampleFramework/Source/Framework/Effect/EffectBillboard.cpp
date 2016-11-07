/*****************************************************************************/
/*!
@file   EffectBillboard.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "EffectBillboard.h"
#include "../Manager.h"
#include "../Math/Math.h"
#include "Emitter.h"


using namespace Framework;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/

EffectBillboard::EffectBillboard() : 
blendType(0), canDepthWrite(false), canDepthTest(false)
{

}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

EffectBillboard::~EffectBillboard()
{
}

/******************************************************************************
@brief  描画処理
******************************************************************************/

void EffectBillboard::Draw(void)
{

    Manager::GetRenderer()->SetCullingEnable(false);
    switch (blendType)
    {
    case 0: Manager::GetRenderer()->SetBlend(Renderer::BLEND_SRC_ALPHA, Renderer::BLEND_ONE); break;
    case 1: break;
    }
    switch (canDepthWrite)
    {
    case 0: Manager::GetRenderer()->SetZWriteEnable(false); break;
    case 1: Manager::GetRenderer()->SetZWriteEnable(true); break;
    }
    switch (canDepthTest)
    {
    case 0: Manager::GetRenderer()->SetZTestEnable(false); break;
    case 1: Manager::GetRenderer()->SetZTestEnable(true); break;
    }

    Billboard::Draw();

    Manager::GetRenderer()->SetCullingEnable(true);
    Manager::GetRenderer()->SetZWriteEnable(true);
    Manager::GetRenderer()->SetZTestEnable(true);
    Manager::GetRenderer()->SetBlend(Renderer::BLEND_SRC_ALPHA, Renderer::BLEND_SRC_INVALPHA);
}

/******************************************************************************
@brief  ビルボード生成処理
@param  pos             座標
@param  size            サイズ
@param  col             色
@param  type            ビルボードの種類
@param  FileName        テクスチャのファイル名
@return Billboard*      ビルボード情報へのポインタ
******************************************************************************/

EffectBillboard* EffectBillboard::Create(const Vector3& pos, const Vector2& size, Color col, TYPE type, const char *FileName)
{
    EffectBillboard *pBillboard = new EffectBillboard;
    pBillboard->SetBillboardType(type);
    pBillboard->SetPosition(pos);
    pBillboard->SetScale(Vector2(size.x, size.y));
    pBillboard->SetColor(col);
    if (FileName)
        pBillboard->SetTexture(FileName);
    return pBillboard;
}

/******************************** 実装ここまで *******************************/

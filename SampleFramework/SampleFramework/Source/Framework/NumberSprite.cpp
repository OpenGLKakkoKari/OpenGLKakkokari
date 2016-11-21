/*****************************************************************************/
/*!
@file   NumberSprite.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "NumberSprite.h"
#include "Manager.h"


using namespace Framework;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/

NumberSprite::NumberSprite() : number_(0)
{
    SetNumberVertexUV();
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

NumberSprite::~NumberSprite()
{
}

/******************************************************************************
@brief  番号設定
******************************************************************************/

void NumberSprite::SetNumber(int number)
{
    number_ = number;
    SetNumberVertexUV();
}

/******************************************************************************
@brief テクスチャ座標設定
******************************************************************************/

void NumberSprite::SetNumberVertexUV()
{
    vtx[0].tex = Vector2(0.1f * number_, 0.0f);
    vtx[1].tex = Vector2(0.1f * number_ + 0.1f, 0.0f);
    vtx[2].tex = Vector2(0.1f * number_, 1.0f);
    vtx[3].tex = Vector2(0.1f * number_ + 0.1f, 1.0f);
}

/******************************************************************************
@brief  スプライト生成処理
@param  pos             座標
@param  size            サイズ
@param  col             色
@param  FileName        テクスチャのファイル名
@param  number          数字
@return Sprite*         スプライト情報へのポインタ
******************************************************************************/

NumberSprite* NumberSprite::Create(const Vector2& pos, const Vector2& size, Color col, const char *FileName, int number)
{
    NumberSprite *pSprite = new NumberSprite;
    pSprite->SetPosition(pos);
    pSprite->SetScale(size);
    pSprite->SetColor(col);
    pSprite->SetTexture(FileName);
    pSprite->SetNumber(number);
    return pSprite;
}
NumberSprite* NumberSprite::Create(const Vector2& pos, const Vector2& size, Color col, int number)
{
    NumberSprite *pSprite = new NumberSprite;
    pSprite->SetPosition(pos);
    pSprite->SetScale(size);
    pSprite->SetColor(col);
    pSprite->SetNumber(number);
    return pSprite;
}

/******************************** 実装ここまで *******************************/

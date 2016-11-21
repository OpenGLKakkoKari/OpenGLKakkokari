/*****************************************************************************/
/*!
@file   Plant.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Plant.h"
#include <math.h>
#include "../Framework/Math/Math.h"
#include "../Framework/Manager.h"


using namespace Framework;
using namespace Framework::Math;
using namespace Game;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/

Plant::Plant() : polygonNum_(3)
{
    type = BILLBOARD_NONE;
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

Plant::~Plant()
{

}

/******************************************************************************
@brief  描画処理
******************************************************************************/

void Plant::Draw(void)
{

    Manager::GetRenderer()->SetAlphaTestEnable(true);
    Manager::GetRenderer()->SetCullingEnable(false);

    float rotUnit = 180.0f / polygonNum_;
    for (int i = 0; i < polygonNum_; i++)
    {
        SetRotation(Vector3(0.0f, ToRad(rotUnit * i), 0.0f));
        SetScale(Vector2(scale_.x, scale_.y));
        Billboard::Draw();
    }

    Manager::GetRenderer()->SetAlphaTestEnable(false);
    Manager::GetRenderer()->SetCullingEnable(true);
}

/******************************************************************************
@brief  草生成処理
@param  FileName    テクスチャ名
@param  pos         座標
@param  size        大きさ
@param  polygonNum  描画枚数
@return Plant       草情報
******************************************************************************/

Plant* Plant::Create(
    const char* FileName,
    const Vector3& pos,
    const Vector2& size,
    int polygonNum)
{
    Plant* pPlant = new Plant;

    pPlant->SetPosition(pos);
    pPlant->SetScale(Vector2(size.x, size.y));
    pPlant->SetTexture(FileName);
    pPlant->SetPolygonNum(polygonNum);

    return pPlant;
}

/******************************** 実装ここまで *******************************/

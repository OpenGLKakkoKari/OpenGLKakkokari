/*****************************************************************************/
/*!
@file   Graph.cpp
@brief  Graph Program

@author Yuki Kogawara
@date   2016/05/31 (Tue) Yuki Kogawara

@copy   Copyright(C) 2016 HAL TOKYO All Rights Reserved.

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Graph.h"
#include "../Manager.h"

using Framework::Graph;
using Framework::Manager;
using Framework::Vector2;
using Framework::Color;


/*  実装
******************************************************************************/

/*****************************************************************************/
/*!
@fn     Framework::Graph::Graph
@brief  コンストラクタ
@param  void

******************************************************************************/


Graph::Graph()
{
    min = 0;
    max = 10;
    pointNum = 10;
    size = Vector2(100.0f, 100.0f);
    pos = Vector2(0.0f, 0.0f);
    pSprite = nullptr;
    pVtx = nullptr;
    isBackground = true;
}


/*****************************************************************************/
/*!
@fn     Framework::Graph::~Graph
@brief  デストラクタ
@param  void

******************************************************************************/


Graph::~Graph()
{
    if (pVtx != nullptr)
    {
        delete[] pVtx;
        pVtx = nullptr;
    }
}


/*****************************************************************************/
/*!
@fn     Framework::Graph::Init
@brief  グラフ初期化
@param  void
@return void

******************************************************************************/


void Graph::Init(float min, float max, int pNum, Vector2 size, Vector2 pos)
{
    this->max = max;
    this->min = min;
    this->pointNum = pNum;
    this->size = size;
    this->pos = pos;

    pSprite = Sprite::Create(
        // 座標
        pos,
        // 大きさ
        size,
        // 色
        Color(  0,  0,  0, 120));

    pVtx = new Vertex[pNum * 2];

    for (int i = 0; i < pointNum * 2; i++)
    {
        pVtx[i].col = Color(255, 255, 255, 255);
        pVtx[i].pos = Vector3(
            -0.5f + (1.0f / (pointNum - 1)) * (i / 2),
            -0.5f,
            0.0f);
        pVtx[i].nor = Vector3::Zero();
        pVtx[i].tex = Vector2::Zero();
    }
}


/*****************************************************************************/
/*!
@fn     Framework::Graph::Uninit
@brief  グラフ終了処理
@param  void
@return void

******************************************************************************/


void Graph::Uninit(void)
{
    if (pSprite != nullptr)
    {
        delete pSprite;
        pSprite = nullptr;
    }
    if (pVtx != nullptr)
    {
        delete pVtx;
        pVtx = nullptr;
    }

}


/*****************************************************************************/
/*!
@fn     Framework::Graph::Draw
@brief  グラフ描画処理
@param  void
@return void

******************************************************************************/


void Graph::Draw(void)
{
    // 背景描画
    if (isBackground)
        pSprite->Draw();

    // グラフ描画
    Matrix WorldMatrix;
    Matrix transMat, scaMat;
    Matrix::Identity(&WorldMatrix);
    Matrix::Scale(&scaMat, size.x, size.y, 1.0f);
    Matrix::Translation(&transMat, pos.x - (float)Manager::GetWindow()->Width() / 2, (float)Manager::GetWindow()->Height() / 2 - pos.y, 0.0f);

    Matrix::Multiply(&WorldMatrix, &WorldMatrix, &scaMat);
    Matrix::Multiply(&WorldMatrix, &WorldMatrix, &transMat);

    Manager::GetRenderer()->SetTranslationMode(false);
    Manager::GetRenderer()->SetLightEnable(false);
    Manager::GetRenderer()->SetTexture(nullptr);
    Manager::GetRenderer()->SetWorldMatrix(&WorldMatrix);
    Manager::GetRenderer()->DrawPrimitiveUP(Renderer::PRIMITIVE_TYPE_TRIANGLE_STRIP, pVtx, pointNum * 2 - 2);

}


/*****************************************************************************/
/*!
@fn     Framework::Graph::SetRange
@brief  範囲設定
@param  min         最小値
@param  max         最大値
@return void

******************************************************************************/


void Graph::SetRange(float min, float max)
{
    this->min = min;
    this->max = max;
}


/*****************************************************************************/
/*!
@fn     Framework::Graph::SetPointNum
@brief  表示数設定
@param  pNum        点の数(表示数)
@return void

******************************************************************************/


void Graph::SetPointNum(int pNum)
{

}


/*****************************************************************************/
/*!
@fn     Framework::Graph::SetColor
@brief  色設定
@param  color       表示色
@return void

******************************************************************************/


void Graph::SetColor(Color color)
{
    for (int i = 0; i < pointNum * 2; i++)
    {
        pVtx[i].col = color;
    }
}


/*****************************************************************************/
/*!
@fn     Framework::Graph::SetBackgroundEnable
@brief  点追加
@param  point       追加する点
@return void

******************************************************************************/


void Graph::SetBackgroundEnable(bool isEnable)
{
    isBackground = isEnable;
}


/*****************************************************************************/
/*!
@fn     Framework::Graph::AddPoint
@brief  点追加
@param  point       追加する点
@return void

******************************************************************************/


void Graph::AddPoint(float point)
{
    float *pTmp = new float[pointNum * 2];

    for (int i = 0; i < pointNum * 2; i++)
    {
        pTmp[i] = pVtx[i].pos.y;
    }
    for (int i = 0; i < pointNum * 2; i++)
    {
        if (i < pointNum * 2 - 2)
        {
            pVtx[i].pos.y = pTmp[i + 2];
        }
        else
        {
            if (i % 2 == 1)
            {
                pVtx[i].pos.y = -0.5f + (point / (max - min));
            }
        }
    }

    delete[] pTmp;
}


/******************************** 実装ここまで *******************************/

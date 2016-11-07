/*****************************************************************************/
/*!
@file   GameObject.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "GameObject.h"
#include "Manager.h"


using namespace Framework;


/*  静的変数宣言
******************************************************************************/


GameObject*     GameObject::pFirst;
GameObject*     GameObject::pLast;
int             GameObject::allObjectNum;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/

GameObject::GameObject()
{
    RegisterList();
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

GameObject::~GameObject()
{
    UnregisterList();
}

/******************************************************************************
@brief  全ゲームオブジェクト更新
******************************************************************************/

void GameObject::UpdateAll()
{
    // ゲームオブジェクトをすべて更新
    for (GameObject* p = pFirst; p != NULL; p = p->pNext)
    {
        if (p->isUsed_)
            p->Update();
    }
}

/******************************************************************************
@brief  描画リストに登録
******************************************************************************/

void GameObject::RegisterList()
{
    // インスタンス数増加
    allObjectNum++;

    // 先頭への要素追加
    if (pFirst == NULL)
    {
        pFirst = this;
        pLast = this;
        pPrev = NULL;
        pNext = NULL;
    }
    // 末尾への要素追加
    else
    {
        pPrev = pLast;
        pPrev->pNext = this;
        pLast = this;
    }
}

/******************************************************************************
@brief  描画リストから解除
******************************************************************************/

void GameObject::UnregisterList()
{
    // インスタンス数減少
    allObjectNum--;

    // 先頭の要素削除
    if (pFirst == this)
    {
        pFirst = pNext;

        // リスト内の要素が残り１つ
        if (pLast == this)
            pLast = NULL;
        else
            pNext->pPrev = NULL;
    }
    // 末尾の要素削除
    else if (pLast == this)
    {
        pLast = pPrev;
        pPrev->pNext = NULL;
    }
    // 中間の要素削除
    else
    {
        pPrev->pNext = pNext;
        pNext->pPrev = pPrev;
    }
}

/******************************** 実装ここまで *******************************/

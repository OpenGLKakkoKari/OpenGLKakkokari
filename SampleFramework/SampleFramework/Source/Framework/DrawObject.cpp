/*****************************************************************************/
/*!
@file   DrawObject.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "DrawObject.h"
#include "Manager.h"


using namespace Framework;


/*  静的変数宣言
******************************************************************************/


DrawObject*     DrawObject::pFirst[TYPE_MAX];
DrawObject*     DrawObject::pLast[TYPE_MAX];
int             DrawObject::objectNum[TYPE_MAX];
int             DrawObject::allObjectNum;
Matrix          DrawObject::viewMatrix;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/

DrawObject::DrawObject() :
type(TYPE_MESH),
priority(0)
{
    RegisterList();
}
DrawObject::DrawObject(Type type) :
type(type),
priority(0)
{
    RegisterList();
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

DrawObject::~DrawObject()
{
    UnregisterList();
}

/******************************************************************************
@brief  全描画処理
******************************************************************************/

void DrawObject::DrawAll()
{
    DrawObject** pObjectListTop[TYPE_MAX];
    for (int i = 0; i < TYPE_MAX; i++)
        pObjectListTop[i] = new DrawObject*[objectNum[i]];

    DrawObject** pObjectList[TYPE_MAX];
    for (int i = 0; i < TYPE_MAX; i++)
        pObjectList[i] = pObjectListTop[i];

    DrawObject* p;

    // リストに全オブジェクトのポインタを代入
    for (int i = 0; i < TYPE_MAX; i++)
    {
        for (p = pFirst[i]; p != NULL; p = p->pNext)
        {
            *pObjectList[i] = p;
            pObjectList[i]++;
        }
    }

    // ビュー行列を取得
    Manager::GetRenderer()->SetTranslationMode(true);
    viewMatrix = Manager::GetRenderer()->GetViewMatrix();

    // Zソート(クイックソート)
    if (objectNum[TYPE_MESH])
        ZSort(0, objectNum[TYPE_MESH] - 1, pObjectListTop[TYPE_MESH]);
    if (objectNum[TYPE_ALPHAMESH])
        ZSort(0, objectNum[TYPE_ALPHAMESH] - 1, pObjectListTop[TYPE_ALPHAMESH]);
    if (objectNum[TYPE_SPRITE])
        PrioritySort(0, objectNum[TYPE_SPRITE] - 1, pObjectListTop[TYPE_SPRITE]);

    // 描画
    for (int i = 0; i < TYPE_MAX; i++)
        pObjectList[i] = pObjectListTop[i];

    for (int i = 0; i < TYPE_MAX; i++)
    {
        for (int j = 0; j < objectNum[i]; j++, pObjectList[i]++)
        {
            if ((*pObjectList[i])->isUsed_)
                (*pObjectList[i])->Draw();
        }
    }

    for (int i = 0; i < TYPE_MAX; i++)
        delete[] pObjectListTop[i];
}

/******************************************************************************
@brief  Zソート(クイックソート)
@param  indexL              整列対象の左端要素番号
@param  indexR              整列対象の右端要素番号
@param  pDrawObjectList     整列対象
******************************************************************************/

void DrawObject::ZSort(int idxL, int idxR, DrawObject** pDrawObjectList)
{
    unsigned int Base = (idxL + idxR) >> 1;		// 基準値の要素番号
    DrawObject* pSwapWork;						// データ入れ替え時の作業用

    int i = idxL;
    int j = idxR;

    while (1){
        /*** 基準値より小さい値をみつける ***/
        while (pDrawObjectList[i]->GetZ() > pDrawObjectList[Base]->GetZ()){
            ++i;
        }

        /*** 基準値より大きい値を見つける ***/
        while (pDrawObjectList[j]->GetZ() < pDrawObjectList[Base]->GetZ()){
            --j;
        }

        /*** 衝突したら終了 ***/
        if (i >= j){
            break;
        }

        /*** 要素の入れ替え ***/
        pSwapWork = pDrawObjectList[i];
        pDrawObjectList[i] = pDrawObjectList[j];
        pDrawObjectList[j] = pSwapWork;

        ++i;
        --j;
    }

    /*** 再帰呼び出し ***/
    if (idxL < i - 1){
        ZSort(idxL, (unsigned int)(i - 1), pDrawObjectList);
    }

    /*** 再帰呼び出し ***/
    if (j + 1 < idxR){
        ZSort((unsigned int)(j + 1), idxR, pDrawObjectList);
    }
}

/******************************************************************************
@brief  優先度ソート(クイックソート)
@param  indexL              整列対象の左端要素番号
@param  indexR              整列対象の右端要素番号
@param  pDrawObjectList     整列対象
******************************************************************************/

void DrawObject::PrioritySort(int idxL, int idxR, DrawObject** pDrawObjectList)
{
    unsigned int Base = (idxL + idxR) >> 1;		// 基準値の要素番号
    DrawObject* pSwapWork;						// データ入れ替え時の作業用

    int i = idxL;
    int j = idxR;

    while (1){
        /*** 基準値より小さい値をみつける ***/
        while (pDrawObjectList[i]->priority > pDrawObjectList[Base]->priority){
            ++i;
        }

        /*** 基準値より大きい値を見つける ***/
        while (pDrawObjectList[j]->priority < pDrawObjectList[Base]->priority){
            --j;
        }

        /*** 衝突したら終了 ***/
        if (i >= j){
            break;
        }

        /*** 要素の入れ替え ***/
        pSwapWork = pDrawObjectList[i];
        pDrawObjectList[i] = pDrawObjectList[j];
        pDrawObjectList[j] = pSwapWork;

        ++i;
        --j;
    }

    /*** 再帰呼び出し ***/
    if (idxL < i - 1){
        PrioritySort(idxL, (unsigned int)(i - 1), pDrawObjectList);
    }

    /*** 再帰呼び出し ***/
    if (j + 1 < idxR){
        PrioritySort((unsigned int)(j + 1), idxR, pDrawObjectList);
    }
}

/******************************************************************************
@brief  Zソートに必要なZ値(ビュー変換後のオブジェクトのZ値)を算出
@param  void
@return float       Z値
******************************************************************************/

float DrawObject::GetZ()
{
    Vector3 vecLook;
    Matrix worldMatrix;
    GetMatrix(&worldMatrix);
    Vector3::Transform(&vecLook, &pos_, &worldMatrix);
    Vector3::Transform(&vecLook, &pos_, &viewMatrix);
    return vecLook.z;
}

/******************************************************************************
@brief  描画リストに登録
******************************************************************************/

void DrawObject::RegisterList()
{
    // インスタンス数増加
    allObjectNum++;
    objectNum[type]++;

    // 先頭への要素追加
    if (pFirst[type] == NULL)
    {
        pFirst[type] = this;
        pLast[type] = this;
        pPrev = NULL;
        pNext = NULL;
    }
    // 末尾への要素追加
    else
    {
        pPrev = pLast[type];
        pPrev->pNext = this;
        pLast[type] = this;
    }
}

/******************************************************************************
@brief  描画リストから解除
******************************************************************************/

void DrawObject::UnregisterList()
{
    // インスタンス数減少
    allObjectNum--;
    objectNum[type]--;

    // 先頭の要素削除
    if (pFirst[type] == this)
    {
        pFirst[type] = pNext;

        // リスト内の要素が残り１つ
        if (pLast[type] == this)
            pLast[type] = NULL;
        else
            pNext->pPrev = NULL;
    }
    // 末尾の要素削除
    else if (pLast[type] == this)
    {
        pLast[type] = pPrev;
        pPrev->pNext = NULL;
    }
    // 中間の要素削除
    else
    {
        pPrev->pNext = pNext;
        pNext->pPrev = pPrev;
    }
}

/******************************************************************************
@brief  新しいタイプで再登録
@param  newType     新しいタイプ
******************************************************************************/

void DrawObject::SetType(Type newType)
{
    UnregisterList();

    type = newType;

    RegisterList();
}

/******************************** 実装ここまで *******************************/

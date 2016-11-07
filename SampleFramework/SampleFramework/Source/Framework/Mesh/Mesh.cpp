/*****************************************************************************/
/*!
@file   Mesh.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Mesh.h"
#include "../File/Reader/ModelReader.h"


using namespace Framework;
using namespace Framework::File;


/*  変数宣言
******************************************************************************/


Mesh*           Mesh::pFirst = NULL;
Mesh*           Mesh::pLast = NULL;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/

Mesh::Mesh() : 
faceNum(0), vertexNum(0),
pVertex(NULL), pIndexList(NULL),
pMaterialList(NULL), materialNum(0),
pSubsetList(NULL), subsetNum(0)
{
    // 文字列の初期化
    strcpy_s(filePath, 256, "");

    // リストの最前列に登録
    if (!pFirst)
    {
        pFirst = this;
        pLast = this;
    }
    // リストの最後尾に登録
    else
    {
        pLast->pNext = this;
        pPrev = pLast;
        pLast = this;
    }

    // 登録後使用カウンタを増やす
    useNum++;
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

Mesh::~Mesh()
{
    // リストの最前列の場合
    if (pFirst == this)
    {
        pFirst = pNext;
        // これ以上テクスチャはない場合
        if (!pFirst)
        {
            pLast = NULL;
        }
        // 他にもテクスチャは残っている場合
        else
        {
            pFirst->pPrev = NULL;
        }
    }
    // 末尾の場合
    else if (pLast == this)
    {
        // これ以上テクスチャはない場合は
        // pFirst == pLast == thisになるため
        // ここには来ない
        pLast = pPrev;
        pLast->pNext = NULL;
    }
    // 中間の場合
    else
    {
        pNext->pPrev = pPrev;
        pPrev->pNext = pNext;
    }
}

/******************************************************************************
@brief  メッシュ読み込み
@param  FileName    ファイル名
@return Mesh*       メッシュ情報
******************************************************************************/

Mesh* Mesh::Load(const char *FileName)
{
    // ファイル名がない場合NULLを返す
    if (strcmp(FileName, "") == 0)
    {
        return NULL;
    }
    // すでに生成されていればそれを返す
    for (Mesh* p = pFirst; p != NULL; p = p->pNext)
    {
        if (!strcmp(p->filePath, FileName))
        {
            p->useNum++;    // 使用オブジェクト数の増加
            return p;
        }
    }

    Mesh* pMesh = ModelReader::Load(FileName);
    strcpy_s(pMesh->filePath, 256, FileName);
    return pMesh;
}

/******************************************************************************
@brief  メッシュ開放
******************************************************************************/

void Mesh::Release()
{
    useNum--;

    if (useNum <= 0)
    {
        if (pVertex)
        {
            delete[] pVertex;
            pVertex = NULL;
        }
        if (pIndexList)
        {
            delete[] pIndexList;
            pIndexList = NULL;
        }
        if (pMaterialList)
        {
            for (int i = 0; i < materialNum; i++)
            {
                if (pMaterialList[i].pTexture)
                {
                    pMaterialList[i].pTexture->Release();
                    pMaterialList[i].pTexture = NULL;
                }
            }
            delete[] pMaterialList;
            pMaterialList = NULL;
        }
        if (pSubsetList)
        {
            delete[] pSubsetList;
            pSubsetList = NULL;
        }
        if (pVtxBuf)
        {
            pVtxBuf->Release();
            pVtxBuf = NULL;
        }
        if (pIdxBuf)
        {
            pIdxBuf->Release();
            pIdxBuf = NULL;
        }
        delete this;
    }
}

/******************************** 実装ここまで *******************************/

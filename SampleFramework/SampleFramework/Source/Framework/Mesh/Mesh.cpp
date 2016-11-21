/*****************************************************************************/
/*!
@file   Mesh.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Mesh.h"
#include "../Manager.h"
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
pSubsetList(NULL), subsetNum(0),
pVtxBuf(NULL), pIdxBuf(NULL),

pNext(NULL), pPrev(NULL), useNum(0)
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
@brief  箱型メッシュ作成
@param  
@return Mesh*       メッシュ情報
******************************************************************************/

Mesh* Mesh::CreateBox(const Vector3& scale)
{
    // 箱型メッシュ情報

    Mesh* pMesh = new Mesh;

    const int faceNum = 12;
    const int vertexNum = 24;
    
    pMesh->faceNum          = faceNum;
    pMesh->vertexNum        = vertexNum;
    pMesh->materialNum      = 1;
    pMesh->subsetNum        = 1;

    pMesh->pVertex          = new Vertex[pMesh->vertexNum];
    pMesh->pIndexList       = new int[pMesh->faceNum*3];
    pMesh->pMaterialList    = new Material[1];
    pMesh->pSubsetList      = new Subset[1];

    pMesh->pVtxBuf          = Manager::GetRenderer()->CreateVertexBuffer(pMesh->vertexNum);
    pMesh->pIdxBuf          = Manager::GetRenderer()->CreateIndexBuffer(pMesh->faceNum*3);

    const Vertex vertexList[vertexNum] =
    {
        // 前面
        { Vector3(-scale.x/2,  scale.y/2, -scale.z/2), Vector3(0.0f, 0.0f, -1.0f), Color(255, 255, 255, 255), Vector2(0.0f, 0.0f), },
        { Vector3( scale.x/2,  scale.y/2, -scale.z/2), Vector3( 0.0f,  0.0f, -1.0f), Color(255, 255, 255, 255), Vector2(1.0f, 0.0f), },
        { Vector3(-scale.x/2, -scale.y/2, -scale.z/2), Vector3( 0.0f,  0.0f, -1.0f), Color(255, 255, 255, 255), Vector2(0.0f, 1.0f), },
        { Vector3( scale.x/2, -scale.y/2, -scale.z/2), Vector3( 0.0f,  0.0f, -1.0f), Color(255, 255, 255, 255), Vector2(1.0f, 1.0f), },
        // 下面
        { Vector3(-scale.x/2, -scale.y/2, -scale.z/2), Vector3( 0.0f, -1.0f,  0.0f), Color(255, 255, 255, 255), Vector2(0.0f, 0.0f), },
        { Vector3( scale.x/2, -scale.y/2, -scale.z/2), Vector3( 0.0f, -1.0f,  0.0f), Color(255, 255, 255, 255), Vector2(1.0f, 0.0f), },
        { Vector3(-scale.x/2, -scale.y/2,  scale.z/2), Vector3( 0.0f, -1.0f,  0.0f), Color(255, 255, 255, 255), Vector2(0.0f, 1.0f), },
        { Vector3( scale.x/2, -scale.y/2,  scale.z/2), Vector3( 0.0f, -1.0f,  0.0f), Color(255, 255, 255, 255), Vector2(1.0f, 1.0f), },
        // 背面
        { Vector3(-scale.x/2, -scale.y/2,  scale.z/2), Vector3( 0.0f,  0.0f,  1.0f), Color(255, 255, 255, 255), Vector2(0.0f, 0.0f), },
        { Vector3( scale.x/2, -scale.y/2,  scale.z/2), Vector3( 0.0f,  0.0f,  1.0f), Color(255, 255, 255, 255), Vector2(1.0f, 0.0f), },
        { Vector3(-scale.x/2,  scale.y/2,  scale.z/2), Vector3( 0.0f,  0.0f,  1.0f), Color(255, 255, 255, 255), Vector2(0.0f, 1.0f), },
        { Vector3( scale.x/2,  scale.y/2,  scale.z/2), Vector3( 0.0f,  0.0f,  1.0f), Color(255, 255, 255, 255), Vector2(1.0f, 1.0f), },
        // 上面
        { Vector3(-scale.x/2,  scale.y/2,  scale.z/2), Vector3( 0.0f,  1.0f,  0.0f), Color(255, 255, 255, 255), Vector2(0.0f, 0.0f), },
        { Vector3( scale.x/2,  scale.y/2,  scale.z/2), Vector3( 0.0f,  1.0f,  0.0f), Color(255, 255, 255, 255), Vector2(1.0f, 0.0f), },
        { Vector3(-scale.x/2,  scale.y/2, -scale.z/2), Vector3( 0.0f,  1.0f,  0.0f), Color(255, 255, 255, 255), Vector2(0.0f, 1.0f), },
        { Vector3( scale.x/2,  scale.y/2, -scale.z/2), Vector3( 0.0f,  1.0f,  0.0f), Color(255, 255, 255, 255), Vector2(1.0f, 1.0f), },
        // 右面
        { Vector3( scale.x/2,  scale.y/2, -scale.z/2), Vector3(-1.0f,  0.0f,  0.0f), Color(255, 255, 255, 255), Vector2(0.0f, 0.0f), },
        { Vector3( scale.x/2,  scale.y/2,  scale.z/2), Vector3(-1.0f,  0.0f,  0.0f), Color(255, 255, 255, 255), Vector2(1.0f, 0.0f), },
        { Vector3( scale.x/2, -scale.y/2, -scale.z/2), Vector3(-1.0f,  0.0f,  0.0f), Color(255, 255, 255, 255), Vector2(0.0f, 1.0f), },
        { Vector3( scale.x/2, -scale.y/2,  scale.z/2), Vector3(-1.0f,  0.0f,  0.0f), Color(255, 255, 255, 255), Vector2(1.0f, 1.0f), },
        // 左面
        { Vector3(-scale.x/2,  scale.y/2,  scale.z/2), Vector3(-1.0f,  0.0f,  0.0f), Color(255, 255, 255, 255), Vector2(0.0f, 0.0f), },
        { Vector3(-scale.x/2,  scale.y/2, -scale.z/2), Vector3(-1.0f,  0.0f,  0.0f), Color(255, 255, 255, 255), Vector2(1.0f, 0.0f), },
        { Vector3(-scale.x/2, -scale.y/2,  scale.z/2), Vector3(-1.0f,  0.0f,  0.0f), Color(255, 255, 255, 255), Vector2(0.0f, 1.0f), },
        { Vector3(-scale.x/2, -scale.y/2, -scale.z/2), Vector3(-1.0f,  0.0f,  0.0f), Color(255, 255, 255, 255), Vector2(1.0f, 1.0f), },

    };

    const int indexList[faceNum*3] =
    {
        0, 1, 2,
        1, 3, 2,

        4, 5, 6,
        5, 7, 6,

        8, 9, 10,
        9, 11, 10,

        12, 13, 14,
        13, 15, 14,

        16, 17, 18,
        17, 19, 18,

        20, 21, 22,
        21, 23, 22,
    };

    for (int i = 0; i < (int)pMesh->vertexNum; i++)
    {
        pMesh->pVertex[i] = vertexList[i];
    }
    for (int i = 0; i < (int)pMesh->faceNum * 3; i++)
    {
        pMesh->pIndexList[i] = indexList[i];
    }


    Vertex* pVtx = pMesh->pVtxBuf->Lock();
    for (int i = 0; i < (int)pMesh->vertexNum; i++)
    {
        *pVtx = vertexList[i];
        pVtx++;
    }
    pMesh->pVtxBuf->Unlock();

    int* pIdx = pMesh->pIdxBuf->Lock();
    for (int i = 0; i < (int)pMesh->faceNum*3; i++)
    {
        *pIdx = indexList[i];
        pIdx++;
    }
    pMesh->pIdxBuf->Unlock();

    
    pMesh->pSubsetList[0].startIndex    = 0;
    pMesh->pSubsetList[0].count         = faceNum*3;
    pMesh->pSubsetList[0].materialIndex = 0;

    pMesh->pMaterialList[0].diffuse     = ColorValue(1.0f, 1.0f, 1.0f, 1.0f);
    pMesh->pMaterialList[0].ambient     = ColorValue(1.0f, 1.0f, 1.0f, 1.0f);
    pMesh->pMaterialList[0].emissive    = ColorValue(0.0f, 0.0f, 0.0f, 1.0f);
    pMesh->pMaterialList[0].specular    = ColorValue(0.0f, 0.0f, 0.0f, 1.0f);
    pMesh->pMaterialList[0].power       = 0.0f;
    pMesh->pMaterialList[0].pTexture    = NULL;

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

/*****************************************************************************/
/*!
@file   Texture.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/


/*  インクルード
******************************************************************************/


#include "Texture.h"
#include "TextureFactory.h"


using Framework::Texture;
using Framework::TextureFactory;


/*  変数宣言
******************************************************************************/


TextureFactory* Texture::pFactory = NULL;
Texture*        Texture::pFirst = NULL;
Texture*        Texture::pLast = NULL;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/

Texture::Texture() : pData(NULL), useNum(0), pNext(NULL), pPrev(NULL)
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

Texture::~Texture()
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
@brief  テクスチャ作成
@param  pInfo       テクスチャ情報
@param  pBuffer     情報
@return Texture*    テクスチャへのポインタ
******************************************************************************/

Texture* Texture::Create(const Info *pInfo, void *pBuffer)
{
    // 生成できない場合NULLを返す
    if (!pFactory)
    {
        return NULL;
    }

    return pFactory->Create(pInfo, pBuffer);
}

/******************************************************************************
@brief  テクスチャ読み込み
@param  FileName    ファイル名
******************************************************************************/

Texture* Texture::Load(const char *FileName)
{
    // 生成できない場合NULLを返す
    if (!pFactory)
    {
        return NULL;
    }
    // ファイル名がない場合NULLを返す
    if (strcmp(FileName, "") == 0)
    {
        return NULL;
    }
    // すでに生成されていればそれを返す
    for (Texture* p = pFirst; p != NULL; p = p->pNext)
    {
        if (!strcmp(p->filePath, FileName))
        {
            p->useNum++;    // 使用オブジェクト数の増加
            return p;
        }
    }

    Texture* pTex = pFactory->Load(FileName);
    strcpy_s(pTex->filePath, 256, FileName);
    return pTex;
}

/******************************************************************************
@brief  テクスチャ開放
******************************************************************************/

void Texture::Release()
{
    useNum--;

    if (useNum <= 0)
    {
        if (pData != NULL)
        {
            delete[] pData;
            pData = NULL;
        }
        delete this;
    }
}

/******************************************************************************
@brief  テクスチャ情報設定
@param  format      フォーマット
@param  width       横幅
@param  height      縦幅
@param  bit         ビット数
@return Texture     テクスチャ情報設定
******************************************************************************/

void Texture::SetInfo
(
Texture::Format format,
unsigned int    width,
unsigned int    height,
unsigned int    bit
)
{
    info.format     = format;
    info.width      = width;
    info.height     = height;
    info.bit        = bit;
    info.pitch      = width * 4;
    info.bufferSize = width * height * 4;
}

/******************************* 実装ここまで ********************************/

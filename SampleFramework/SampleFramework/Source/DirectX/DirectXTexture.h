#pragma once
/*****************************************************************************/
/*!
@file   DirectXTexture.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "DirectX.h"
#include "..\Framework\Texture\Texture.h"


/*  クラス定義
******************************************************************************/


namespace DirectX
{
    class Texture : public Framework::Texture
    {
    public:
        Texture();
        virtual ~Texture();

        /// リソース取得
        LPDIRECT3DTEXTURE9 GetResource() { return pTex; }

        /// テクスチャ作成
        void Create(LPDIRECT3DDEVICE9 pDev, const Info *pInfo, void *pBuffer)
        {
            this->info = *pInfo;
            unsigned char *pNewBuf = new unsigned char[pInfo->bufferSize];
            memcpy(pNewBuf, pBuffer, pInfo->bufferSize);
            this->pData = pNewBuf;

            // DirectXのテクスチャ生成
            D3DFORMAT fmt = (pInfo->format == RGBA8888) ? (D3DFMT_A8R8G8B8) : (D3DFMT_A8R8G8B8);
            if (FAILED(pDev->CreateTexture(pInfo->width, pInfo->height, 0, 0, fmt, D3DPOOL_MANAGED, &pTex, 0)))
                return;
            D3DLOCKED_RECT r;
            if (FAILED(pTex->LockRect(0, &r, 0, 0)))
                return;
            memcpy(r.pBits, pBuffer, pInfo->bufferSize);
            pTex->UnlockRect(0);

        }
        void Release();

    private:
        LPDIRECT3DTEXTURE9 pTex;
    };
}


/******************************* ヘッダここまで ******************************/

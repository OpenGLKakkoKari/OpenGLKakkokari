#pragma once
/*****************************************************************************/
/*!
@file   DirectXTexture.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "DirectX.h"
#include "..\Framework\Texture\Texture.h"


/*  �N���X��`
******************************************************************************/


namespace DirectX
{
    class Texture : public Framework::Texture
    {
    public:
        Texture();
        virtual ~Texture();

        /// ���\�[�X�擾
        LPDIRECT3DTEXTURE9 GetResource() { return pTex; }

        /// �e�N�X�`���쐬
        void Create(LPDIRECT3DDEVICE9 pDev, const Info *pInfo, void *pBuffer)
        {
            this->info = *pInfo;
            unsigned char *pNewBuf = new unsigned char[pInfo->bufferSize];
            memcpy(pNewBuf, pBuffer, pInfo->bufferSize);
            this->pData = pNewBuf;

            // DirectX�̃e�N�X�`������
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


/******************************* �w�b�_�����܂� ******************************/

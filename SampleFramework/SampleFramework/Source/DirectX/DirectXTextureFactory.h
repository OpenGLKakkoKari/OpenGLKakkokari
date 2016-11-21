#pragma once
/*****************************************************************************/
/*!
@file   DirectXTextureFactory.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "DirectXTexture.h"
#include "..\Framework\Texture\TextureFactory.h"
#include "..\Framework\File\Reader\TextureReader.h"


/*  �N���X��`
******************************************************************************/


namespace DirectX
{
    class TextureFactory : public Framework::TextureFactory
    {
    public:
        TextureFactory(LPDIRECT3DDEVICE9 pDevice) : pDev(pDevice) {}
        virtual ~TextureFactory() {}

        /// �e�N�X�`���쐬
        virtual Framework::Texture *Create(const Framework::Texture::Info *pInfo, void* pBuffer)
        {
            DirectX::Texture *pNewTex = new DirectX::Texture;
            pNewTex->Create(pDev, pInfo, pBuffer);
            return pNewTex;
        }

        /// �e�N�X�`���ǂݍ���
        virtual Framework::Texture *Load(const char *FileName)
        {
            DirectX::Texture *pNewTex = new DirectX::Texture;
            Framework::Texture* pTex = Framework::File::TextureReader::Load(FileName, true);
            pNewTex->Create(pDev, &pTex->info, pTex->pData);
            pTex->Release();
            return pNewTex;
        }
    private:
        LPDIRECT3DDEVICE9 pDev;
    };
}


/****************************** �w�b�_�����܂� *******************************/

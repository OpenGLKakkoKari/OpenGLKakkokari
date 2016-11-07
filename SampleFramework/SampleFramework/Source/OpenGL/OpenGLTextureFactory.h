#pragma once
/******************************************************************************
/*!
@file   OpenGLTextureFactory.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "OpenGLTexture.h"
#include "..\Framework\Texture\TextureFactory.h"
#include "..\Framework\File\Reader\TextureReader.h"


/*  �N���X��`
******************************************************************************/


namespace OpenGL
{
    class TextureFactory : public Framework::TextureFactory
    {
    public:
        TextureFactory() {}
        virtual ~TextureFactory() {}

        /// �e�N�X�`���쐬
        virtual Framework::Texture *Create(const Framework::Texture::Info *pInfo, void* pBuffer)
        {
            Texture *pNewTex = new Texture;
            pNewTex->Create(pInfo, pBuffer);
            return pNewTex;
        }

        /// �e�N�X�`���ǂݍ���
        virtual Framework::Texture *Load(const char *FileName)
        {
            OpenGL::Texture *pNewTex = new OpenGL::Texture;
            Framework::Texture* pTex = Framework::File::TextureReader::Load(FileName);
            pNewTex->Create(&pTex->info, pTex->pData);
            pTex->Release();
            pTex = NULL;
            return pNewTex;
        }
    };
}


/****************************** �w�b�_�����܂� *******************************/

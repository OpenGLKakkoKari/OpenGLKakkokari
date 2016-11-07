#pragma once
/******************************************************************************
/*!
@file   TextureFactory.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Texture.h"


/*  �N���X��`
******************************************************************************/


namespace Framework
{
    class TextureFactory
    {

    public:
        TextureFactory() {}
        virtual ~TextureFactory() {}

        /// �e�N�X�`���쐬
        virtual Texture *Create(const Texture::Info *pInfo, void* pBuffer) = 0;
        virtual Texture *Load(const char *FileName) = 0;
    };
}


/****************************** �w�b�_�����܂� *******************************/

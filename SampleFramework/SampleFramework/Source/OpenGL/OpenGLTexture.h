#pragma once
/******************************************************************************
/*!
@file   OpenGLTexture.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "OpenGL.h"
#include "..\Framework\Texture\Texture.h"


/*  �N���X��`
******************************************************************************/


namespace OpenGL
{
    class Texture : public Framework::Texture
    {
    public:
        Texture() : texture(0){}
        virtual ~Texture() {}

        /// ���\�[�X�擾
        virtual const void *GetResource() { return pData; }

        /// �e�N�X�`���쐬
        void Create(const Info *pInfo, void *pBuffer)
        {
            this->info = *pInfo;
            unsigned char *pNewBuf = new unsigned char[pInfo->bufferSize];
            memcpy(pNewBuf, pBuffer, pInfo->bufferSize);
            this->pData = pNewBuf;

            // OpenGL�̃e�N�X�`������
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            // �~�b�v�}�b�v�ݒ�
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // �g�厞�ߖT
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // �k�����ߖT

            //�@�e�N�X�`���̊��蓖��
            int internalFormat = (info.format == Texture::RGBA8888) ? (GL_RGBA) : (GL_RGBA);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,                  // mipmap
                internalFormat,
                info.width,         // width
                info.height,        // height
                0,                  // border
                internalFormat,
                GL_UNSIGNED_BYTE,
                GetResource()
                );
        }

        void Release()
        {
            if (IsReleased())
            {
                glDeleteTextures(1, &texture);
            }
            Framework::Texture::Release();
        }

        unsigned int texture;
    };
}


/******************************* �w�b�_�����܂� ******************************/

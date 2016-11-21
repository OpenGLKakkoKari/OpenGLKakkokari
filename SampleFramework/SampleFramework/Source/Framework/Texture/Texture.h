#pragma once
/******************************************************************************
/*!
@file   Texture.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �N���X��`
******************************************************************************/


#include <stdio.h>
#include <string.h>


/*  �N���X��`
******************************************************************************/


namespace Framework
{
    class TextureFactory;
    class Texture
    {
    public:
        enum Format
        {
            RGBA8888,
            RGBX8888
        };
        struct Info
        {
            Format format;
            unsigned int width;
            unsigned int height;
            unsigned int bit;
            unsigned int pitch;
            unsigned int bufferSize;
            Info() : width(), height(), bit(), bufferSize(), pitch(), format(RGBA8888) {}
        };

        Texture();
        virtual ~Texture();

        static void RegisterFactory(TextureFactory *pTextureFactory) { pFactory = pTextureFactory; }

        static Texture* Create(const Info *pInfo, void *pBuffer);
        static Texture* Load(const char *FileName);

        virtual void Release();

        Info GetInfo() { return info; }

        void SetInfo
            (
            Texture::Format format,
            unsigned int    width,
            unsigned int    height,
            unsigned int    bit
            );


        void*                   pData;          // �f�[�^�ւ̃|�C���^
        Info                    info;           // �e�N�X�`�����

    protected:
        bool                    IsReleased()    // �J������钼�O���ǂ���
        {
            return useNum - 1 <= 0;
        }

        static TextureFactory*  pFactory;
        int                     useNum;         // ���̃e�N�X�`���̎Q�Ɛ�

    private:
        static Texture*         pFirst;         // �e�N�X�`�����X�g�̍őO��
        static Texture*         pLast;          // �e�N�X�`�����X�g�̍Ō��

        Texture*                pNext;
        Texture*                pPrev;
        char                    filePath[256];  // ���̃e�N�X�`���̃t�@�C���p�X
    };
}


/****************************** �w�b�_�����܂� *******************************/

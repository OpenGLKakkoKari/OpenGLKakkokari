#pragma once
/******************************************************************************
/*!
@file   Reader.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �}�N����`
******************************************************************************/


#pragma warning(disable : 4996)


/*  �C���N���[�h
******************************************************************************/


#include <windows.h>


/*  �N���X��`
******************************************************************************/


namespace Framework
{
    namespace File
    {
        class Reader
        {
        public:
            virtual void Load(const char *FileName){}

        protected:
            static void GetExtension(const char *FilePath);
            static void CurrentDirectory(const char *FilePath);

            static char fileName[MAX_PATH];     // �t�@�C����
            static char dir[MAX_PATH];          // �J�����g�f�B���N�g��
            static char ext[16];                // �g���q
            static int  fileSize;               // �t�@�C���T�C�Y
        };
    }
}


/****************************** �w�b�_�����܂� *******************************/
#pragma once
/******************************************************************************
/*!
@file   BinaryWriter.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Writer.h"


/*  �N���X��`
******************************************************************************/


namespace Framework
{
    namespace File
    {
        class BinaryWriter : public Writer
        {
        public:
            void Write(const char *FileName, void *pData, int size);

        public:
            static char fileName[MAX_PATH];     // �t�@�C����
            static char ext[16];                // �g���q
            static int  fileSize;               // �t�@�C���T�C�Y
        };
    }
}


/****************************** �w�b�_�����܂� *******************************/
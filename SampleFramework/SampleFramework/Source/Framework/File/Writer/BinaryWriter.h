#pragma once
/******************************************************************************
/*!
@file   BinaryWriter.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Writer.h"


/*  クラス定義
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
            static char fileName[MAX_PATH];     // ファイル名
            static char ext[16];                // 拡張子
            static int  fileSize;               // ファイルサイズ
        };
    }
}


/****************************** ヘッダここまで *******************************/
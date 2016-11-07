#pragma once
/******************************************************************************
/*!
@file   Reader.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  マクロ定義
******************************************************************************/


#pragma warning(disable : 4996)


/*  インクルード
******************************************************************************/


#include <windows.h>


/*  クラス定義
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

            static char fileName[MAX_PATH];     // ファイル名
            static char dir[MAX_PATH];          // カレントディレクトリ
            static char ext[16];                // 拡張子
            static int  fileSize;               // ファイルサイズ
        };
    }
}


/****************************** ヘッダここまで *******************************/
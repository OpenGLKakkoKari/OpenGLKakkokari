/*****************************************************************************/
/*!
@file   BinaryWriter.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "BinaryWriter.h"
#include "../File.h"

using Framework::File::BinaryWriter;
using Framework::File::File;


/*  変数宣言
******************************************************************************/


char BinaryWriter::fileName[MAX_PATH];
char BinaryWriter::ext[16];
int  BinaryWriter::fileSize;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  ファイル書き込み
@param  FileName        ファイルパス
@param  pData           書き込むデータ
@param  size            書き込むサイズ
******************************************************************************/

void BinaryWriter::Write(const char *FileName, void *pData, int size)
{
    File file;
    if (file.Open(FileName, "wb"))
    {
        printf("%s file open error!!\n", FileName);
    }

    file.Seek(0, SEEK_SET);
    file.Write(pData, size, 1);

    file.Close();
}

/******************************* 関数ここまで ********************************/

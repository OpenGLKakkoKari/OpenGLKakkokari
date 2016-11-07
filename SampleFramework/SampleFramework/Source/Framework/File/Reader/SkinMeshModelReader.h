#pragma once
/******************************************************************************
/*!
@file   SkinMeshModelReader.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  マクロ定義
******************************************************************************/


#pragma warning(disable : 4996)


/*  インクルード
******************************************************************************/


#include "Reader.h"
#include "..\..\Mesh\SkinMeshModel.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    namespace File
    {
        class SkinMeshModelReader : public Reader
        {
        public:
            static SkinMeshModel* Load(const char *FileName);
        };
    }
}


/****************************** ヘッダここまで *******************************/
#pragma once
/******************************************************************************
/*!
@file   EffectReader.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Reader.h"
#include "../../Effect/Effect.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    namespace File
    {
        class EffectReader : public Reader
        {
        public:
            static Effect* LoadEffect(const char *FileName);
        };
    }
}


/****************************** ヘッダここまで *******************************/
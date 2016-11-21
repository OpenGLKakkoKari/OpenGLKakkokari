#pragma once
/******************************************************************************
/*!
@file   NumberSprite.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Sprite.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class NumberSprite : public Sprite
    {
    public:
        NumberSprite();
        virtual ~NumberSprite();

        void SetNumber(int number);

        static NumberSprite* Create(const Vector2& pos, const Vector2& size, Color col, int number);
        static NumberSprite* Create(const Vector2& pos, const Vector2& size, Color col, const char *fileName, int number);

    protected:
        void SetNumberVertexUV();

        int number_;
    };
}


/****************************** ヘッダここまで *******************************/

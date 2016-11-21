#pragma once
/******************************************************************************
/*!
@file   Sprite.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Polygon.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class Sprite : public Polygon
    {
    public:
        Sprite();
        virtual ~Sprite();

        virtual void Draw();
        virtual void SetPosition(const Vector2& pos)    { pos_ = Vector3(pos.x, pos.y, 0.0f); }
        virtual void SetRotation(float rot)             { rot_ = Vector3(0.0f, 0.0f, rot); }

        static Sprite* Create(const Vector2& pos, const Vector2& size, Color col);
        static Sprite* Create(const Vector2& pos, const Vector2& size, Color col, const char *FileName);
    };
}


/****************************** ヘッダここまで *******************************/

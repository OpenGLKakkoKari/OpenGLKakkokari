#pragma once
/******************************************************************************
/*!
@file   Billboard.h
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
    class Billboard : public Polygon
    {
    public:
        enum TYPE
        {
            BILLBOARD_DEFAULT,
            BILLBOARD_YENABLE,
            BILLBOARD_ZROTATION,
            BILLBOARD_NONE,
        };

        Billboard();
        virtual ~Billboard();

        virtual void Draw();

        static Billboard* Create(const Vector3& pos, const Vector2& size, Color col, TYPE type, const char *FileName);
        void SetBillboardType(TYPE type){ this->type = type; }

    protected:
        TYPE     type;
    };
}


/****************************** ヘッダここまで *******************************/

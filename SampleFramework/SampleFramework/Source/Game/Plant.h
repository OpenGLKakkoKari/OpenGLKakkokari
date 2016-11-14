#pragma once
/******************************************************************************
/*!
@file   Plant.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/


/*  インクルード
******************************************************************************/


#include "..\Framework\Billboard.h"


/*  クラス定義
******************************************************************************/


namespace Game
{
    class Plant : public Framework::Billboard
    {
    public:
        Plant();
        ~Plant();

        void Draw();
        void SetPolygonNum(int polygonNum){ polygonNum_ = polygonNum; }

        static Plant* Create(const char* FileName,
            const Framework::Vector3& pos,
            const Framework::Vector2& size,
            int polygonNum);
    private:
        int polygonNum_;
    };
}


/******************************* ヘッダここまで ******************************/

#pragma once
/******************************************************************************
/*!
@file   Score.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/


/*  インクルード
******************************************************************************/


#include "..\Framework\GameObject.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class NumberSprite;
    class Vector2;
};
namespace Game
{
    class Score : public Framework::GameObject
    {
    public:
        Score();
        ~Score();

        void Init();
        void Uninit(){}
        void Update();
        void SetValue(int value){ value_ = value; }
        void AddValue(int value){ value_ += value; }

        static Score* Create(const char* FileName,
            const Framework::Vector3& pos,
            const Framework::Vector2& size,
            int value);

        static Score* Create(const char* FileName,
            const Framework::Vector3& pos,
            const Framework::Vector2& size);

    private:
        int                         value_;
        int                         digits_;
        Framework::NumberSprite**   pNumberList;
    };
}


/******************************* ヘッダここまで ******************************/

#pragma once
/******************************************************************************
/*!
@file   Explosion.h
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
    class AnimationBillboard;
    class Vector2;
};
namespace Game
{
    enum { BILLBOARD_NUM = 32 };
    class Explosion : public Framework::GameObject
    {
    public:
        Explosion();
        ~Explosion();

        void Init();
        void Uninit(){}
        void Update();

        void Create(const Framework::Vector3& pos);

    private:
        int                             frameCount[BILLBOARD_NUM];
        int                             frameMax;
        Framework::AnimationBillboard*  pBillboard[BILLBOARD_NUM];
    };
}


/******************************* ヘッダここまで ******************************/

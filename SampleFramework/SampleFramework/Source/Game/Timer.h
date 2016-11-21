#pragma once
/******************************************************************************
/*!
@file   Timer.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "../Framework/GameObject.h"
#include "../Framework/NumberSprite.h"

/*  クラス定義
******************************************************************************/


namespace Game
{
    class Timer : public Framework::GameObject
    {
    public:
		enum { DIGIT_MAX = 2 };
		enum { TIME = 11 } ;
        Timer();
        virtual ~Timer();

        virtual void Init();
        virtual void Uninit(){}
        virtual void Update();


    private:
        Framework::NumberSprite* pSprite[DIGIT_MAX];

		int        time_;		//現在のタイム
		int        timeCnt_ ;	//タイムカント
    };
}


/****************************** ヘッダここまで *******************************/

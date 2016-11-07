#pragma once
/*****************************************************************************/
/*!
@file   Effect.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Emitter.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class Effect : public GameObject
    {
    public:
        enum {EMITTER_MAX = 4};

        Effect();
        ~Effect();

        void Init(){}
        void Uninit(){}
        void Update();
        
        void Play()                 { isPlaying = true; }
        void Pause()                { isPlaying = false; }
        void SetLoop(bool isLoop)   { this->isLoop = isLoop; }

        int             startTime;
        int             endTime;
        int             timer;
        bool            isPlaying;
        bool            isLoop;
        int             emitterNum;
        Emitter         **pEmitterList;
    };
}


/****************************** ヘッダここまで *******************************/

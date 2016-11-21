#pragma once
/*****************************************************************************/
/*!
@file   Effect.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Emitter.h"


/*  �N���X��`
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


/****************************** �w�b�_�����܂� *******************************/

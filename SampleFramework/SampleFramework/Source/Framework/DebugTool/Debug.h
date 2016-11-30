#pragma once
/******************************************************************************
/*!
@file   Debug.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/


/*  インクルード
******************************************************************************/


#include "Text.h"
#include "../Sprite.h"
#include "Tweaker.h"
#include "DebugTimer.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class Debug
    {
    public:
        Debug();
        virtual ~Debug();

        void Init();
        void Uninit();
        void Update();

        void Print(const char *format, ...);

        void Add(char* DirName) { pTweaker->Add(DirName); }
        void Add(const char* Text, bool* value) { pTweaker->Add(Text, value); }
        void Add(const char* Text, int*  value) { pTweaker->Add(Text, value); }
        void Add(const char* Text, float* value) { pTweaker->Add(Text, value); }
        void Add(const char* Text, Vector2* value) { pTweaker->Add(Text, value); }
        void Add(const char* Text, Vector3* value) { pTweaker->Add(Text, value); }
        void Add(const char* Text, Color* value) { pTweaker->Add(Text, value); }

        void Delete(const char* Text){ pTweaker->Delete(Text); }

        void SetDirectory(char* DirName) { pTweaker->SetDirectory(DirName); }

        void Reset() { pTweaker->Reset(); }

        void TimerStart(){ pTimer->Start(); }
        void TimerEnd(){ pTimer->End(); }
        float GetTimerSecond(){ return pTimer->GetSecond(); }

        void SetUpdateTime(float sec) { msecUpdate = sec; }
        void SetDrawTime(float sec) { msecDraw = sec; }

    private:
        Tweaker::Tweaker*   pTweaker;
        Text*               pText;
        Sprite*             pSprite;
        DebugTimer*         pTimer;

        float               msecUpdate;
        float               msecDraw;

        bool                isShow;
        bool                isTexture;
        bool                isWireFrame;
        bool                isCulling;
        bool                isTweaker;
        bool                isBackground;
    };
}


/******************************* ヘッダここまで ******************************/

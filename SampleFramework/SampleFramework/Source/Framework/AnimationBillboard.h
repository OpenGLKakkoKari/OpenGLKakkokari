#pragma once
/******************************************************************************
/*!
@file   AnimationBillboard.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Billboard.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    struct AnimationData
    {
        int wDiv;
        int hDiv;
        int pattern;
        int patternMax;
        bool loop;

        AnimationData() 
            : wDiv(0), hDiv(0),
            pattern(0), patternMax(0),
            loop(false)
        {}

        AnimationData(int wDiv, int hDiv, int patternMax)
            : wDiv(wDiv), hDiv(hDiv),
            pattern(0), patternMax(patternMax),
            loop(false)
        {}
    };

    class AnimationBillboard : public Billboard
    {
    public:

        AnimationBillboard();
        virtual ~AnimationBillboard();

        static AnimationBillboard* Create(const Vector3& pos, const Vector2& size, Color col, TYPE type, AnimationData animData, const char *FileName);
        void SetAnimationData(AnimationData animData){ anim_ = animData; }
        void SetPattern(int index);
        void NextPattern();
        bool IsAnimationEnd(){ return (anim_.loop == false) && (anim_.pattern == anim_.patternMax - 1); }

    protected:
        AnimationData anim_;
    };
}


/****************************** ヘッダここまで *******************************/

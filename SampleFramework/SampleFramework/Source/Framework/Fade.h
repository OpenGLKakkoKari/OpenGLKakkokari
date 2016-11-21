#pragma once
/******************************************************************************
/*!
@file   Fade.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Scene.h"
#include "Sprite.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class Fade : public Sprite
    {
    public:
        enum Type
        {
            FADE_NONE,
            FADE_IN,
            FADE_OUT,
            FADE_MAX,
        };

        Fade();
        ~Fade();

        void Update();

        void SetFade(Type fadeType, Scene* nextScene);
        Type GetFade(){ return nowFade; }
        void SetFrame(unsigned int changeFrame){ unit = 255 / changeFrame + 1; }

    protected:
        Color               color;
        Type                nowFade;
        Scene*              nextScene_;
        int                 unit;
    };
}


/******************************* ヘッダここまで ******************************/

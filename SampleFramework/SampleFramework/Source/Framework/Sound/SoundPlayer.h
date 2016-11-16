#pragma once
/******************************************************************************
/*!
@file   SoundPlayer.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "..\Math\Vector3.h"
#include "Sound.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class SoundPlayer
    {
    public:
        enum { TAG_MAX = 64 };
        enum State
        {
            SOUND_PLAYING,
            SOUND_STOPPED,
            SOUND_PAUSED,
            SOUND_INITIAL,
        };

        SoundPlayer();
        virtual ~SoundPlayer();

        void Load(const char* tag, const char* FileName);
        void Unload();

        void Play(bool loop = false);

        void Pause();
        void Stop();

        State GetState();

        const char* GetTag(){ return tag; }
        const char* GetFileName(){ return sound.FileName; }
        bool Use(){ return use; }

    private:
        unsigned int    buffer;
        unsigned int    source;
        Sound           sound;
        char            tag[TAG_MAX];
        bool            use;

        Vector3         ListenerPos;
        Vector3         ListenerVel;
        Vector3         ListenerOri;
        Vector3         SourcePos;
        Vector3         SourceVel;
    };
}


/******************************* ヘッダここまで ******************************/

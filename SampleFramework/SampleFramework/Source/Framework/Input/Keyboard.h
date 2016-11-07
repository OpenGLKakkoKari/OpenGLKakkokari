#pragma once
/******************************************************************************
/*!
@file   Input.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include <Windows.h>


/*  クラス定義
******************************************************************************/


namespace Framework
{
    namespace Input
    {
        class Keyboard
        {
        public:
            enum {KEY_MAX = 256};

            Keyboard();
            virtual ~Keyboard();

            void Update();

            bool Press(int Key){ return (press[Key] & 0x80) ? (true) : (false); }
            bool Trigger(int Key){ return (trigger[Key] & 0x80) ? (true) : (false); }
            bool Release(int Key){ return (release[Key] & 0x80) ? (true) : (false); }
            bool Repeat(int Key){ return (repeat[Key] & 0x80) ? (true) : (false); }

            void SetRepeatTerm(int termFrame){ repeatTerm = termFrame; }

        private:
            BYTE press[KEY_MAX];
            BYTE trigger[KEY_MAX];
            BYTE release[KEY_MAX];
            BYTE repeat[KEY_MAX];

            int repeatCnt[KEY_MAX];
            int repeatTerm;
        };
    }
}


/****************************** ヘッダここまで *******************************/

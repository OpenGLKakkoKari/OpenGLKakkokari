#pragma once
/******************************************************************************
/*!
@file   Text.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "../Sprite.h"


/*  マクロ定義
******************************************************************************/


#define TEXT_BUFFER_SIZE (2048)


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class Text : public Sprite
    {
    public:
        enum FONT_TYPE
        {
            FONT_TYPE_MEIRYO,
            FONT_TYPE_5x5,
            FONT_TYPE_OSAKA,

            FONT_TYPE_MAX
        };
        enum FONT_SIZE
        {
            FONT_SIZE_S,

            FONT_SIZE_MAX
        };

        Text();
        Text(FONT_TYPE FontType, FONT_SIZE FontSize = FONT_SIZE_S);
        virtual ~Text();

        void Draw();

        void ClearBuffer();
        void Print(const char *format, ...);
        
    protected:
        Vector2 GetUVPos(int charCode);

        char         buffer[TEXT_BUFFER_SIZE];
        int          charNum;
        FONT_TYPE    fontType;
        FONT_SIZE    fontSize;
    };
}


/****************************** ヘッダここまで *******************************/

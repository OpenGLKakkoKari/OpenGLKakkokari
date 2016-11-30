/*****************************************************************************/
/*!
@file   Text.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Text.h"

#include "../Manager.h"
#include <stdarg.h>
#include <crtdbg.h>


using Framework::Text;
using Framework::Vector2;
using Framework::Color;
using Framework::Sprite;


/*  静的変数宣言
******************************************************************************/


static char* TextureNameTable[Text::FONT_TYPE_MAX][Text::FONT_SIZE_MAX] =
{
    "data/TEXTURE/DebugTool/Meiryo/string_mini.png",
    "data/TEXTURE/DebugTool/5x5/string_mini.png",
    "data/TEXTURE/DebugTool/Osaka/string_mini.png"
};

static Vector2 FontSizeTable[Text::FONT_TYPE_MAX][Text::FONT_SIZE_MAX] = 
{
    Vector2(23.0f, 24.0f),
    Vector2(17.0f, 26.0f),
    Vector2(15.0f, 20.0f),
};

static Vector2 FontIntervalTable[Text::FONT_TYPE_MAX][Text::FONT_SIZE_MAX] =
{
    Vector2(15.0f, 12.0f),
    Vector2(9.0f, 14.0f),
    Vector2(7.0f, 8.0f),
};


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
@param  FontType        フォントタイプ
@param  FontSize        フォントサイズ
******************************************************************************/

Text::Text()
{
    charNum = 0;
    SetPriority(-100);

    SetTexture(TextureNameTable[FONT_TYPE_OSAKA][FONT_SIZE_S]);
    fontType = FONT_TYPE_OSAKA;
    fontSize = FONT_SIZE_S;
    SetUse(true);
}


Text::Text(FONT_TYPE FontType, FONT_SIZE FontSize)
{
    charNum = 0;
    SetPriority(-100);

    SetTexture(TextureNameTable[FONT_TYPE_OSAKA][FONT_SIZE_S]);
    fontType = FontType;
    fontSize = FontSize;
    SetUse(true);
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

Text::~Text()
{
}

/******************************************************************************
@brief  描画処理
******************************************************************************/

void Text::Draw(void)
{
    Vector2 uv;
    Vector2 size = FontSizeTable[fontType][fontSize];
    Vector2 base = Vector2(size.x / 2, (size.y-12.0f) / 2);
    int column = 0;
    int row = 0;

    for (int i = 0; i < charNum; i++)
    {
        if (buffer[i] == '\n')
        {
            column = 0;
            row++;
        }
        else
        {
            uv = GetUVPos(buffer[i]);
            SetVertexUV(Vector2(uv.x, uv.y), Vector2(uv.x + 0.1f, uv.y + 0.1f));
            SetScale(Vector2(size.x, size.y));
            SetPosition(Vector2(
                base.x + column * (size.x - FontIntervalTable[fontType][fontSize].x),
                base.y + row    * (size.y - FontIntervalTable[fontType][fontSize].y)));
            Sprite::Draw();

            column++;
        }
    }
    ClearBuffer();
}

/******************************************************************************
@brief  バッファクリア処理
******************************************************************************/

void Text::ClearBuffer(void)
{
    charNum = 0;
}

/******************************************************************************
@brief  テキスト書き込み処理
@param  format          表示するテキスト
******************************************************************************/

void Text::Print(const char *format, ...)
{

    va_list args;
    va_start(args, format);
    vsprintf_s(&buffer[charNum], TEXT_BUFFER_SIZE - charNum, format, args);
    
    int i = 0;
    while (buffer[i] != '\0')
    {
        i++;
    }

    charNum = i;

    va_end(args);
}

/******************************************************************************
@brief  UV座標取得
@param  charCode        文字コード
@return Vector2         UV座標
******************************************************************************/

Vector2 Text::GetUVPos(int charCode)
{
    Vector2 uv;
    char index;

    if (' ' <= charCode && charCode <= '~' + 2)
        index = charCode - ' ';
    else
        index = 0;

    uv.x = index % 10 * 0.1f;
    uv.y = index / 10 * 0.1f;

    return uv;
}

/******************************** 実装ここまで *******************************/

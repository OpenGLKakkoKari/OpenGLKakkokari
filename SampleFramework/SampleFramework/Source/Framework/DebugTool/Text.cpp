/*****************************************************************************/
/*!
@file   Text.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Text.h"

#include "../Manager.h"
#include <stdarg.h>
#include <crtdbg.h>


using Framework::Text;
using Framework::Vector2;
using Framework::Color;
using Framework::Sprite;


/*  �ÓI�ϐ��錾
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


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
@param  FontType        �t�H���g�^�C�v
@param  FontSize        �t�H���g�T�C�Y
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
@brief  �f�X�g���N�^
******************************************************************************/

Text::~Text()
{
}

/******************************************************************************
@brief  �`�揈��
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
@brief  �o�b�t�@�N���A����
******************************************************************************/

void Text::ClearBuffer(void)
{
    charNum = 0;
}

/******************************************************************************
@brief  �e�L�X�g�������ݏ���
@param  format          �\������e�L�X�g
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
@brief  UV���W�擾
@param  charCode        �����R�[�h
@return Vector2         UV���W
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

/******************************** ���������܂� *******************************/

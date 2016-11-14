/******************************************************************************
/*!
@file   TokenAnalyzer.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "TokenAnalyzer.h"
#include <string.h>
#include <stdlib.h>


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/

TokenAnalyzer::TokenAnalyzer(const char* string) : str(string), pos(0)
{
    strcpy_s(token, TOKEN_SIZE, "");
    strcpy_s(skipChars, SKIPCHAR_SIZE, " \t\n\r,;\"");
}

/******************************************************************************
@brief  スキップする文字列を設定
@param  skipChars   スキップする単語の文字列
******************************************************************************/

void TokenAnalyzer::SetSkipChars(const char* skipChars)
{
    strcpy_s(this->skipChars, SKIPCHAR_SIZE, skipChars);
}

/******************************************************************************
@brief  トークンの取得
@return char*   取得したトークン
******************************************************************************/

char* TokenAnalyzer::GetToken()
{
    // トークンを初期化
    memset(token, '\0', TOKEN_SIZE);

    char *q = token;

    // 現在の文字がスキップ文字でない限りトークンに格納
    while (!IsScriptEnd() && !strchr(skipChars, str[pos]))
    {
        // 文字をトークン情報に格納
        *q = str[pos];
        if (*q == '#')
        {
            while (str[pos] != '\n')
            {
                *q = str[pos];
                q++;
                pos++;
            }
            break;
        }
        q++;
        // 次の文字を調べる
        pos++;
    }
    // 現在の文字がスキップ文字の場合進む
    while (!IsScriptEnd() && strchr(skipChars, str[pos]))
    {
        // 次の文字を調べる
        pos++;
    }

    return token;
}

/******************************************************************************
@brief  浮動小数点型の値を文字列から取得
@return float   取得した浮動小数点型の値
******************************************************************************/

float TokenAnalyzer::GetFloatToken()
{
    GetToken();
    return (float)atof(token);
}

/******************************************************************************
@brief  符号ありの整数型の値を文字列から取得
@return float   取得した符号ありの整数型の値
******************************************************************************/

int TokenAnalyzer::GetIntToken()
{
    GetToken();
    return (int)atoi(token);
}

/******************************************************************************
@brief  トークンと文字列を比較
@param  cmpStr      比較文字列
@retval true        トークンと比較文字列が一致
@retval false       トークンと比較文字列が不一致
******************************************************************************/

bool TokenAnalyzer::CheckToken(const char* cmpStr)
{
    if (strcmp(token, cmpStr) == 0)
        return true;
    else
        return false;
}

/******************************************************************************
@brief  波括弧のブロックを飛ばす
******************************************************************************/

void TokenAnalyzer::SkipBracket()
{
    while (!IsScriptEnd())
    {
        GetToken();
        if (strchr(token, '{')) break;
    }
    // 現在の階層カウンター
    // 深くなる度に+1
    // 抜ける度に  -1

    int count = 1;
    while (!IsScriptEnd() && count > 0)
    {
        GetToken();
        if (strchr(token, '{')) count++;
        else if (strchr(token, '}')) count--;
    }
    if (count > 0)
    {
        return;
    }
}

/******************************** 実装ここまで *******************************/

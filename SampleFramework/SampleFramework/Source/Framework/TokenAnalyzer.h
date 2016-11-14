#pragma once
/******************************************************************************
/*!
@file   TokenAnalyzer.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �N���X��`
******************************************************************************/


class TokenAnalyzer
{
public:
    enum { TOKEN_SIZE = 256, SKIPCHAR_SIZE = 32 };

    TokenAnalyzer(const char* string);
    ~TokenAnalyzer(){}

    void SetSkipChars(const char* skipChars);

    char* GetToken();
    float GetFloatToken();
    int   GetIntToken();
    void  SkipBracket();

    bool  CheckToken(const char* cmpStr);
    bool  IsScriptEnd(){ return str[pos] == '\0'; }
    void  Reset(){ pos = 0; }

private:
    const char*     str;
    int             pos;
    char            token[TOKEN_SIZE];
    char            skipChars[SKIPCHAR_SIZE];
};


/******************************* �w�b�_�����܂� ******************************/

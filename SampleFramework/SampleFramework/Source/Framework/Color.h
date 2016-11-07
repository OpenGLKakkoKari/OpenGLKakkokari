#pragma once
/******************************************************************************
/*!
@file   Color.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/


/*  クラス定義
******************************************************************************/


namespace Framework
{

    class Color
    {
    public:
        unsigned char b, g, r, a;

        Color() : r(255), g(255), b(255), a(255) {}
        Color(float nr, float ng, float nb, float na)
        {
            r = (unsigned char)(nr * 255.0f);
            g = (unsigned char)(ng * 255.0f);
            b = (unsigned char)(nb * 255.0f);
            a = (unsigned char)(na * 255.0f);
        }

        Color(int nr, int ng, int nb, int na)
        {
            r = nr;
            g = ng;
            b = nb;
            a = na;
        }
    };

    class ColorValue
    {
    public:
        float r, g, b, a;

        ColorValue() : r(), g(), b(), a(){}
        ColorValue(float nr, float ng, float nb, float na) : r(nr), g(ng), b(nb), a(na){}
    };
}


/******************************* ヘッダここまで ******************************/

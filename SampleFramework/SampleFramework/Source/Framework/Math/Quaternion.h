#pragma once
/******************************************************************************
/*!
@file   Quaternion.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  クラス定義
******************************************************************************/


namespace Framework
{
    class Quaternion
    {
    public:
        float x;
        float y;
        float z;
        float w;

        Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
        Quaternion(float nx, float ny, float nz, float nw)
        {
            x = nx;
            y = ny;
            z = nz;
            w = nw;
        }

        static Quaternion* Slerp(Quaternion* pOut, Quaternion* pQ1, Quaternion* pQ2, float t);
    };
}


/****************************** ヘッダここまで *******************************/

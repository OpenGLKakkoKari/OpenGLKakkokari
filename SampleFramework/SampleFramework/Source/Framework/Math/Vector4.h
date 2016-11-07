#pragma once
/******************************************************************************
/*!
@file   Vector4.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Matrix.h"


/*  構造体定義
******************************************************************************/


namespace Framework
{
    class Vector4
    {
    public:
        float x;
        float y;
        float z;
        float w;

        Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
        Vector4(float nx, float ny, float nz, float nw)
        {
            x = nx;
            y = ny;
            z = nz;
            w = nw;
        }

        /**
        * オペレーター
        */

        // 加減乗除
        Vector4 &operator += (const Vector4 &other) { return *this = *this + other; }
        Vector4 &operator -= (const Vector4 &other) { return *this = *this - other; }
        Vector4 &operator *= (float scalar) { return *this = *this * scalar; }
        Vector4 &operator /= (float scalar) { return *this = *this / scalar; }

        const Vector4 operator + (const Vector4 &other) const
        {
            return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
        }
        const Vector4 operator - (const Vector4 &other) const
        {
            return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
        }
        const Vector4 operator * (float scalar) const
        {
            return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
        }
        const Vector4 operator / (float scalar) const
        {
            return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
        }

        // 符号反転
        const Vector4 operator - () const
        {
            return Vector4(-x, -y, -z, -w);
        }

        // 条件式
        bool operator == (const Vector4 &other) const
        {
            return (x == other.x) && (y == other.y) && (z == other.z) && (w == other.w);
        }
        bool operator != (const Vector4 &other) const
        {
            return !(*this == other);
        }

        /**
        * ヘルパー関数群
        */

        static Vector4 Zero(){ return Vector4(0.0f, 0.0f, 0.0f, 0.0f); }
        static Vector4 *Transform(Vector4 *pOut, Vector4 *pV, Matrix *pM);

    };
}


/******************************* ヘッダここまで ******************************/

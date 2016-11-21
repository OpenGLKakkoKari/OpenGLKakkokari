#pragma once
/******************************************************************************
/*!
@file   Vector3.h
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
    class Matrix;
    class Vector3
    {
    public:
        float x;
        float y;
        float z;

        Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
        Vector3(float nx, float ny, float nz)
        {
            x = nx;
            y = ny;
            z = nz;
        }

        /**
         * オペレーター
         */

        // 加減乗除
        Vector3 &operator += (const Vector3 &other) { return *this = *this + other; }
        Vector3 &operator -= (const Vector3 &other) { return *this = *this - other; }
        Vector3 &operator *= (float scalar) { return *this = *this * scalar; }
        Vector3 &operator /= (float scalar) { return *this = *this / scalar; }

        const Vector3 operator + (const Vector3 &other) const
        {
            return Vector3(x + other.x, y + other.y, z + other.z);
        }
        const Vector3 operator - (const Vector3 &other) const
        {
            return Vector3(x - other.x, y - other.y, z - other.z);
        }
        const Vector3 operator * (float scalar) const
        {
            return Vector3(x * scalar, y * scalar, z * scalar);
        }
        const Vector3 operator / (float scalar) const
        {
            return Vector3(x / scalar, y / scalar, z / scalar);
        }

        // 符号反転
        const Vector3 operator - () const
        {
            return Vector3(-x, -y, -z);
        }

        // 条件式
        bool operator == (const Vector3 &other) const
        {
            return (x == other.x) && (y == other.y) && (z == other.z);
        }
        bool operator != (const Vector3 &other) const
        {
            return !(*this == other);
        }

        /**
         * ヘルパー関数群
         */

        static Vector3 Zero(){ return Vector3(0.0f, 0.0f, 0.0f); }

        static float Dot(const Vector3 *pV1, const Vector3 *pV2);
        static Vector3* Cross(Vector3 *pOut, const Vector3 *pV1, const Vector3 *pV2);
        static float Length(const Vector3 *pV);
        static float Distance(const Vector3 *pV1, const Vector3 *pV2);
        static float Radian(const Vector3 *pV1, const Vector3 *pV2);
        static Vector3* Normalize(Vector3 *pOut, const Vector3 *pV);
        static Vector3* Transform(Vector3 *pOut, Vector3 *pV, Matrix *pM);

        static Vector3* Lerp(Vector3* pOut, const Vector3 &A, const Vector3 &B,
            float min, float max, float elapsed, float(*func)(float));

        Vector3* Hermite(
            Vector3 *pOut,
            Vector3 *p0, Vector3 *v0,
            Vector3 *p1, Vector3 *v1,
            float s);

        Vector3* Bezier(
            Vector3 *pOut,
            Vector3 *p0, Vector3 *p1,
            Vector3 *p2, Vector3 *p3,
            float s);

        Vector3* BSpline(
            Vector3 *pOut,
            Vector3 *p0, Vector3 *p1,
            Vector3 *p2, Vector3 *p3,
            float s);
    };
}


/******************************* ヘッダここまで ******************************/

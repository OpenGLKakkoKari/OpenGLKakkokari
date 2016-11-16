/******************************************************************************
/*!
@file   Math.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include <math.h>


/*  クラス定義
******************************************************************************/


namespace Framework
{
    namespace Math
    {
        const float _PI = 3.14159265358979f;
        const float _2PI = _PI * 2.0f;
        const float epsilon = 0.000001f;        // 許容範囲の誤差



        // 度→ラジアン変換
        inline float ToRad(float deg)
        {
            return deg * _2PI / 360.0f;
        }

        // ラジアン→度変換
        inline float ToDeg(float rad)
        {
            return rad * 360.0f / _2PI;
        }

        // 範囲
        template <typename T>
        class Range
        {
        public:
            static bool IsInside(T value, T min, T max)
            {
                return (min <= value) && (value <= max);
            }

            static T Clamp(T value, T min, T max)
            {
                T max_ = (min < value) ? (value) : (min);
                return (max_ < max) ? (max_) : (max);
            }

            static T Wrap(T value, T min, T max)
            {
                const T n = (value - min) / (value - max);
                return (n >= 0) ? (n + min) : (n + max);
            }
        };
        
        // 角度の正規化
        inline void NormalizeRadian(float* rad)
        {
            float d;

            if (*rad > 0.0f)
                d = -_PI * 2;
            else
                d = _PI * 2;

            // ラジアンを正規化
            while (!(0.0f <= *rad && *rad < _PI * 2))
                *rad += d;
        }
        

//
// 補間時に使用する割合算出関数
//

        namespace Lerp
        {
            // 線形補間
            inline float Linear(float t)
            {
                return t;
            }

            // 2次関数補間
            inline float _2D(float t)
            {
                return t * (2.0f - t);
            }

            // 3次関数補間
            inline float Cube(float t)
            {
                return t * t * (3.0f - 2.0f * t);
            }

            // cos補間
            inline float Cos(float t)
            {
                return (1.0f - cosf(t * _PI)) / 2.0f;
            }
        }
    };
}


/******************************* ヘッダここまで ******************************/

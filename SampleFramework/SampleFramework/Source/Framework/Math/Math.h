/******************************************************************************
/*!
@file   Math.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include <math.h>


/*  �N���X��`
******************************************************************************/


namespace Framework
{
    namespace Math
    {
        const float _PI = 3.14159265358979f;
        const float _2PI = _PI * 2.0f;
        const float epsilon = 0.000001f;        // ���e�͈͂̌덷



        // �x�����W�A���ϊ�
        inline float ToRad(float deg)
        {
            return deg * _2PI / 360.0f;
        }

        // ���W�A�����x�ϊ�
        inline float ToDeg(float rad)
        {
            return rad * 360.0f / _2PI;
        }

        // �͈�
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
        
        // �p�x�̐��K��
        inline void NormalizeRadian(float* rad)
        {
            float d;

            if (*rad > 0.0f)
                d = -_PI * 2;
            else
                d = _PI * 2;

            // ���W�A���𐳋K��
            while (!(0.0f <= *rad && *rad < _PI * 2))
                *rad += d;
        }
        

//
// ��Ԏ��Ɏg�p���銄���Z�o�֐�
//

        namespace Lerp
        {
            // ���`���
            inline float Linear(float t)
            {
                return t;
            }

            // 2���֐����
            inline float _2D(float t)
            {
                return t * (2.0f - t);
            }

            // 3���֐����
            inline float Cube(float t)
            {
                return t * t * (3.0f - 2.0f * t);
            }

            // cos���
            inline float Cos(float t)
            {
                return (1.0f - cosf(t * _PI)) / 2.0f;
            }
        }
    };
}


/******************************* �w�b�_�����܂� ******************************/

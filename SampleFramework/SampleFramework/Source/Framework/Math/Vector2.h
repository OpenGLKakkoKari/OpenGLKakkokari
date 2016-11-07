#pragma once
/******************************************************************************
/*!
@file   Vector2.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


/*  �\���̒�`
******************************************************************************/


namespace Framework
{
    class Vector2
    {
    public:
        float x;
        float y;

        Vector2() {}
        Vector2(float nx, float ny)
        {
            x = nx;
            y = ny;
        }

        /**
         * �I�y���[�^�[
         */

        // �����揜
        Vector2 &operator += (const Vector2 &other) { return *this = *this + other; }
        Vector2 &operator -= (const Vector2 &other) { return *this = *this - other; }
        Vector2 &operator *= (float scalar) { return *this = *this * scalar; }
        Vector2 &operator /= (float scalar) { return *this = *this / scalar; }

        const Vector2 operator + (const Vector2 &other) const
        {
            return Vector2(x + other.x, y + other.y);
        }
        const Vector2 operator - (const Vector2 &other) const
        {
            return Vector2(x - other.x, y - other.y);
        }
        const Vector2 operator * (float scalar) const
        {
            return Vector2(x * scalar, y * scalar);
        }
        const Vector2 operator / (float scalar) const
        {
            return Vector2(x / scalar, y / scalar);
        }

        // �������]
        const Vector2 operator - () const
        {
            return Vector2(-x, -y);
        }

        // ������
        bool operator == (const Vector2 &other) const
        {
            return (x == other.x) && (y == other.y);
        }
        bool operator != (const Vector2 &other) const
        {
            return !(*this == other);
        }

        /**
         * �w���p�[�֐��Q
         */

        static Vector2 Zero(){ return Vector2(0.0f, 0.0f); }

        static float Dot(const Vector2 *pV1, const Vector2 *pV2);
        static float Cross(const Vector2 *pV1, const Vector2 *pV2);
        static float Length(const Vector2 *pV);
        static float Distance(const Vector2 *pV1, const Vector2 *pV2);
        static Vector2 *Normalize(Vector2 *pOut, const Vector2 *pV);
    };
}


/******************************* �w�b�_�����܂� ******************************/

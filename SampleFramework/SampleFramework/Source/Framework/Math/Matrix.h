#pragma once
/******************************************************************************
/*!
@file   Matrix.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Vector3.h"
#include "Quaternion.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class Vector3;
    class Matrix
    {
    public:
        float _11, _12, _13, _14;
        float _21, _22, _23, _24;
        float _31, _32, _33, _34;
        float _41, _42, _43, _44;

        Matrix();
        Matrix(float _11, float _12, float _13, float _14,
            float _21, float _22, float _23, float _24,
            float _31, float _32, float _33, float _34,
            float _41, float _42, float _43, float _44);
        ~Matrix(){}

        const Matrix operator + (const Matrix &other) const
        {
            Matrix mat;

            mat._11 = this->_11 + other._11;
            mat._12 = this->_12 + other._12;
            mat._13 = this->_13 + other._13;
            mat._14 = this->_14 + other._14;

            mat._21 = this->_21 + other._21;
            mat._22 = this->_22 + other._22;
            mat._23 = this->_23 + other._23;
            mat._24 = this->_24 + other._24;

            mat._31 = this->_31 + other._31;
            mat._32 = this->_32 + other._32;
            mat._33 = this->_33 + other._33;
            mat._34 = this->_34 + other._34;

            mat._41 = this->_41 + other._41;
            mat._42 = this->_42 + other._42;
            mat._43 = this->_43 + other._43;
            mat._44 = this->_44 + other._44;

            return mat;
        }

        const Matrix operator * (const float &other) const
        {
            Matrix mat;

            mat._11 = this->_11 * other;
            mat._12 = this->_12 * other;
            mat._13 = this->_13 * other;
            mat._14 = this->_14 * other;

            mat._21 = this->_21 * other;
            mat._22 = this->_22 * other;
            mat._23 = this->_23 * other;
            mat._24 = this->_24 * other;

            mat._31 = this->_31 * other;
            mat._32 = this->_32 * other;
            mat._33 = this->_33 * other;
            mat._34 = this->_34 * other;

            mat._41 = this->_41 * other;
            mat._42 = this->_42 * other;
            mat._43 = this->_43 * other;
            mat._44 = this->_44 * other;

            return mat;
        }


        static Matrix* Zero(Matrix *pOut);
        static Matrix* Identity(Matrix *pOut);
        static Matrix* Multiply(Matrix *pOut, Matrix *pM1, Matrix *pM2);

        static Matrix* Scale(Matrix *pOut, float x, float y, float z);

        static Matrix* RotationXYZ(Matrix *pOut, float x, float y, float z);
        static Matrix* RotationYXZ(Matrix *pOut, float x, float y, float z);
        static Matrix* RotationX(Matrix *pOut, float x);
        static Matrix* RotationY(Matrix *pOut, float y);
        static Matrix* RotationZ(Matrix *pOut, float z);
        static Matrix* RotationQuaternion(Matrix *pOut, Quaternion* pQ);

        static Matrix* Translation(Matrix *pOut, float x, float y, float z);

        static Matrix* GetCalcMatrix(Matrix *pOut, Vector3 *pScale, Vector3 *pRot, Vector3 *pTrans);
        static Matrix* GetCalcMatrix(Matrix *pOut, Vector3 *pScale, Quaternion *pRot, Vector3 *pTrans);

        static Matrix* Transpose(Matrix *pOut, Matrix *pM);
        static Matrix* Inverse(Matrix *pOut, Matrix *pM);

        static Matrix* SetPerspectiveLH(Matrix *pOut, float Width, float Height, float nearZ, float farZ);
        static Matrix* SetPerspectiveRH(Matrix *pOut, float Width, float Height, float nearZ, float farZ);
        static Matrix* SetPerspectiveFovLH(Matrix *pOut, float Fov, float Width, float Height, float nearZ, float farZ);
        static Matrix* SetPerspectiveFovRH(Matrix *pOut, float Fov, float Width, float Height, float nearZ, float farZ);
        static Matrix* SetOrthoOffCenterLH(Matrix *pOut, float l, float r, float b, float t, float zn, float zf);
        static Matrix* SetOrthoLH(Matrix *pOut, float w, float h, float zn, float zf);

        static Matrix* SetLookAtLH(Matrix *pOut, Vector3 *pEye, Vector3 *pAt, Vector3 *pUp);
        static Matrix* SetLookAtRH(Matrix *pOut, Vector3 *pEye, Vector3 *pAt, Vector3 *pUp);
    };
}


/******************************* ヘッダここまで ******************************/

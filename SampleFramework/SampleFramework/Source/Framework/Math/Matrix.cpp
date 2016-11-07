/*****************************************************************************/
/*!
@file   Matrix.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Matrix.h"
#include <math.h>


using Framework::Matrix;
using Framework::Vector3;
using Framework::Quaternion;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

Matrix::Matrix()
{
    Identity(this);
}

Matrix::Matrix(float _11, float _12, float _13, float _14,
               float _21, float _22, float _23, float _24,
               float _31, float _32, float _33, float _34,
               float _41, float _42, float _43, float _44)
{

    this->_11 = _11, this->_21 = _21, this->_31 = _31, this->_41 = _41;
    this->_12 = _12, this->_22 = _22, this->_32 = _32, this->_42 = _42;
    this->_13 = _13, this->_23 = _23, this->_33 = _33, this->_43 = _43;
    this->_14 = _14, this->_24 = _24, this->_34 = _34, this->_44 = _44;

}

/******************************************************************************
@brief  ��s��쐬
@param  pOut        ������(�P�ʍs��)����x�N�g��
@return Matrix      �P�ʍs��
******************************************************************************/

Matrix *Matrix::Zero(Matrix *pOut)
{

    pOut->_11 = 0.0f, pOut->_12 = 0.0f, pOut->_13 = 0.0f, pOut->_14 = 0.0f;
    pOut->_21 = 0.0f, pOut->_22 = 0.0f, pOut->_23 = 0.0f, pOut->_24 = 0.0f;
    pOut->_31 = 0.0f, pOut->_32 = 0.0f, pOut->_33 = 0.0f, pOut->_34 = 0.0f;
    pOut->_41 = 0.0f, pOut->_42 = 0.0f, pOut->_43 = 0.0f, pOut->_44 = 0.0f;

    return pOut;
}

/******************************************************************************
@brief  �P�ʍs��쐬
@param  pOut        ������(�P�ʍs��)����x�N�g��
@return Matrix      �P�ʍs��
******************************************************************************/

Matrix *Matrix::Identity(Matrix *pOut)
{

    pOut->_11 = 1.0f, pOut->_12 = 0.0f, pOut->_13 = 0.0f, pOut->_14 = 0.0f;
    pOut->_21 = 0.0f, pOut->_22 = 1.0f, pOut->_23 = 0.0f, pOut->_24 = 0.0f;
    pOut->_31 = 0.0f, pOut->_32 = 0.0f, pOut->_33 = 1.0f, pOut->_34 = 0.0f;
    pOut->_41 = 0.0f, pOut->_42 = 0.0f, pOut->_43 = 0.0f, pOut->_44 = 1.0f;

    return pOut;
}

/******************************************************************************
@brief  �s���Z
@param  pOut        ��Z����x�N�g��
@param  Matrix1     �s��1
@param  Matrix2     �s��2
@return Matrix      ��Z���ꂽ�x�N�g��
******************************************************************************/

Matrix *Matrix::Multiply(Matrix *pOut, Matrix *Matrix1, Matrix *Matrix2)
{
    Matrix mat1 = *Matrix1;
    Matrix mat2 = *Matrix2;

    pOut->_11 = mat1._11 * mat2._11
        + mat1._12 * mat2._21
        + mat1._13 * mat2._31
        + mat1._14 * mat2._41;

    pOut->_12 = mat1._11 * mat2._12
        + mat1._12 * mat2._22
        + mat1._13 * mat2._32
        + mat1._14 * mat2._42;

    pOut->_13 = mat1._11 * mat2._13
        + mat1._12 * mat2._23
        + mat1._13 * mat2._33
        + mat1._14 * mat2._43;

    pOut->_14 = mat1._11 * mat2._14
        + mat1._12 * mat2._24
        + mat1._13 * mat2._34
        + mat1._14 * mat2._44;


    pOut->_21 = mat1._21 * mat2._11
        + mat1._22 * mat2._21
        + mat1._23 * mat2._31
        + mat1._24 * mat2._41;

    pOut->_22 = mat1._21 * mat2._12
        + mat1._22 * mat2._22
        + mat1._23 * mat2._32
        + mat1._24 * mat2._42;

    pOut->_23 = mat1._21 * mat2._13
        + mat1._22 * mat2._23
        + mat1._23 * mat2._33
        + mat1._24 * mat2._43;

    pOut->_24 = mat1._21 * mat2._14
        + mat1._22 * mat2._24
        + mat1._23 * mat2._34
        + mat1._24 * mat2._44;

    pOut->_31 = mat1._31 * mat2._11
        + mat1._32 * mat2._21
        + mat1._33 * mat2._31
        + mat1._34 * mat2._41;

    pOut->_32 = mat1._31 * mat2._12
        + mat1._32 * mat2._22
        + mat1._33 * mat2._32
        + mat1._34 * mat2._42;

    pOut->_33 = mat1._31 * mat2._13
        + mat1._32 * mat2._23
        + mat1._33 * mat2._33
        + mat1._34 * mat2._43;

    pOut->_34 = mat1._31 * mat2._14
        + mat1._32 * mat2._24
        + mat1._33 * mat2._34
        + mat1._34 * mat2._44;

    pOut->_41 = mat1._41 * mat2._11
        + mat1._42 * mat2._21
        + mat1._43 * mat2._31
        + mat1._44 * mat2._41;

    pOut->_42 = mat1._41 * mat2._12
        + mat1._42 * mat2._22
        + mat1._43 * mat2._32
        + mat1._44 * mat2._42;

    pOut->_43 = mat1._41 * mat2._13
        + mat1._42 * mat2._23
        + mat1._43 * mat2._33
        + mat1._44 * mat2._43;

    pOut->_44 = mat1._41 * mat2._14
        + mat1._42 * mat2._24
        + mat1._43 * mat2._34
        + mat1._44 * mat2._44;

    return pOut;
}

/******************************************************************************
@brief  X����]�s��쐬
@param  pOut        �o�͍s��
@param  x           X���̉�]��
@return Matrix      ��]�s��
******************************************************************************/

Matrix *Matrix::RotationX(Matrix *pOut, float x)
{
    float sinX = sinf(x);
    float cosX = cosf(x);

    pOut->_22 = cosX;
    pOut->_23 = sinX;
    pOut->_32 = -sinX;
    pOut->_33 = cosX;

    return pOut;
}

/******************************************************************************
@brief  Y����]�s��쐬
@param  pOut        �o�͍s��
@param  y           Y���̉�]��
@return Matrix      ��]�s��
******************************************************************************/

Matrix *Matrix::RotationY(Matrix *pOut, float y)
{
    float sinY = sinf(y);
    float cosY = cosf(y);

    pOut->_11 = cosY;
    pOut->_13 = -sinY;
    pOut->_31 = sinY;
    pOut->_33 = cosY;

    return pOut;
}

/******************************************************************************
@brief  Z����]�s��쐬
@param  pOut        �o�͍s��
@param  z           Z���̉�]��
@return Matrix      ��]�s��
******************************************************************************/

Matrix *Matrix::RotationZ(Matrix *pOut, float z)
{
    float sinZ = sinf(z);
    float cosZ = cosf(z);

    pOut->_11 = cosZ;
    pOut->_12 = sinZ;
    pOut->_21 = -sinZ;
    pOut->_22 = cosZ;

    return pOut;
}

/******************************************************************************
@brief  3��( X��Y��Z�� )��]�s��쐬
@param  pOut        �o�͍s��
@param  x           X���̉�]��
@param  y           Y���̉�]��
@param  z           Z���̉�]��
@return Matrix      ��]�s��
******************************************************************************/

Matrix *Matrix::RotationXYZ(Matrix *pOut, float x, float y, float z)
{

    Matrix matX, matY, matZ;

    RotationX(&matX, x);
    RotationY(&matY, y);
    RotationZ(&matZ, z);

    Multiply(&matX, &matX, &matY);
    Multiply(&matZ, &matX, &matZ);
    
    *pOut = matZ;
    return pOut;
}

/******************************************************************************
@brief  3��( X��Y��Z�� )��]�s��쐬
@param  pOut        �o�͍s��
@param  x           X���̉�]��
@param  y           Y���̉�]��
@param  z           Z���̉�]��
@return Matrix      ��]�s��
******************************************************************************/

Matrix *Matrix::RotationYXZ(Matrix *pOut, float x, float y, float z)
{

    Matrix matX, matY, matZ;

    RotationX(&matX, x);
    RotationY(&matY, y);
    RotationZ(&matZ, z);

    Multiply(&matZ, &matZ, &matX);
    Multiply(&matZ, &matZ, &matY);

    *pOut = matZ;
    return pOut;
}

/******************************************************************************
@brief  �N�H�[�^�j�I����]�s��쐬
@param  pOut        �o�͍s��
@param  pQ          �N�H�[�^�j�I��
@return Matrix      ��]�s��
******************************************************************************/

Matrix *Matrix::RotationQuaternion(Matrix *pOut, Quaternion *pQ)
{
    Matrix rot;

    rot._11 = 1 - 2 * ((pQ->y*pQ->y) + (pQ->z*pQ->z));
    rot._12 = 2 * (pQ->x*pQ->y + pQ->w*pQ->z);
    rot._13 = 2 * (pQ->x*pQ->z - pQ->w*pQ->y);
    rot._14 = 0.0f;

    rot._21 = 2 * (pQ->x*pQ->y - pQ->w*pQ->z);
    rot._22 = 1 - 2 * ((pQ->x*pQ->x) + (pQ->z*pQ->z));
    rot._23 = 2 * (pQ->y*pQ->z + pQ->w*pQ->x);
    rot._24 = 0.0f;

    rot._31 = 2 * (pQ->x*pQ->z + pQ->w*pQ->y);
    rot._32 = 2 * (pQ->y*pQ->z - pQ->w*pQ->x);
    rot._33 = 1 - 2 * ((pQ->x*pQ->x) + (pQ->y*pQ->y));
    rot._34 = 0.0f;

    rot._41 = 0.0f;
    rot._42 = 0.0f;
    rot._43 = 0.0f;
    rot._44 = 1.0f;

    *pOut = rot;
    return pOut;
}

/******************************************************************************
@brief  3��( X��Y��Z�� )�X�P�[���s��쐬
@param  pOut        �o�͍s��
@param  x           X���̃X�P�[��
@param  y           Y���̃X�P�[��
@param  z           Z���̃X�P�[��
@return Matrix      �X�P�[���s��
******************************************************************************/

Matrix *Matrix::Scale(Matrix *pOut, float x, float y, float z)
{

    pOut->_11 = x;
    pOut->_22 = y;
    pOut->_33 = z;

    return pOut;
}

/******************************************************************************
@brief  3��( X��Y��Z�� )�ړ��s��쐬
@param  pOut        �o�͍s��
@param  x           X���̈ړ���
@param  y           Y���̈ړ���
@param  z           Z���̈ړ���
@return Matrix      �ړ��s��
******************************************************************************/

Matrix *Matrix::Translation(Matrix *pOut, float x, float y, float z)
{

    pOut->_41 = x;
    pOut->_42 = y;
    pOut->_43 = z;

    return pOut;
}

/******************************************************************************
@brief  �g�k��]�ړ��v�Z�ςݍs��쐬
@param  pOut        �o�͍s��
@param  pScale      �g�k��
@param  pRot        ��]��
@param  pTrans      �ړ���
@return Matrix      �v�Z�ςݍs��
******************************************************************************/

Matrix *Matrix::GetCalcMatrix(Matrix *pOut, Vector3 *pScale, Vector3 *pRot, Vector3 *pTrans)
{
    Matrix transMat, rotMat, scaMat;

    Matrix::Scale(&scaMat, pScale->x, pScale->y, pScale->z);
    Matrix::RotationYXZ(&rotMat, pRot->x, pRot->y, pRot->z);
    Matrix::Translation(&transMat, pTrans->x, pTrans->y, pTrans->z);

    Matrix::Multiply(pOut, pOut, &scaMat);
    Matrix::Multiply(pOut, pOut, &rotMat);
    Matrix::Multiply(pOut, pOut, &transMat);

    return pOut;
}

Matrix *Matrix::GetCalcMatrix(Matrix *pOut, Vector3 *pScale, Quaternion *pRot, Vector3 *pTrans)
{

    Matrix result;
    Matrix transMat, rotMat, scaMat;

    Matrix::Identity(&result);
    Matrix::Scale(&scaMat, pScale->x, pScale->y, pScale->z);
    Matrix::RotationQuaternion(&rotMat, pRot);
    Matrix::Translation(&transMat, pTrans->x, pTrans->y, pTrans->z);

    Matrix::Multiply(&result, &result, &scaMat);
    Matrix::Multiply(&result, &result, &rotMat);
    Matrix::Multiply(&result, &result, &transMat);
    *pOut = result;

    return pOut;
}

/******************************************************************************
@brief  �]�u�s��쐬
@param  pOut        �]�u�s��
@param  pM          ���͍s��
@return Matrix      �]�u�s��
******************************************************************************/

Matrix *Matrix::Transpose(Matrix *pOut, Matrix *pM)
{

    pOut->_12 = pM->_21;
    pOut->_13 = pM->_31;
    pOut->_14 = pM->_41;

    pOut->_21 = pM->_12;
    pOut->_23 = pM->_32;
    pOut->_24 = pM->_42;

    pOut->_31 = pM->_13;
    pOut->_32 = pM->_23;
    pOut->_34 = pM->_43;

    pOut->_41 = pM->_14;
    pOut->_42 = pM->_24;
    pOut->_43 = pM->_34;

    return pOut;
}

/******************************************************************************
@brief  �t�s��쐬
@param  pOut        �t�s��
@param  pM          ���͍s��
@return Matrix      �t�s��
******************************************************************************/

Matrix *Matrix::Inverse(Matrix *pOut, Matrix *pM)
{

    Matrix mat = *pM;

    pOut->_11 = mat._22 * mat._33 * mat._44
              + mat._23 * mat._34 * mat._42
              + mat._24 * mat._32 * mat._43
              - mat._22 * mat._34 * mat._43
              - mat._23 * mat._32 * mat._44
              - mat._24 * mat._33 * mat._42;

    pOut->_12 = mat._12 * mat._34 * mat._43
              + mat._13 * mat._32 * mat._44
              + mat._14 * mat._33 * mat._42
              - mat._12 * mat._33 * mat._44
              - mat._13 * mat._34 * mat._42
              - mat._14 * mat._32 * mat._43;

    pOut->_13 = mat._12 * mat._23 * mat._44
              + mat._13 * mat._24 * mat._42
              + mat._14 * mat._22 * mat._43
              - mat._12 * mat._24 * mat._43
              - mat._13 * mat._22 * mat._44
              - mat._14 * mat._23 * mat._42;

    pOut->_14 = mat._12 * mat._24 * mat._33
              + mat._13 * mat._22 * mat._34
              + mat._14 * mat._23 * mat._32
              - mat._12 * mat._23 * mat._34
              - mat._13 * mat._24 * mat._32
              - mat._14 * mat._22 * mat._33;


    pOut->_21 = mat._21 * mat._34 * mat._43
              + mat._23 * mat._31 * mat._44
              + mat._24 * mat._33 * mat._41
              - mat._21 * mat._33 * mat._44
              - mat._23 * mat._34 * mat._41
              - mat._24 * mat._31 * mat._43;

    pOut->_22 = mat._11 * mat._33 * mat._44
              + mat._13 * mat._34 * mat._41
              + mat._14 * mat._31 * mat._43
              - mat._11 * mat._34 * mat._43
              - mat._13 * mat._31 * mat._44
              - mat._14 * mat._33 * mat._41;

    pOut->_23 = mat._11 * mat._24 * mat._43
              + mat._13 * mat._21 * mat._44
              + mat._14 * mat._23 * mat._41
              - mat._11 * mat._23 * mat._44
              - mat._13 * mat._24 * mat._41
              - mat._14 * mat._21 * mat._43;

    pOut->_24 = mat._11 * mat._23 * mat._34
              + mat._13 * mat._24 * mat._31
              + mat._14 * mat._21 * mat._33
              - mat._11 * mat._24 * mat._33
              - mat._13 * mat._21 * mat._34
              - mat._14 * mat._23 * mat._31;


    pOut->_31 = mat._21 * mat._32 * mat._44
              + mat._22 * mat._34 * mat._41
              + mat._24 * mat._31 * mat._42
              - mat._21 * mat._34 * mat._42
              - mat._22 * mat._31 * mat._44
              - mat._24 * mat._32 * mat._41;

    pOut->_32 = mat._11 * mat._34 * mat._42
              + mat._12 * mat._31 * mat._44
              + mat._14 * mat._32 * mat._41
              - mat._11 * mat._32 * mat._44
              - mat._12 * mat._34 * mat._41
              - mat._14 * mat._31 * mat._42;

    pOut->_33 = mat._11 * mat._22 * mat._44
              + mat._12 * mat._24 * mat._41
              + mat._14 * mat._21 * mat._42
              - mat._11 * mat._24 * mat._42
              - mat._12 * mat._21 * mat._44
              - mat._14 * mat._22 * mat._41;

    pOut->_34 = mat._11 * mat._24 * mat._32
              + mat._12 * mat._21 * mat._34
              + mat._14 * mat._22 * mat._31
              - mat._11 * mat._22 * mat._34
              - mat._12 * mat._24 * mat._31
              - mat._14 * mat._21 * mat._32;


    pOut->_41 = mat._21 * mat._33 * mat._42
              + mat._22 * mat._31 * mat._43
              + mat._23 * mat._32 * mat._41
              - mat._21 * mat._32 * mat._43
              - mat._22 * mat._33 * mat._41
              - mat._23 * mat._31 * mat._42;

    pOut->_42 = mat._11 * mat._32 * mat._43
              + mat._12 * mat._33 * mat._41
              + mat._13 * mat._31 * mat._42
              - mat._11 * mat._33 * mat._42
              - mat._12 * mat._31 * mat._43
              - mat._13 * mat._32 * mat._41;

    pOut->_43 = mat._11 * mat._23 * mat._42
              + mat._12 * mat._21 * mat._43
              + mat._13 * mat._22 * mat._41
              - mat._11 * mat._22 * mat._43
              - mat._12 * mat._23 * mat._41
              - mat._13 * mat._21 * mat._42;

    pOut->_44 = mat._11 * mat._22 * mat._33
              + mat._12 * mat._23 * mat._31 
              + mat._13 * mat._21 * mat._32
              - mat._11 * mat._23 * mat._32
              - mat._12 * mat._21 * mat._33
              - mat._13 * mat._22 * mat._31;

    return pOut;
}

/******************************************************************************
@brief  ����n�ˉe�s�񐶐�
@param  pOut        �������ꂽ�ˉe�s��
@param  pEye        ����p
@param  pAt         �A�X�y�N�g��
@param  pUp         �߂�Z�l
@return Matrix      �������ꂽ�s��
******************************************************************************/

Matrix *Matrix::SetLookAtLH(Matrix *pOut, Vector3 *pEye, Vector3 *pAt, Vector3 *pUp)
{
    Vector3 Xaxis, Yaxis, Zaxis;
    Vector3 tmp = *pAt - *pEye;

    Vector3::Normalize(&Zaxis, &tmp);
    Vector3::Normalize(&Xaxis, Vector3::Cross(&Xaxis, pUp, &Zaxis));
    Vector3::Cross    (&Yaxis, &Zaxis, &Xaxis);

    pOut->_11 = Xaxis.x;
    pOut->_12 = Yaxis.x;
    pOut->_13 = Zaxis.x;
    pOut->_14 = 0.0f;

    pOut->_21 = Xaxis.y;
    pOut->_22 = Yaxis.y;
    pOut->_23 = Zaxis.y;
    pOut->_24 = 0.0f;

    pOut->_31 = Xaxis.z;
    pOut->_32 = Yaxis.z;
    pOut->_33 = Zaxis.z;
    pOut->_34 = 0.0f;

    pOut->_41 = -Vector3::Dot(&Xaxis, pEye);
    pOut->_42 = -Vector3::Dot(&Yaxis, pEye);
    pOut->_43 = -Vector3::Dot(&Zaxis, pEye);
    pOut->_44 = 1.0f;

    return pOut;
}

/******************************************************************************
@brief  �E��n�ˉe�s�񐶐�
@param  pOut        �������ꂽ�ˉe�s��
@param  pEye        ����p
@param  pAt         �A�X�y�N�g��
@param  pUp         �߂�Z�l
@return Matrix      �������ꂽ�s��
******************************************************************************/

Matrix *Matrix::SetLookAtRH(Matrix *pOut, Vector3 *pEye, Vector3 *pAt, Vector3 *pUp)
{
    Vector3 Xaxis, Yaxis, Zaxis;
    Vector3 tmp = *pEye - *pAt;

    Vector3::Normalize(&Zaxis, &tmp);
    Vector3::Normalize(&Xaxis, Vector3::Cross(&Xaxis, pUp, &Zaxis));
    Vector3::Cross(&Yaxis, &Zaxis, &Xaxis);

    pOut->_11 = Xaxis.x;
    pOut->_12 = Yaxis.x;
    pOut->_13 = Zaxis.x;
    pOut->_14 = 0.0f;

    pOut->_21 = Xaxis.y;
    pOut->_22 = Yaxis.y;
    pOut->_23 = Zaxis.y;
    pOut->_24 = 0.0f;

    pOut->_31 = Xaxis.z;
    pOut->_32 = Yaxis.z;
    pOut->_33 = Zaxis.z;
    pOut->_34 = 0.0f;

    pOut->_41 = Vector3::Dot(&Xaxis, pEye);
    pOut->_42 = Vector3::Dot(&Yaxis, pEye);
    pOut->_43 = Vector3::Dot(&Zaxis, pEye);
    pOut->_44 = 1.0f;

    return pOut;
}

/******************************************************************************
@brief  ����n�ˉe�s�񐶐�
@param  pOut        �������ꂽ�ˉe�s��
@param  Width       ����
@param  Height      �c��
@param  nearZ       �߂�Z�l
@param  farZ        ����Z�l
@return Matrix      �������ꂽ�ˉe�s��
******************************************************************************/

Matrix *Matrix::SetPerspectiveLH(Matrix *pOut, float Width, float Height, float nearZ, float farZ)
{
    pOut->_11 = 2 * nearZ / Width;
    pOut->_12 = 0.0f;
    pOut->_13 = 0.0f;
    pOut->_14 = 0.0f;

    pOut->_21 = 0.0f;
    pOut->_22 = 2 * nearZ / Height;
    pOut->_23 = 0.0f;
    pOut->_24 = 0.0f;

    pOut->_31 = 0.0f;
    pOut->_32 = 0.0f;
    pOut->_33 = farZ / (farZ - nearZ);
    pOut->_34 = 1.0f;

    pOut->_41 = 0.0f;
    pOut->_42 = 0.0f;
    pOut->_43 = nearZ * farZ / (nearZ - farZ);
    pOut->_44 = 0.0f;

    return pOut;
}

/******************************************************************************
@brief  �E��n�ˉe�s�񐶐�
@param  pOut        �������ꂽ�ˉe�s��
@param  Width       ����
@param  Height      �c��
@param  nearZ       �߂�Z�l
@param  farZ        ����Z�l
@return Matrix      �������ꂽ�ˉe�s��
******************************************************************************/

Matrix *Matrix::SetPerspectiveRH(Matrix *pOut, float Width, float Height, float nearZ, float farZ)
{
    pOut->_11 = 2 * nearZ / Width;
    pOut->_12 = 0.0f;
    pOut->_13 = 0.0f;
    pOut->_14 = 0.0f;

    pOut->_21 = 0.0f;
    pOut->_22 = 2 * nearZ / Height;
    pOut->_23 = 0.0f;
    pOut->_24 = 0.0f;

    pOut->_31 = 0.0f;
    pOut->_32 = 0.0f;
    pOut->_33 = farZ / (nearZ - farZ);
    pOut->_34 = -1.0f;

    pOut->_41 = 0.0f;
    pOut->_42 = 0.0f;
    pOut->_43 = nearZ * farZ / (nearZ - farZ);
    pOut->_44 = 0.0f;

    return pOut;
}

/******************************************************************************
@brief  ����n�ˉe�s�񐶐�
@param  pOut        �������ꂽ�ˉe�s��
@param  Fov         ����p
@param  Width       ����
@param  Height      �c��
@param  nearZ       �߂�Z�l
@param  farZ        ����Z�l
@return Matrix      �������ꂽ�ˉe�s��
******************************************************************************/

Matrix *Matrix::SetPerspectiveFovLH(Matrix *pOut, float Fov, float Width, float Height, float nearZ, float farZ)
{
    float cot = 1.0f / tanf(Fov/2);
    float yScale = cot;
    float xScale = yScale / (Width / Height);
    
    pOut->_11 = xScale;
    pOut->_12 = 0.0f;
    pOut->_13 = 0.0f;
    pOut->_14 = 0.0f;

    pOut->_21 = 0.0f;
    pOut->_22 = yScale;
    pOut->_23 = 0.0f;
    pOut->_24 = 0.0f;

    pOut->_31 = 0.0f;
    pOut->_32 = 0.0f;
    pOut->_33 = farZ / (farZ - nearZ);
    pOut->_34 = 1.0f;

    pOut->_41 = 0.0f;
    pOut->_42 = 0.0f;
    pOut->_43 = -nearZ * farZ / (farZ - nearZ);
    pOut->_44 = 0.0f;

    return pOut;
}

/******************************************************************************
@brief  �E��n�ˉe�s�񐶐�
@param  pOut        �������ꂽ�ˉe�s��
@param  Fov         ����p
@param  Width       ����
@param  Height      �c��
@param  nearZ       �߂�Z�l
@param  farZ        ����Z�l
@return Matrix      �������ꂽ�ˉe�s��
******************************************************************************/

Matrix *Matrix::SetPerspectiveFovRH(Matrix *pOut, float Fov, float Width, float Height, float nearZ, float farZ)
{
    float cot = 1.0f / tanf(Fov / 2);
    float yScale = cot;
    float xScale = yScale / (Width / Height);

    pOut->_11 = xScale;
    pOut->_12 = 0.0f;
    pOut->_13 = 0.0f;
    pOut->_14 = 0.0f;

    pOut->_21 = 0.0f;
    pOut->_22 = yScale;
    pOut->_23 = 0.0f;
    pOut->_24 = 0.0f;

    pOut->_31 = 0.0f;
    pOut->_32 = 0.0f;
    pOut->_33 = farZ / (nearZ - farZ);
    pOut->_34 = -1.0f;
    
    pOut->_41 = 0.0f;
    pOut->_42 = 0.0f;
    pOut->_43 = farZ * nearZ / (nearZ - farZ);
    pOut->_44 = 0.0f;

    return pOut;
}

/******************************************************************************
@brief  ����n���ˉe�s�񐶐�
@param  pOut        �������ꂽ���ˉe�s��
@param  l           �r���[ �{�����[���̍ŏ� x �l
@param  r           �r���[ �{�����[���̍ő� x �l
@param  b           �r���[ �{�����[���̍ŏ� y �l
@param  t           �r���[ �{�����[���̍ő� y �l
@param  zn          �r���[ �{�����[���̍ŏ� z �l
@return zf          �r���[ �{�����[���̍ő� z �l
******************************************************************************/

Matrix *Matrix::SetOrthoOffCenterLH(Matrix *pOut, float l, float r, float b, float t, float zn, float zf)
{

    pOut->_11 = 2 / (r - 1);
    pOut->_12 = 0.0f;
    pOut->_13 = 0.0f;
    pOut->_14 = 0.0f;

    pOut->_21 = 0.0f;
    pOut->_22 = 2 / (t - b);
    pOut->_23 = 0.0f;
    pOut->_24 = 0.0f;

    pOut->_31 = 0.0f;
    pOut->_32 = 0.0f;
    pOut->_33 = 1 / (zf - zn);
    pOut->_34 = 0.0f;

    pOut->_41 = (1 + r)/(1 - r);
    pOut->_42 = (t + b)/(b - t);
    pOut->_43 = zn / (zn - zf);
    pOut->_44 = 1.0f;

    return pOut;
}

/******************************************************************************
@brief  ����n���ˉe�s�񐶐�
@param  pOut        �������ꂽ���ˉe�s��
@param  w           �r���[ �{�����[���̕�
@param  h           �r���[ �{�����[���̍���
@param  zn          �r���[ �{�����[���̍ŏ� z �l
@return zf          �r���[ �{�����[���̍ő� z �l
******************************************************************************/

Matrix *Matrix::SetOrthoLH(Matrix *pOut, float w, float h, float zn, float zf)
{
    pOut->_11 = 2 / w;
    pOut->_12 = 0.0f;
    pOut->_13 = 0.0f;
    pOut->_14 = 0.0f;

    pOut->_21 = 0.0f;
    pOut->_22 = 2 / h;
    pOut->_23 = 0.0f;
    pOut->_24 = 0.0f;

    pOut->_31 = 0.0f;
    pOut->_32 = 0.0f;
    pOut->_33 = 1 / (zf - zn);
    pOut->_34 = 0.0f;

    pOut->_41 = 0.0f;
    pOut->_42 = 0.0f;
    pOut->_43 = zn / (zn - zf);
    pOut->_44 = 1.0f;

    return pOut;
}

/******************************** ���������܂� *******************************/

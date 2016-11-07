/*****************************************************************************/
/*!
@file   Vector3.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/


/*  �C���N���[�h
******************************************************************************/


#include "Vector3.h"
#include <math.h>
#include "..\Math\Math.h"


using Framework::Vector3;
using Framework::Matrix;
using namespace Framework::Math;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  ���ώZ�o
@param  pV1         ���̓x�N�g��1
@param  pV2         ���̓x�N�g��2
@return float       ����
******************************************************************************/

float Vector3::Dot(const Vector3 *pV1, const Vector3 *pV2)
{
    return pV1->x * pV2->x +
           pV1->y * pV2->y +
           pV1->z * pV2->z;

}

/******************************************************************************
@brief  �O�ώZ�o
@param  pOut        �o�͐�
@param  pV1         ���̓x�N�g��1
@param  pV2         ���̓x�N�g��2
@return Vector3     �O��
******************************************************************************/

Vector3* Vector3::Cross(Vector3 *pOut, const Vector3 *pV1, const Vector3 *pV2)
{

    pOut->x = pV1->y * pV2->z - pV1->z * pV2->y;
    pOut->y = pV1->z * pV2->x - pV1->x * pV2->z;
    pOut->z = pV1->x * pV2->y - pV1->y * pV2->x;

    return pOut;
}

/******************************************************************************
@brief  �x�N�g���̒����Z�o
@param  pV          ���̓x�N�g��
@return float       �x�N�g���̒���
******************************************************************************/

float Vector3::Length(const Vector3 *pV)
{

    return sqrtf( pV->x * pV->x +
                  pV->y * pV->y +
                  pV->z * pV->z);

}

/******************************************************************************
@brief  �����Z�o
@param  pV1         ���̓x�N�g��1
@param  pV2         ���̓x�N�g��2
@return float       ����
******************************************************************************/

float Vector3::Distance(const Vector3 *pV1, const Vector3 *pV2)
{
    return Vector3::Length(pV1) - Vector3::Length(pV2);
}

/******************************************************************************
@brief  2�̃x�N�g�����Ȃ��p���Z�o
@param  pV1         ���̓x�N�g��1
@param  pV2         ���̓x�N�g��2
@return float       ���W�A��
******************************************************************************/

float Vector3::Radian(const Vector3 *pV1, const Vector3 *pV2)
{
    float lengthA = Vector3::Length(pV1);
    float lengthB = Vector3::Length(pV2);

    float cos = Vector3::Dot(pV1, pV2) / (lengthA * lengthB);

    return acosf(cos);
}

/******************************************************************************
@brief  �x�N�g���̐��K��( ��x�N�g���̏ꍇ�A��x�N�g����Ԃ� )
@param  pOut        �o�̓x�N�g��
@param  pV          ���̓x�N�g��
******************************************************************************/

Vector3* Vector3::Normalize(Vector3 *pOut, const Vector3 *pV)
{
    (Length(pV) == 0.0f) ?
        (*pOut = Vector3::Zero()) :
        (*pOut = *pV / Length(pV));
    
    return pOut;
}

/******************************************************************************
@brief  3�����x�N�g�����s��ϊ�
@param  pOut        �o�̓x�N�g��
@param  pV          ���̓x�N�g��
@param  pM          ���͍s��
@return Vector3*    �o�̓x�N�g��
******************************************************************************/

Vector3* Vector3::Transform(Vector3 *pOut, Vector3 *pV, Matrix *pM)
{

    pOut->x = pV->x    * pM->_11
            + pV->y    * pM->_21
            + pV->z    * pM->_31
            + pM->_41;

    pOut->y = pV->x    * pM->_12
            + pV->y    * pM->_22
            + pV->z    * pM->_32
            + pM->_42;

    pOut->z = pV->x    * pM->_13
            + pV->y    * pM->_23
            + pV->z    * pM->_33
            + pM->_43;

    return pOut;
}

/******************************************************************************
@brief  ���
@param  A           �n�_
@param  B           �I�_
@param  min         �ŏ�����
@param  max         �ő厞��
@param  elapsed     �o�ߎ���
@param  func        ��Ԋ֐��|�C���^
@return Vector3     ���W
******************************************************************************/

Vector3* Vector3::Lerp(
    Vector3* pOut,
    const Vector3 &A,
    const Vector3 &B,
    float min,
    float max,
    float elapsed,
    float(*func)(float))
{

    float t = (elapsed - min) / (max - min);    // ���Ԃ�}��ϐ���
    bool isOut = false;
    if (t < 0.0f)
    {
        t = 0.0f; isOut = true;
    }
    else if (t > 1.0f)
    {
        t = 1.0f; isOut = true;
    }

    float rate = (*func)(t);                    // �����̕�Ԓl�ɕϊ�
    *pOut = A * (1.0f - rate) + B * rate;

    return pOut;
}

/******************************************************************************
@brief  �G���~�[�g�Ȑ�
@param  p0          �n�_
@param  v0          �n�_�x�N�g��
@param  p1          �I�_
@param  v1          �I�_�x�N�g��
@param  s           ��Ԕ䗦(0 �` 1)
@return Vector3     �w����W
******************************************************************************/

Vector3* Vector3::Hermite(
    Vector3 *pOut,
    Vector3 *p0, Vector3 *v0,
    Vector3 *p1, Vector3 *v1,
    float s)
{

    Vector3 Vec;

    float u1 = s;
    float u2 = u1*u1;
    float u3 = u1*u1*u1;
    float mP0 = 2 * u3 - 3 * u2 + 0 + 1;
    float mV0 = u3 - 2 * u2 + u1;
    float mP1 = -2 * u3 + 3 * u2;
    float mV1 = u3 - u2;

    Vec.x = p0->x*mP0 + v0->x*mV0 + p1->x*mP1 + v1->x*mV1;
    Vec.y = p0->y*mP0 + v0->y*mV0 + p1->y*mP1 + v1->y*mV1;
    Vec.z = p0->z*mP0 + v0->z*mV0 + p1->z*mP1 + v1->z*mV1;

    *pOut = Vec;
    return pOut;
}

/******************************************************************************
@brief  �x�W�F�Ȑ�
@param  p0          �n�_
@param  p1          ����_1
@param  p2          ����X2
@param  p3          �I�_
@param  s           ��Ԕ䗦(0 �` 1)
@return Vector3     �w����W
******************************************************************************/

Vector3* Vector3::Bezier(
    Vector3 *pOut,
    Vector3 *p0, Vector3 *p1,
    Vector3 *p2, Vector3 *p3,
    float s)
{

    Vector3 Vec;

    float u = s;
    float mP0 = (1 - u)*(1 - u)*(1 - u);
    float mP1 = 3 * u     * (1 - u)*(1 - u);
    float mP2 = 3 * u*u   * (1 - u);
    float mP3 = u*u*u;

    Vec.x = p0->x*mP0 + p1->x*mP1 + p2->x*mP2 + p3->x*mP3;
    Vec.y = p0->y*mP0 + p1->y*mP1 + p2->y*mP2 + p3->y*mP3;
    Vec.z = p0->z*mP0 + p1->z*mP1 + p2->z*mP2 + p3->z*mP3;

    *pOut = Vec;
    return pOut;
}

/******************************************************************************
@brief  B�X�v���C���Ȑ�
@param  p0          �n�_
@param  p1          ����_1
@param  p2          ����X2
@param  p3          �I�_
@param  s           ��Ԕ䗦(0 �` 1)
@return Vector3     �w����W
******************************************************************************/

Vector3* Vector3::BSpline(
    Vector3 *pOut,
    Vector3 *p0, Vector3 *p1,
    Vector3 *p2, Vector3 *p3,
    float s)
{
    Vector3 Vec;

    float u1 = s;
    float u2 = u1*u1;
    float u3 = u1*u1*u1;
    float mP0 = (-1 * u3 + 3 * u2 - 3 * u1 + 1)*1.0f / 6;
    float mP1 = (3 * u3 - 6 * u2 + 4)*1.0f / 6;
    float mP2 = (-3 * u3 + 3 * u2 + 3 * u1 + 1)*1.0f / 6;
    float mP3 = (1 * u3)*1.0f / 6;

    Vec.x = p0->x*mP0 + p1->x*mP1 + p2->x*mP2 + p3->x*mP3;
    Vec.y = p0->y*mP0 + p1->y*mP1 + p2->y*mP2 + p3->y*mP3;
    Vec.z = p0->z*mP0 + p1->z*mP1 + p2->z*mP2 + p3->z*mP3;

    *pOut = Vec;
    return pOut;
}

/******************************** ���������܂� *******************************/

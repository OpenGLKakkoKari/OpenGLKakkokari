/*****************************************************************************/
/*!
@file   Vector2.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/


/*  �C���N���[�h
******************************************************************************/


#include "Vector2.h"
#include <math.h>

using Framework::Vector2;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  ���ώZ�o
@param  pV1         ���̓x�N�g��1
@param  pV2         ���̓x�N�g��2
@return float       ����
******************************************************************************/

float Vector2::Dot(const Vector2 *pV1, const Vector2 *pV2)
{
    return (pV1->x * pV2->x) + (pV1->y * pV2->y);
}

/******************************************************************************
@brief  �O�ώZ�o
@param  pV1         ���̓x�N�g��1
@param  pV2         ���̓x�N�g��2
@return float       �O��
******************************************************************************/

float Vector2::Cross(const Vector2 *pV1, const Vector2 *pV2)
{
    return (pV1->x * pV2->y) - (pV1->y * pV2->x);
}

/******************************************************************************
@brief  �x�N�g���̒����Z�o
@param  pV          ���̓x�N�g��
@return float       �x�N�g���̒���
******************************************************************************/

float Vector2::Length(const Vector2 *pV)
{
    return sqrt( pV->x * pV->x + pV->y * pV->y);
}

/******************************************************************************
@brief  �����Z�o
@param  pV1         ���̓x�N�g��1
@param  pV2         ���̓x�N�g��2
@return float       ����
******************************************************************************/

float Vector2::Distance(const Vector2 *pV1, const Vector2 *pV2)
{
    return Vector2::Length(pV1) - Vector2::Length(pV2);
}

/******************************************************************************
@brief  �x�N�g���̐��K��
@param  pOut        �o�̓x�N�g��
@param  pV          ���̓x�N�g��
******************************************************************************/

Vector2 *Vector2::Normalize(Vector2 *pOut, const Vector2 *pV)
{
    *pOut = *pV / Length(pV);

    return pOut;
}

/******************************** ���������܂� *******************************/
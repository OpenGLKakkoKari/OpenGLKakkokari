/*****************************************************************************/
/*!
@file   Quaternion.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Quaternion.h"
#include <math.h>


using Framework::Quaternion;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �N�H�[�^�j�I���̋��ʐ��`���
@param  pOut        ��ԍς݂̃N�H�[�^�j�I��
@param  pQ1         �n�_
@param  pQ2         �I�_
@param  t           ����
******************************************************************************/

Quaternion* Quaternion::Slerp(Quaternion* pOut, Quaternion* pQ1, Quaternion* pQ2, float t)
{
    Quaternion q;
    if (pQ1->x == pQ2->x && pQ1->y == pQ2->y && pQ1->z == pQ2->z && pQ1->w == pQ2->w)
    {
        *pOut = *pQ2; return pOut;
    } 

    float qr = pQ1->w * pQ2->w + pQ1->x * pQ2->x + pQ1->y * pQ2->y + pQ1->z * pQ2->z;
    float ss = 1.0f - qr * qr;

    if (ss == 0.0f) {
        q.w = pQ1->w;
        q.x = pQ1->x;
        q.y = pQ1->y;
        q.z = pQ1->z;
    }
    else {
        float sp = sqrt(ss);
        float ph = acos(qr);
        float pt = ph * t;
        float t1 = sin(pt) / sp;
        float t0 = sin(ph - pt) / sp;

        q.w = pQ1->w * t0 + pQ2->w * t1;
        q.x = pQ1->x * t0 + pQ2->x * t1;
        q.y = pQ1->y * t0 + pQ2->y * t1;
        q.z = pQ1->z * t0 + pQ2->z * t1;
    }
    *pOut = q;
    return pOut;
}

/******************************** ���������܂� *******************************/

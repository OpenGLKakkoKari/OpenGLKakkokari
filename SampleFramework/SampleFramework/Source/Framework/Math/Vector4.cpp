/*****************************************************************************/
/*!
@file   Vector4.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/


/*  �C���N���[�h
******************************************************************************/


#include "Vector4.h"
#include <math.h>
#include "..\Math\Math.h"


using Framework::Vector4;
using Framework::Matrix;
using namespace Framework::Math;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �g�����X�t�H�[��
@param  pOut        �o�̓x�N�g��
@param  pV          ���̓x�N�g��
@param  pM          ���͍s��
@return Vector3*    �o�̓x�N�g��
******************************************************************************/

Vector4 *Vector4::Transform(Vector4 *pOut, Vector4 *pV, Matrix *pM)
{

    pOut->x = (pV->x    * pM->_11
             + pV->y    * pM->_21
             + pV->z    * pM->_31
             + pV->w    * pM->_41);
    
    pOut->y = (pV->x    * pM->_12
             + pV->y    * pM->_22
             + pV->z    * pM->_32
             + pV->w    * pM->_42);
    
    pOut->z = (pV->x    * pM->_13
             + pV->y    * pM->_23
             + pV->z    * pM->_33
             + pV->w    * pM->_43);

    pOut->w = (pV->x    * pM->_14
             + pV->y    * pM->_24
             + pV->z    * pM->_34
             + pV->w    * pM->_44);

    return pOut;
}

/******************************** ���������܂� *******************************/

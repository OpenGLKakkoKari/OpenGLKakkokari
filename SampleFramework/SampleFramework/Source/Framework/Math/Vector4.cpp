/*****************************************************************************/
/*!
@file   Vector4.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/


/*  インクルード
******************************************************************************/


#include "Vector4.h"
#include <math.h>
#include "..\Math\Math.h"


using Framework::Vector4;
using Framework::Matrix;
using namespace Framework::Math;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  トランスフォーム
@param  pOut        出力ベクトル
@param  pV          入力ベクトル
@param  pM          入力行列
@return Vector3*    出力ベクトル
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

/******************************** 実装ここまで *******************************/

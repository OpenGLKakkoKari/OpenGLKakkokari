/*****************************************************************************/
/*!
@file   Object.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Object.h"


using namespace Framework;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/

Object::Object() :
pos_(Vector3(0.0f, 0.0f, 0.0f)),
rot_(Vector3(0.0f, 0.0f, 0.0f)),
scale_(Vector3(1.0f, 1.0f, 1.0f)),
isUsed_(true)
{
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

Object::~Object()
{
}

/******************************************************************************
@brief  親行列取得
@param  pOut        親行列
******************************************************************************/

void Object::GetMatrix(Matrix* pOut)
{
    Matrix sclMat, rotMat, transMat, worldMat, parentMat;

    Matrix::Scale(&sclMat, scale_.x, scale_.y, scale_.z);
    Matrix::RotationYXZ(&rotMat, rot_.x, rot_.y, rot_.z);
    Matrix::Translation(&transMat, pos_.x, pos_.y, pos_.z);

    Matrix::Multiply(&worldMat, &sclMat, &rotMat);
    Matrix::Multiply(&worldMat, &worldMat, &transMat);

    if (parent_)
    {
        parent_->GetMatrix(&parentMat);
        Matrix::Multiply(pOut, &worldMat, &parentMat);
    }
    else
    {
        *pOut = worldMat;
    }
}

/******************************** 実装ここまで *******************************/

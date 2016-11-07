/*****************************************************************************/
/*!
@file   Object.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Object.h"


using namespace Framework;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

Object::Object() :
pos_(Vector3(0.0f, 0.0f, 0.0f)),
rot_(Vector3(0.0f, 0.0f, 0.0f)),
scale_(Vector3(1.0f, 1.0f, 1.0f)),
isUsed_(true)
{
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

Object::~Object()
{
}

/******************************************************************************
@brief  �e�s��擾
@param  pOut        �e�s��
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

/******************************** ���������܂� *******************************/

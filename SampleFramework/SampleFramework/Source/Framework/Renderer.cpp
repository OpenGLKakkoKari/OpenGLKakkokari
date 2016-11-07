/*****************************************************************************/
/*!
@file   Renderer.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Manager.h"
#include "Renderer.h"
#include "Math\Math.h"


using namespace Framework;
using namespace Framework::Math;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �J����2D�E3D�؂�ւ�
@param  isEnabled   3D�\���̏ꍇtrue 2D�\���̏ꍇfalse
******************************************************************************/

void Renderer::SetTranslationMode(bool isEnabled)
{
    if (isEnabled)
    {
        Matrix::SetLookAtLH(&ViewMatrix, &pCamera->Eye, &pCamera->At, &pCamera->Up);
        Matrix::SetPerspectiveFovLH(&ProjectionMatrix, Math::ToRad(45.0f), (float)Manager::GetWindow()->GetWidth(), (float)Manager::GetWindow()->GetHeight(), 10.0f, 12000.0f);
    }
    else
    {
        Matrix::Identity(&ViewMatrix);
        Matrix::Identity(&ProjectionMatrix);
        ProjectionMatrix._11 = 2.0f / (float)Manager::GetWindow()->GetWidth();
        ProjectionMatrix._22 = 2.0f / (float)Manager::GetWindow()->GetHeight();
    }
}

/******************************* ���������܂� ********************************/
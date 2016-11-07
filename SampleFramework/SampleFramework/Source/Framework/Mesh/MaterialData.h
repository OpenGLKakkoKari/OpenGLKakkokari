#pragma once
/******************************************************************************
/*!
@file   MaterialData.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "..\Color.h"


/*  �N���X��`
******************************************************************************/


namespace Framework
{
    struct MaterialData
    {

        ColorValue ambient;
        ColorValue diffuse;
        ColorValue specular;
        ColorValue emissive;
        float power;

        char fileName[256];
    };
}


/****************************** �w�b�_�����܂� *******************************/

#pragma once
/******************************************************************************
/*!
@file   Material.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Color.h"
#include "Texture\Texture.h"


/*  �N���X��`
******************************************************************************/


namespace Framework
{
    class Material
    {
    public:

        ColorValue ambient;
        ColorValue diffuse;
        ColorValue specular;
        ColorValue emissive;
        float power;

        Texture *pTexture;
    };
}


/****************************** �w�b�_�����܂� *******************************/

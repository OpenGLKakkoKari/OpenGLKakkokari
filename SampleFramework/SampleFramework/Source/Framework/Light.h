#pragma once
/******************************************************************************
/*!
@file   Light.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Color.h"
#include "Math\Vector4.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class Light
    {
    public:
        typedef enum
        {
            POINT         = 1,
            SPOT          = 2,
            DIRECTIONAL   = 3,
        }Type;

        Light::Type     type;
        ColorValue      diffuse;
        ColorValue      specular;
        ColorValue      ambient;
        Vector3         position;
        Vector3         direction;
        float           range;
        float           falloff;
        float           attenuation0;
        float           attenuation1;
        float           attenuation2;
        float           theta;
        float           phi;
    };
}


/******************************* ヘッダここまで ******************************/

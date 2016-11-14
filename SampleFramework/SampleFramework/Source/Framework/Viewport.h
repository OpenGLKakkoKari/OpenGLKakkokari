#pragma once
/******************************************************************************
/*!
@file   Viewport.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Viewport.h"


/*  �N���X��`
******************************************************************************/


namespace Framework
{
    class Viewport
    {
    public:
        Viewport() : X(0), Y(0), width(0), height(0), minZ(0.0f), maxZ(0) {}

        int   X;
        int   Y;
        int   width;
        int   height;
        float minZ;
        float maxZ;

        static Viewport* Set(Viewport *pOut, int X, int Y, int Width, int Height);
    };
}


/******************************* �w�b�_�����܂� ******************************/

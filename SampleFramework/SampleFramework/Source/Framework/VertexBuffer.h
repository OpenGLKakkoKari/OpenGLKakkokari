#pragma once
/******************************************************************************
/*!
@file   VertexBuffer.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Vertex.h"


/*  �N���X��`
******************************************************************************/


namespace Framework
{

    class VertexBuffer
    {
    public:
        VertexBuffer() : vertexNum(0){}
        virtual ~VertexBuffer(){}

        virtual Vertex* Lock() = 0;
        virtual void Unlock() = 0;
        virtual void Release() = 0;

        int vertexNum;
    };
}


/******************************* �w�b�_�����܂� ******************************/

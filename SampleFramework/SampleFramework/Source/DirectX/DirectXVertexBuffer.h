#pragma once
/*****************************************************************************/
/*!
@file   DirectXVertexBuffer.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "DirectX.h"
#include "..\Framework\VertexBuffer.h"


/*  �N���X��`
******************************************************************************/


namespace DirectX
{
    class VertexBuffer : public Framework::VertexBuffer
    {
    public:
        VertexBuffer(){}
        virtual ~VertexBuffer(){}

        Framework::Vertex* Lock()
        {
            Framework::Vertex* vtx;
            pVertexBuffer->Lock(0, 0, (void**)&vtx, 0);
            return vtx;
        }

        void Unlock()
        {
            pVertexBuffer->Unlock();
        }

        void Release()
        {
            pVertexBuffer->Release(); delete this;
        }

        LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;
    };
}


/******************************* �w�b�_�����܂� ******************************/

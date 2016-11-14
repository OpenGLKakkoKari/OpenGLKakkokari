#pragma once
/*****************************************************************************/
/*!
@file   DirectXIndexBuffer.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "DirectX.h"
#include "..\Framework\IndexBuffer.h"


/*  クラス定義
******************************************************************************/


namespace DirectX
{
    class IndexBuffer : public Framework::IndexBuffer
    {
    public:
        IndexBuffer(){}
        virtual ~IndexBuffer(){}

        int* Lock()
        {
            int* index;
            pIndexBuffer->Lock(0, 0, (void**)&index, 0);
            return index;
        }

        void Unlock()
        {
            pIndexBuffer->Unlock();
        }

        void Release()
        {
            pIndexBuffer->Release(); delete this;
        }

        LPDIRECT3DINDEXBUFFER9 pIndexBuffer;
    };
}


/******************************* ヘッダここまで ******************************/

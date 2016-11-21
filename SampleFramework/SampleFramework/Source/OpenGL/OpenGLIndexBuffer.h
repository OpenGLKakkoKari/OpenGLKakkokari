#pragma once
/******************************************************************************
/*!
@file   OpenGLIndexBuffer.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "OpenGL.h"
#include "..\Framework\IndexBuffer.h"


/*  クラス定義
******************************************************************************/


namespace OpenGL
{
    class IndexBuffer : public Framework::IndexBuffer
    {
    public:
        IndexBuffer() : idxVBO(0){}
        virtual ~IndexBuffer(){}

        int* Lock()
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idxVBO);
            int* idx = (int*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
            return idx;
        }

        void Unlock()
        {
            glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        void Release()
        {
            glDeleteBuffers(1, &idxVBO);
            delete this;
        }

        unsigned int idxVBO;
    };
}


/****************************** ヘッダここまで *******************************/

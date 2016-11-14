#pragma once
/******************************************************************************
/*!
@file   OpenGLVertexBuffer.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "OpenGL.h"
#include "..\Framework\VertexBuffer.h"


/*  クラス定義
******************************************************************************/


namespace OpenGL
{
    class VertexBuffer : public Framework::VertexBuffer
    {
    public:
        VertexBuffer() : vrtVBO(0){}
        virtual ~VertexBuffer(){}

        Framework::Vertex* Lock()
        {
            glBindBuffer(GL_ARRAY_BUFFER, vrtVBO);
            Framework::Vertex* vtx = (Framework::Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
            return vtx;
        }

        void Unlock()
        {
            glUnmapBuffer(GL_ARRAY_BUFFER);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        void Release()
        {
            glDeleteBuffers(1, &vrtVBO);
            delete this;
        }

        unsigned int vrtVBO;
    };
}


/****************************** ヘッダここまで *******************************/

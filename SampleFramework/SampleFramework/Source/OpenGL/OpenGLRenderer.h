#pragma once
/******************************************************************************
/*!
@file   OpenGLRenderer.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include <Windows.h>
#include "../Framework/Renderer.h"

#include "OpenGL.h"
#include "OpenGLTexture.h"


/*  �N���X��`
******************************************************************************/


namespace OpenGL
{
    class Renderer : public Framework::Renderer
    {
    public:
        Renderer();
        virtual ~Renderer();

        void Init(Windows::GameWindow *pGameWindow);
        void Uninit();

        void Clear();
        void Flip();

        void SetLight(int index, Framework::Light *pLight);
        void SetLight(int index, bool isLight);
        void SetLightEnable(bool isLight);
        void SetTexture(Framework::Texture *pTexture);
        void SetMaterial(Framework::Material *pMaterial);
        void SetBlend(Blend SrcBlend, Blend DestBlend);
        void SetZTestEnable(bool isZEnable);
        void SetZWriteEnable(bool isZEnable);
        void SetAlphaTestEnable(bool isAlphaEnable);
        void SetSamplerState(SamplerStateType ssType, TextureAddress ta);
        void SetVertexColorEnable(bool isEnable);
        void SetTextureEnable(bool isEnable);
        void SetWireFrameEnable(bool isEnable);
        void SetCullingEnable(bool isEnable);

        Framework::VertexBuffer* CreateVertexBuffer(int vertexNum);
        Framework::IndexBuffer* CreateIndexBuffer(int indexNum);

        void DrawPrimitiveUP(
            Renderer::PrimitiveType PriType,
            const Framework::Vertex *pVertex, int PriNum);

        void DrawIndexedPrimitiveUP(
            Framework::Renderer::PrimitiveType PriType,
            unsigned int StartIndex,
            unsigned int VertexNum,
            const int *pIndex,
            const Framework::Vertex *pVertex,
            unsigned int Count);

        void DrawPrimitive(Framework::Renderer::PrimitiveType PriType);
        void DrawIndexedPrimitive(Framework::Renderer::PrimitiveType PriType,
            int StartIndex,
            int Count);

    private:
        void Lighting();

        Texture *pTex;

        PIXELFORMATDESCRIPTOR pfd;
        HWND hWnd;
        HGLRC glrc;                 // GL�����_�����O�R���e�L�X�g
        HDC hDC;                    // �f�o�C�X�R���e�L�X�g

        Framework::Light*       pLight[8];
    };
}


/****************************** �w�b�_�����܂� *******************************/

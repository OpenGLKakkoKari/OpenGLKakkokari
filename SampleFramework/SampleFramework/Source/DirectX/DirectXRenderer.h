#pragma once
/*****************************************************************************/
/*!
@file   DirectXRenderer.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include <Windows.h>
#include "../Framework/Renderer.h"

#include "DirectX.h"
#include "DirectXTexture.h"


/*  クラス定義
******************************************************************************/


namespace DirectX
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
            Framework::Renderer::PrimitiveType PriType,
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

        LPDIRECT3DDEVICE9 GetDevice() { return pD3DDev; }

    private:
        LPDIRECT3D9       pD3D;         //!< Direct3Dオブジェクトへのポインタ
        LPDIRECT3DDEVICE9 pD3DDev;      //!< Direct3Dデバイスへのポインタ

        DirectX::Texture *pTex;
    };
}


/****************************** ヘッダここまで *******************************/

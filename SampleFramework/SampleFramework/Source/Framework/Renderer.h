#pragma once
/******************************************************************************
/*!
@file   Renderer.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Windows\GameWindow.h"
#include "Math\Matrix.h"
#include "Vertex.h"
#include "Texture\Texture.h"
#include "Viewport.h"
#include "Light.h"
#include "Material.h"
#include "Camera.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class Renderer
    {
    public:
        enum RendererType
        {
            DIRECTX9,
            OPENGL,
        };
        
        enum SamplerStateType
        {
            SAMP_ADDRESSU = 1,
            SAMP_ADDRESSV = 2,
            SAMP_ADDRESSW = 3,
            SAMP_BORDERCOLOR = 4,
            SAMP_MAGFILTER = 5,
            SAMP_MINFILTER = 6,
            SAMP_MIPFILTER = 7,
            SAMP_MIPMAPLODBIAS = 8,
            SAMP_MAXMIPLEVEL = 9,
            SAMP_MAXANISOTROPY = 10,
            SAMP_SRGBTEXTURE = 11,


            SAMP_ELEMENTINDEX = 12,

            SAMP_DMAPOFFSET = 13
        };

        enum TextureAddress
        {
            TADDRESS_WRAP = 1,
            TADDRESS_MIRROR = 2,
            TADDRESS_CLAMP = 3,
            TADDRESS_BORDER = 4,
            TADDRESS_MIRRORONCE = 5
        };

        enum PrimitiveType
        {
            PRIMITIVE_TYPE_LINE_LIST,
            PRIMITIVE_TYPE_LINE_STRIP,

            PRIMITIVE_TYPE_TRIANGLE_LIST,
            PRIMITIVE_TYPE_TRIANGLE_STRIP,
            PRIMITIVE_TYPE_TRIANGLE_FAN
        };

        enum Blend
        {
            BLEND_ZERO,
            BLEND_ONE,

            BLEND_SRC_COLOR,
            BLEND_SRC_INVCOLOR,
            BLEND_SRC_ALPHA,
            BLEND_SRC_INVALPHA,

            BLEND_DEST_COLOR,
            BLEND_DEST_INVCOLOR,
            BLEND_DEST_ALPHA,
            BLEND_DEST_INVALPHA,

        };

        Renderer();
        virtual ~Renderer(){}

        virtual void Init(Windows::GameWindow *pWindow){}
        virtual void Uninit() = 0;

        virtual void Clear() = 0;
        virtual void Flip() = 0;

        virtual void SetLight(int index, Light *pLight) = 0;
        virtual void SetLight(int index, bool isLight) = 0;
        virtual void SetLightEnable(bool isLight) = 0;
        virtual void SetTexture(Texture *pTexture) = 0;
        virtual void SetMaterial(Material *pMaterial) = 0;
        virtual void SetBlend(Blend SrcBlend, Blend DestBlend) = 0;
        virtual void SetZTestEnable(bool isZEnable) = 0;
        virtual void SetZWriteEnable(bool isZEnable) = 0;
        virtual void SetAlphaTestEnable(bool isZEnable) = 0;
        virtual void SetSamplerState(SamplerStateType ssType, TextureAddress ta) = 0;
        virtual void SetVertexColorEnable(bool isEnable) = 0;
        virtual void SetTextureEnable(bool isEnable) = 0;
        virtual void SetWireFrameEnable(bool isEnable) = 0;
        virtual void SetCullingEnable(bool isEnable) = 0;
        virtual void SetTranslationMode(bool isEnabled);

        virtual VertexBuffer* CreateVertexBuffer(int vertexNum) = 0;
        virtual IndexBuffer* CreateIndexBuffer(int indexNum) = 0;

        virtual void SetVertexBuffer(VertexBuffer* pVertexBuffer)
            { this->pVertexBuffer = pVertexBuffer; }
        virtual void SetIndexBuffer(IndexBuffer* pIndexBuffer)
            { this->pIndexBuffer = pIndexBuffer; }

        virtual void DrawPrimitiveUP(
            PrimitiveType PriType,
            const Framework::Vertex *pVertex, int PriNum) = 0;

        virtual void DrawIndexedPrimitiveUP(
            Framework::Renderer::PrimitiveType PriType,
            unsigned int StartIndex,
            unsigned int VertexNum,
            const int *pIndex,
            const Framework::Vertex *pVertex,
            unsigned int Count) = 0;

        virtual void DrawPrimitive(PrimitiveType PriType) = 0;
        virtual void DrawIndexedPrimitive(PrimitiveType PriType, int StartIndex, int Count) = 0;

        virtual void SetWorldMatrix(Matrix *pWorldMat)  { WorldMatrix = *pWorldMat; }
        virtual void SetCamera(Camera* pNewCamera)      { pCamera = pNewCamera; }

        virtual Matrix GetWorldMatrix()                 { return WorldMatrix; }
        virtual Matrix GetViewMatrix()                  { return ViewMatrix; }
        virtual Matrix GetProjectionMatrix()            { return ProjectionMatrix; }
        virtual Camera* GetCamera()                     { return pCamera; }
        virtual RendererType GetRendererType()          { return type; }

    protected:
        Matrix WorldMatrix;
        Matrix ViewMatrix;
        Matrix ProjectionMatrix;
        Camera*  pCamera;

        RendererType type;
        VertexBuffer* pVertexBuffer;
        IndexBuffer* pIndexBuffer;
    };
}


/****************************** ヘッダここまで *******************************/

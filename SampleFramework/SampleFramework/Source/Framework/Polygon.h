#pragma once
/******************************************************************************
/*!
@file   Polygon.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "DrawObject.h"
#include "Vertex.h"
#include "VertexBuffer.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class Polygon : public DrawObject
    {
    public:
        Polygon();
        virtual ~Polygon();

        virtual void Draw();

        static Polygon* Create(const Vector3& pos, const Vector2& size, Color col);
        static Polygon* Create(const Vector3& pos, const Vector2& size, Color col, const char *FileName);

        virtual void SetColor(Color color);
        virtual void SetColor(Color v1, Color v2, Color v3, Color v4);
        virtual void SetScale(const Vector2& size)      { scale_ = Vector3(size.x, size.y, 0.0f); }

        virtual void SetVertexUV(const Vector2& uv1, const Vector2& uv2);
        virtual void SetVertexPosition(const Vector3& vec1, const Vector3& vec2, const Vector3& vec3, const Vector3& vec4);
        virtual void SetVertexNormal(const Vector3& vec1, const Vector3& vec2, const Vector3& vec3, const Vector3& vec4);
        virtual void SetTexture(const char* FileName)   { texture_ = Texture::Load(FileName); }
        virtual void SetTexture(Texture *tex)           { texture_ = tex; }

        Vertex          vtx[4];
        Texture*        texture_;
    };
}


/****************************** ヘッダここまで *******************************/

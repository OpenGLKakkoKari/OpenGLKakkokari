/*****************************************************************************/
/*!
@file   Polygon.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Polygon.h"
#include "Manager.h"


using namespace Framework;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/

Polygon::Polygon() : texture_(NULL)
{
    vtx[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
    vtx[0].nor = Vector3(0.0f, 0.0f, -1.0f);
    vtx[0].col = Color(255, 255, 255, 255);
    vtx[0].tex = Vector2(0.0f, 0.0f);

    vtx[1].pos = Vector3(0.5f, 0.5f, 0.0f);
    vtx[1].nor = Vector3(0.0f, 0.0f, -1.0f);
    vtx[1].col = Color(255, 255, 255, 255);
    vtx[1].tex = Vector2(1.0f, 0.0f);

    vtx[2].pos = Vector3(-0.5f, -0.5f, 0.0f);
    vtx[2].nor = Vector3(0.0f, 0.0f, -1.0f);
    vtx[2].col = Color(255, 255, 255, 255);
    vtx[2].tex = Vector2(0.0f, 1.0f);

    vtx[3].pos = Vector3(0.5f, -0.5f, 0.0f);
    vtx[3].nor = Vector3(0.0f, 0.0f, -1.0f);
    vtx[3].col = Color(255, 255, 255, 255);
    vtx[3].tex = Vector2(1.0f, 1.0f);
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

Polygon::~Polygon()
{
    if (texture_)
    {
        texture_->Release();
        texture_ = NULL;
    }
}

/******************************************************************************
@brief  描画処理
******************************************************************************/

void Polygon::Draw(void)
{
    Matrix WorldMatrix, transMat, rotMat, scaMat;

    Matrix::Identity(&WorldMatrix);
    Matrix::Scale(&scaMat, scale_.x, scale_.y, scale_.z);
    Matrix::RotationYXZ(&rotMat, rot_.x, rot_.y, rot_.z);
    Matrix::Translation(&transMat, pos_.x, pos_.y, pos_.z);

    Matrix::Multiply(&WorldMatrix, &WorldMatrix, &scaMat);
    Matrix::Multiply(&WorldMatrix, &WorldMatrix, &rotMat);
    Matrix::Multiply(&WorldMatrix, &WorldMatrix, &transMat);
    
    Manager::GetRenderer()->SetTranslationMode(true);
    Manager::GetRenderer()->SetTexture(texture_);
    Manager::GetRenderer()->SetMaterial(NULL);
    Manager::GetRenderer()->SetLightEnable(true);
    Manager::GetRenderer()->SetWorldMatrix(&WorldMatrix);
    Manager::GetRenderer()->DrawPrimitiveUP(Framework::Renderer::PRIMITIVE_TYPE_TRIANGLE_STRIP, vtx, 2);
}

/******************************************************************************
@brief  ポリゴン頂点の座標設定
@param  vec1        左上頂点のベクトル
@param  vec2        右上頂点のベクトル
@param  vec3        左下頂点のベクトル
@param  vec4        右下頂点のベクトル
******************************************************************************/

void Polygon::SetVertexPosition(const Vector3& vec1, const Vector3& vec2, const Vector3& vec3, const Vector3& vec4)
{
    vtx[0].pos = Vector3(vec1.x, vec1.y, vec1.z);
    vtx[1].pos = Vector3(vec2.x, vec2.y, vec2.z);
    vtx[2].pos = Vector3(vec3.x, vec3.y, vec3.z);
    vtx[3].pos = Vector3(vec4.x, vec4.y, vec4.z);
}

/******************************************************************************
@brief  ポリゴン頂点の法線設定
@param  vec1        左上頂点のベクトル
@param  vec2        右上頂点のベクトル
@param  vec3        左下頂点のベクトル
@param  vec4        右下頂点のベクトル
******************************************************************************/

void Polygon::SetVertexNormal(const Vector3& vec1, const Vector3& vec2, const Vector3& vec3, const Vector3& vec4)
{
    vtx[0].nor = Vector3(vec1.x, vec1.y, vec1.z);
    vtx[1].nor = Vector3(vec2.x, vec2.y, vec2.z);
    vtx[2].nor = Vector3(vec3.x, vec3.y, vec3.z);
    vtx[3].nor = Vector3(vec4.x, vec4.y, vec4.z);
}

/******************************************************************************
@brief  ポリゴン頂点のUV設定
@param  uv1         左上頂点のUV
@param  uv2         右下頂点のUV
******************************************************************************/

void Polygon::SetVertexUV(const Vector2& uv1, const Vector2& uv2)
{
    vtx[0].tex = Vector2(uv1.x, uv1.y);
    vtx[1].tex = Vector2(uv2.x, uv1.y);
    vtx[2].tex = Vector2(uv1.x, uv2.y);
    vtx[3].tex = Vector2(uv2.x, uv2.y);
}

/******************************************************************************
@brief  ポリゴン生成処理
@param  pos             座標
@param  size            サイズ
@param  col             色
@param  FileName        テクスチャのファイル名
@return Polygon*        ポリゴン情報へのポインタ
******************************************************************************/

Framework::Polygon* Polygon::Create(const Vector3& pos, const Vector2& size, Color col, const char *FileName)
{
    Polygon *pPolygon = new Polygon;
    pPolygon->SetPosition(pos);
    pPolygon->SetScale(size);
    pPolygon->SetColor(col);
    pPolygon->SetTexture(FileName);
    return pPolygon;
}
Framework::Polygon* Polygon::Create(const Vector3& pos, const Vector2& size, Color col)
{
    Polygon *pPolygon = new Polygon;
    pPolygon->SetPosition(pos);
    pPolygon->SetScale(size);
    pPolygon->SetColor(col);
    return pPolygon;
}

/******************************************************************************
@brief  ポリゴンの色設定
@param  v1              左上の頂点色
@param  v2              右上の頂点色
@param  v3              左下の頂点色
@param  v4              右下の頂点色
******************************************************************************/

void Polygon::SetColor(Color color)
{
    if (Manager::GetRenderer()->GetRendererType() == Renderer::DIRECTX9)
    {
        vtx[0].col = color;
        vtx[1].col = color;
        vtx[2].col = color;
        vtx[3].col = color;
    }
    else
    {
        vtx[0].col = Color(color.b, color.g, color.r, color.a);
        vtx[1].col = Color(color.b, color.g, color.r, color.a);
        vtx[2].col = Color(color.b, color.g, color.r, color.a);
        vtx[3].col = Color(color.b, color.g, color.r, color.a);
    }
}
void Polygon::SetColor(Color v1, Color v2, Color v3, Color v4)
{
    if (Manager::GetRenderer()->GetRendererType() == Renderer::DIRECTX9)
    {
        vtx[0].col = v1;
        vtx[1].col = v2;
        vtx[2].col = v3;
        vtx[3].col = v4;
    }
    else
    {
        vtx[0].col = Color(v1.b, v1.g, v1.r, v1.a);
        vtx[1].col = Color(v2.b, v2.g, v2.r, v2.a);
        vtx[2].col = Color(v3.b, v3.g, v3.r, v3.a);
        vtx[3].col = Color(v4.b, v4.g, v4.r, v4.a);
    }
}


/******************************** 実装ここまで *******************************/

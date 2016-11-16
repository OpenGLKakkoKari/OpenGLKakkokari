/*****************************************************************************/
/*!
@file   OpenGLRenderer.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "OpenGLRenderer.h"
#include "OpenGLTexture.h"
#include <crtdbg.h>
#include "OpenGLVertexBuffer.h"
#include "OpenGLIndexBuffer.h"


using OpenGL::Renderer;
using namespace Framework;
using namespace Windows;


/*  マクロ定義
******************************************************************************/


#define BUFFER_OFFSET(i) ((void*)(i))


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/


OpenGL::Renderer::Renderer() 
    : pTex(NULL), hWnd(NULL), glrc(NULL), hDC(NULL)
{
    type = OPENGL;
    for (int i = 0; i < LIGHT_MAX; i++)
    {
        pLight[i] = NULL;
    }
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

OpenGL::Renderer::~Renderer()
{
}

/******************************************************************************
@brief  初期化処理
@param  pGameWindow     ウインドウ情報
******************************************************************************/

void OpenGL::Renderer::Init(GameWindow *pGameWindow)
{
    
    OpenGL::Renderer::hWnd = pGameWindow->GetHandle();

/**
 * OpenGL初期化
 */
    
    // ピクセルフォーマット初期化
    pfd.nSize           = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion        = 1;                                // バージョン
    pfd.dwFlags         = ( PFD_DRAW_TO_WINDOW |            // ウインドウをサポート
                            PFD_SUPPORT_OPENGL |            // OpenGLをサポート
                            PFD_DOUBLEBUFFER);              // ダブルバッファ使用
    pfd.iPixelType      = PFD_TYPE_RGBA;                    // RGBA
    pfd.cColorBits      = 32;                               // カラービット数
    pfd.cRedBits        = 0;
    pfd.cRedShift       = 0;
    pfd.cGreenBits      = 0;
    pfd.cGreenShift     = 0;
    pfd.cBlueBits       = 0;
    pfd.cBlueShift      = 0;
    pfd.cAlphaBits      = 0;
    pfd.cAlphaShift     = 0;
    pfd.cAccumBits      = 0;
    pfd.cAccumRedBits   = 0;
    pfd.cAccumGreenBits = 0;
    pfd.cAccumBlueBits  = 0;
    pfd.cAccumAlphaBits = 0;
    pfd.cDepthBits      = 32;
    pfd.cStencilBits    = 8;
    pfd.cAuxBuffers     = 0;
    pfd.iLayerType      = PFD_MAIN_PLANE;
    pfd.bReserved       = 0;
    pfd.dwLayerMask     = 0;
    pfd.dwVisibleMask   = 0;
    pfd.dwDamageMask    = 0;

    hDC = GetDC(hWnd);
    int format = ChoosePixelFormat(hDC, &pfd);

    // 該当するピクセルフォーマットが無い
    if (format == 0)
        return;

    // OpenGLが使うデバイスコンテキストに指定のピクセルフォーマットをセット
    if (!SetPixelFormat(hDC, format, &pfd))
        return;

    // OpenGLコンテキストを作成
    glrc = wglCreateContext(hDC);

    // 作成されたコンテキストが現在使用中か？
    if (!wglMakeCurrent(hDC, glrc))
        return;

    // GLEW初期化
    glewInit();

    // レンダーステートを初期化
    glEnable(GL_LIGHTING);                                              // ライト有効化
    glFrontFace(GL_CW);                                                 // 時計回りが表
    glCullFace(GL_BACK);                                                // 裏面をカリング
    glEnable(GL_CULL_FACE);                                             // カリング有効
    glEnable(GL_DEPTH_TEST);                                            // Zテスト有効
    glDepthMask(TRUE);                                                  // Zバッファに書込を許可
    glDepthFunc(GL_LEQUAL);                                             // Zテストの条件を設定
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);                  // αカラーの設定
    glEnable(GL_BLEND);                                                 // αブレンド有効化


    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);                              // テクスチャ画像は1バイト単位
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);       // テクスチャU座標はリピート
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);       // テクスチャV座標はリピート
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  // 縮小時近傍補間
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  // 拡大時近傍補間
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);        // テクスチャは乗算合成
    glEnable(GL_TEXTURE_2D);                                            // テクスチャを有効
}

/******************************************************************************
@brief  終了処理
******************************************************************************/

void OpenGL::Renderer::Uninit()
{

    // カレントコンテキストを無効にする
    wglMakeCurrent(NULL, NULL);

    // デバイスコンテキスト解放
    ReleaseDC(hWnd, hDC);

    // カレントコンテキストを削除
    wglDeleteContext(glrc);

}

/******************************************************************************
@brief  画面クリア
******************************************************************************/

void OpenGL::Renderer::Clear()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/******************************************************************************
@brief  バックバッファ表示
******************************************************************************/

void OpenGL::Renderer::Flip()
{
    glFlush();
    SwapBuffers(hDC);
}

/******************************************************************************
@brief  ライト設定
@param  index                   インデックス
@param  Framework::pLight       ライト情報
******************************************************************************/

void OpenGL::Renderer::SetLight(int index, Framework::Light *pLight)
{
    _ASSERT(0 <= index && index <= 7 && "Light Index is from 0 to 7.");
    this->pLight[index] = pLight;
}

/******************************************************************************
@brief  ライト設定
@param  index       インデックス
@param  isLight     ライトがONかOFFかどうか
******************************************************************************/

void OpenGL::Renderer::SetLight(int index, bool isLight)
{
    _ASSERT(0 <= index && index <= 7 && "Light Index is from 0 to 7.");
    unsigned short lightIndex;
    switch (index)
    {
    case 0: lightIndex = GL_LIGHT0; break;
    case 1: lightIndex = GL_LIGHT1; break;
    case 2: lightIndex = GL_LIGHT2; break;
    case 3: lightIndex = GL_LIGHT3; break;
    case 4: lightIndex = GL_LIGHT4; break;
    case 5: lightIndex = GL_LIGHT5; break;
    case 6: lightIndex = GL_LIGHT6; break;
    case 7: lightIndex = GL_LIGHT7; break;
    }
    (isLight) ? (glEnable(lightIndex)) : (glDisable(lightIndex));
}

/******************************************************************************
@brief  ライトのONOFF設定
@param  isLight     ライトがONかOFFかどうか
******************************************************************************/

void OpenGL::Renderer::SetLightEnable(bool isLight)
{
    (isLight) ? (glEnable(GL_LIGHTING)) : (glDisable(GL_LIGHTING));
}

/******************************************************************************
@brief  ライト設定
******************************************************************************/

void OpenGL::Renderer::Lighting()
{
    for (int index = 0; index < 8; index++)
    {
        if (pLight[index] != nullptr)
        {
            unsigned short lightIndex;
            switch (index)
            {
            case 0: lightIndex = GL_LIGHT0; break;
            case 1: lightIndex = GL_LIGHT1; break;
            case 2: lightIndex = GL_LIGHT2; break;
            case 3: lightIndex = GL_LIGHT3; break;
            case 4: lightIndex = GL_LIGHT4; break;
            case 5: lightIndex = GL_LIGHT5; break;
            case 6: lightIndex = GL_LIGHT6; break;
            case 7: lightIndex = GL_LIGHT7; break;
            }

            float position[]  = { pLight[index]->position.x , pLight[index]->position.y , pLight[index]->position.z , 1.0f };
            float diffuse[]   = { pLight[index]->diffuse.r  , pLight[index]->diffuse.g  , pLight[index]->diffuse.b  , pLight[index]->diffuse.a };
            float ambient[]   = { pLight[index]->ambient.r  , pLight[index]->ambient.g  , pLight[index]->ambient.b  , pLight[index]->ambient.a };
            float specular[]  = { pLight[index]->specular.r , pLight[index]->specular.g , pLight[index]->specular.b , pLight[index]->specular.a };
            float direction[] = { -pLight[index]->direction.x, -pLight[index]->direction.y, -pLight[index]->direction.z, 1.0f };

            switch (pLight[index]->type)
            {
            case Framework::Light::DIRECTIONAL:
                // Wを0.0fにする
                direction[3] = 0.0f;
                glLightfv(lightIndex, GL_POSITION, direction);
                glLightfv(lightIndex, GL_DIFFUSE, diffuse);
                glLightfv(lightIndex, GL_AMBIENT, ambient);
                glLightfv(lightIndex, GL_SPECULAR, specular);
                break;

            case Framework::Light::SPOT:
                glLightf(lightIndex, GL_LINEAR_ATTENUATION, 0.01f);
                glLightfv(lightIndex, GL_SPOT_DIRECTION, direction); //スポットライトの向ける方向（デフォルト (0,0,-1.0)）
                glLightf(lightIndex, GL_SPOT_CUTOFF, 30.0f);          // スポットライトの絞り（デフォルト 180.0）
                glLightf(lightIndex, GL_SPOT_EXPONENT, 0.1f);         // スポットライトの中心からの減衰の度合い（デフォルト 0.1f)
                break;

            case Framework::Light::POINT:
                glLightfv(lightIndex, GL_POSITION, position);
                glLightfv(lightIndex, GL_DIFFUSE, diffuse);
                glLightfv(lightIndex, GL_AMBIENT, ambient);
                glLightfv(lightIndex, GL_SPECULAR, specular);
                glLightf(lightIndex, GL_LINEAR_ATTENUATION, 0.01f);
                break;

            }
        }
    }
}

/******************************************************************************
@brief  テクスチャ設定
@param  pTexture    テクスチャ情報
******************************************************************************/

void OpenGL::Renderer::SetTexture(Framework::Texture *pTexture)
{
    pTex = (OpenGL::Texture*)pTexture;

    //　テクスチャをバインド
    if (pTex != nullptr)
        glBindTexture(GL_TEXTURE_2D, pTex->texture);
    else
        glBindTexture(GL_TEXTURE_2D, 0);
}

/******************************************************************************
@brief  マテリアル設定
@param  pMaterial   マテリアル情報
******************************************************************************/

void OpenGL::Renderer::SetMaterial(Framework::Material *pMaterial)
{
    float ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    float diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    float specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float emission[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    float power = 0.0f;
    if (pMaterial)
    {
        ambient[0] = pMaterial->ambient.r;
        ambient[1] = pMaterial->ambient.g;
        ambient[2] = pMaterial->ambient.b;
        ambient[3] = pMaterial->ambient.a;

        diffuse[0] = pMaterial->diffuse.r;
        diffuse[1] = pMaterial->diffuse.g;
        diffuse[2] = pMaterial->diffuse.b;
        diffuse[3] = pMaterial->diffuse.a;

        specular[0] = pMaterial->specular.r;
        specular[1] = pMaterial->specular.g;
        specular[2] = pMaterial->specular.b;
        specular[3] = pMaterial->specular.a;

        emission[0] = pMaterial->emissive.r;
        emission[1] = pMaterial->emissive.g;
        emission[2] = pMaterial->emissive.b;
        emission[3] = pMaterial->emissive.a;

        power = pMaterial->power;
    }

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &power);
}

/******************************************************************************
@brief  ブレンドモード設定
@param  SrcBlend    ソースブレンド
@param  DestBlend   ディストブレンド
******************************************************************************/

void OpenGL::Renderer::SetBlend(Blend SrcBlend, Blend DestBlend)
{
    
    unsigned short srcBlend, destBlend;

    switch (SrcBlend)
    {
    case BLEND_ZERO         : srcBlend = GL_ZERO;                   break;
    case BLEND_ONE          : srcBlend = GL_ONE;                    break;
    case BLEND_SRC_COLOR    : srcBlend = GL_SRC_COLOR;              break;
    case BLEND_SRC_INVCOLOR : srcBlend = GL_ONE_MINUS_SRC_COLOR;    break;
    case BLEND_SRC_ALPHA    : srcBlend = GL_SRC_ALPHA;              break;
    case BLEND_SRC_INVALPHA : srcBlend = GL_ONE_MINUS_SRC_ALPHA;    break;

    case BLEND_DEST_COLOR   : srcBlend = GL_DST_COLOR;              break;
    case BLEND_DEST_INVCOLOR: srcBlend = GL_ONE_MINUS_DST_COLOR;    break;
    case BLEND_DEST_ALPHA   : srcBlend = GL_DST_ALPHA;              break;
    case BLEND_DEST_INVALPHA: srcBlend = GL_ONE_MINUS_DST_ALPHA;    break;
    }

    switch (DestBlend)
    {
    case BLEND_ZERO         : destBlend = GL_ZERO;                  break;
    case BLEND_ONE          : destBlend = GL_ONE;                   break;
    case BLEND_SRC_COLOR    : destBlend = GL_SRC_COLOR;             break;
    case BLEND_SRC_INVCOLOR : destBlend = GL_ONE_MINUS_SRC_COLOR;   break;
    case BLEND_SRC_ALPHA    : destBlend = GL_SRC_ALPHA;             break;
    case BLEND_SRC_INVALPHA : destBlend = GL_ONE_MINUS_SRC_ALPHA;   break;

    case BLEND_DEST_COLOR   : destBlend = GL_DST_COLOR;             break;
    case BLEND_DEST_INVCOLOR: destBlend = GL_ONE_MINUS_DST_COLOR;   break;
    case BLEND_DEST_ALPHA   : destBlend = GL_DST_ALPHA;             break;
    case BLEND_DEST_INVALPHA: destBlend = GL_ONE_MINUS_DST_ALPHA;   break;
    }

    glBlendFunc(srcBlend, destBlend);

}

/******************************************************************************
@brief  ZテストONOFF設定
@param  isZEnable   Zテスト有効無効フラグ
******************************************************************************/

void OpenGL::Renderer::SetZTestEnable(bool isZEnable)
{
    (isZEnable) ? (glEnable(GL_DEPTH_TEST)) : (glDisable(GL_DEPTH_TEST));
}

/******************************************************************************
@brief  Zバッファ書込ONOFF設定
@param  isZEnable   Zバッファ書込有効無効フラグ
******************************************************************************/

void OpenGL::Renderer::SetZWriteEnable(bool isZEnable)
{
    (isZEnable) ? (glDepthMask(TRUE)) : (glDepthMask(FALSE));
}

/******************************************************************************
@brief  αテストONOFF設定
@param  isAlphaEnable   αテスト有効無効フラグ
******************************************************************************/

void OpenGL::Renderer::SetAlphaTestEnable(bool isAlphaEnable)
{
    if (isAlphaEnable)
    {
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GEQUAL, 0.5f);
    }
    else
    {
        glDisable(GL_ALPHA_TEST);
        glAlphaFunc(GL_ALWAYS, 0.8f);
    }
}

/******************************************************************************
@brief  サンプラーステート設定
@param  ssType      サンプラーステートタイプ
@param  ta          テクスチャアドレスタイプ
******************************************************************************/

void OpenGL::Renderer::SetSamplerState(SamplerStateType ssType, TextureAddress ta)
{
    unsigned short samplerState = GL_TEXTURE_WRAP_S, TextureAddress = GL_REPEAT;

    switch (ssType)
    {
    case SAMP_ADDRESSU      : samplerState = GL_TEXTURE_WRAP_S;     break;
    case SAMP_ADDRESSV      : samplerState = GL_TEXTURE_WRAP_T;     break;
    //case SAMP_ADDRESSW      :                                       break;
    //case SAMP_BORDERCOLOR   :                                       break;
    //case SAMP_MAGFILTER     : samplerState = GL_TEXTURE_MAG_FILTER; break;
    //case SAMP_MINFILTER     : samplerState = GL_TEXTURE_MIN_FILTER; break;
    //case SAMP_MIPFILTER     :                                       break;
    //case SAMP_MIPMAPLODBIAS :                                       break;
    //case SAMP_MAXMIPLEVEL   :                                       break;
    //case SAMP_MAXANISOTROPY :                                       break;
    //case SAMP_SRGBTEXTURE   :                                       break;
    //case SAMP_ELEMENTINDEX  :                                       break;
    //case SAMP_DMAPOFFSET    :                                       break;
    default                 : samplerState = GL_TEXTURE_WRAP_S;     break;
    }

    switch (TextureAddress)
    {
    case TADDRESS_WRAP      : TextureAddress = GL_REPEAT;   break;
    //case TADDRESS_MIRROR    :                               break;
    case TADDRESS_CLAMP     : TextureAddress = GL_CLAMP;    break;
    //case TADDRESS_BORDER    :                               break;
    //case TADDRESS_MIRRORONCE:                               break;
    default                 : TextureAddress = GL_REPEAT;   break;
    }

    glTexParameteri(GL_TEXTURE_2D, samplerState, TextureAddress);
}

/******************************************************************************
@brief  頂点カラーONOFF設定
@param  isEnable    頂点カラー有効無効フラグ
******************************************************************************/

void OpenGL::Renderer::SetVertexColorEnable(bool isEnable)
{
    if (isEnable)
    {
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    }
    else
    {
        glDisable(GL_COLOR_MATERIAL);
    }
}

/******************************************************************************
@brief  テクスチャONOFF設定
@param  isEnable    テクスチャ有効無効フラグ
******************************************************************************/

void OpenGL::Renderer::SetTextureEnable(bool isEnable)
{
    (isEnable) ? (glEnable(GL_TEXTURE_2D)) : (glDisable(GL_TEXTURE_2D));
}

/******************************************************************************
@brief  ワイヤーフレームONOFF設定
@param  isEnable    ワイヤーフレーム有効無効フラグ
******************************************************************************/

void OpenGL::Renderer::SetWireFrameEnable(bool isEnable)
{
    (isEnable) ? (glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)) : ( glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
}

/******************************************************************************
@brief  カリングONOFF設定
@param  isEnable    カリング有効無効フラグ
******************************************************************************/

void OpenGL::Renderer::SetCullingEnable(bool isEnable)
{
    (isEnable) ?
        (glEnable(GL_CULL_FACE)) :
        (glDisable(GL_CULL_FACE));
}

/******************************************************************************
@brief  頂点バッファ生成
@param  vertexNum       頂点数
@return VertexBuffer*   生成された頂点バッファ
******************************************************************************/

Framework::VertexBuffer* OpenGL::Renderer::CreateVertexBuffer(int vertexNum)
{
    OpenGL::VertexBuffer* pVertexBuffer = new OpenGL::VertexBuffer;

    glGenBuffers(1, &pVertexBuffer->vrtVBO);
    glBindBuffer(GL_ARRAY_BUFFER, pVertexBuffer->vrtVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertexNum, NULL, GL_DYNAMIC_DRAW);
    pVertexBuffer->vertexNum = vertexNum;

    return pVertexBuffer;
}

/******************************************************************************
@brief  インデックスバッファ生成
@param  indexNum        インデックス数
@return IndexBuffer*    生成されたインデックスバッファ
******************************************************************************/

Framework::IndexBuffer* OpenGL::Renderer::CreateIndexBuffer(int indexNum)
{
    OpenGL::IndexBuffer* pIndexBuffer = new OpenGL::IndexBuffer;

    glGenBuffers(1, &pIndexBuffer->idxVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pIndexBuffer->idxVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*indexNum, NULL, GL_STATIC_DRAW);
    pIndexBuffer->indexNum = indexNum;

    return pIndexBuffer;
}

/******************************************************************************
@brief  プリミティブ描画(そのまま)
@param  PriType     描画方法
@param  pVertex     頂点情報へのポインタ
@param  vtxNum      頂点数
******************************************************************************/

void OpenGL::Renderer::DrawPrimitiveUP(
    PrimitiveType PriType,
    const Framework::Vertex *pVertex, int PriNum)
{
    glViewport(pCamera->vp.X, pCamera->vp.Y, pCamera->vp.width, pCamera->vp.height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMultMatrixf(&ProjectionMatrix._11);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMultMatrixf(&ViewMatrix._11);
    
    Lighting();
    glMultMatrixf(&WorldMatrix._11);

    // 頂点配列を有効化
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &pVertex[0].pos);
    glNormalPointer(GL_FLOAT, sizeof(Vertex), &pVertex[0].nor);
    glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &pVertex[0].tex);
    glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex), &pVertex[0].col);

    switch (PriType)
    {
    case PRIMITIVE_TYPE_LINE_STRIP:
        glDrawArrays(GL_LINE_STRIP, 0, PriNum + 1);
        break;

    case PRIMITIVE_TYPE_TRIANGLE_LIST:
        glDrawArrays(GL_TRIANGLES, 0, PriNum*3);
        break;

    case PRIMITIVE_TYPE_TRIANGLE_STRIP:
        glDrawArrays(GL_TRIANGLE_STRIP, 0, PriNum + 2);
        break;
    }

    // 頂点配列を無効化
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

/******************************************************************************
@brief  インデックス付きプリミティブ描画(そのまま)
@param  PriType             描画方法
@param  StartIndex          描画する最初のインデックス
@param  vertexNum           全体の頂点数
@param  pIndex              インデックス情報
@param  pVertex             頂点情報
@param  Count               描画する超点数
******************************************************************************/

void OpenGL::Renderer::DrawIndexedPrimitiveUP(
    Framework::Renderer::PrimitiveType PriType,
    unsigned int StartIndex,
    unsigned int vertexNum,
    const int *pIndex,
    const Framework::Vertex *pVertex,
    unsigned int Count)
{
    glViewport(pCamera->vp.X, pCamera->vp.Y, pCamera->vp.width, pCamera->vp.height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMultMatrixf(&ProjectionMatrix._11);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMultMatrixf(&ViewMatrix._11);

    Lighting();
    glMultMatrixf(&WorldMatrix._11);

    // 頂点配列を有効化
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &pVertex[0].pos);
    glNormalPointer(GL_FLOAT, sizeof(Vertex), &pVertex[0].nor);
    glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &pVertex[0].tex);
    glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex), &pVertex[0].col);

    switch (PriType)
    {
    case PRIMITIVE_TYPE_TRIANGLE_LIST:
        glDrawElements(GL_TRIANGLES, Count * 3, GL_UNSIGNED_INT, &pIndex[StartIndex]);
        break;
        
    case PRIMITIVE_TYPE_TRIANGLE_STRIP:
        glDrawElements(GL_TRIANGLE_STRIP, Count + 2, GL_UNSIGNED_INT, &pIndex[StartIndex]);
        break;

    }

    // 頂点配列を無効化
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

/******************************************************************************
@brief  プリミティブ描画(頂点バッファ)
@param  PriType     描画方法
******************************************************************************/

void OpenGL::Renderer::DrawPrimitive(
    Framework::Renderer::PrimitiveType PriType)
{
    glViewport(pCamera->vp.X, pCamera->vp.Y, pCamera->vp.width, pCamera->vp.height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMultMatrixf(&ProjectionMatrix._11);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMultMatrixf(&ViewMatrix._11);

    Lighting();
    glMultMatrixf(&WorldMatrix._11);

    // 頂点配列を有効化
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    VertexBuffer* pVtxBuf = (VertexBuffer*)pVertexBuffer;
    glBindBuffer(GL_ARRAY_BUFFER, pVtxBuf->vrtVBO);

    // オフセットを設定
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));
    glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(sizeof(Vector3)));
    glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex), BUFFER_OFFSET(sizeof(Vector3)*2));
    glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(sizeof(Vector3)*2 + sizeof(Color)));

    switch (PriType)
    {
    case PRIMITIVE_TYPE_LINE_STRIP:
        glDrawArrays(GL_LINE_STRIP, 0, pVtxBuf->vertexNum);
        break;

    case PRIMITIVE_TYPE_TRIANGLE_LIST:
        glDrawArrays(GL_TRIANGLES, 0, pVtxBuf->vertexNum);
        break;

    case PRIMITIVE_TYPE_TRIANGLE_STRIP:
        glDrawArrays(GL_TRIANGLE_STRIP, 0, pVtxBuf->vertexNum);
        break;
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // 頂点配列を無効化
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

/******************************************************************************
@brief  インデックス付きプリミティブ描画(頂点バッファ)
@param  PriType         描画方法
@param  StartIndex      開始インデックス
@param  Count
******************************************************************************/

void OpenGL::Renderer::DrawIndexedPrimitive(
    Framework::Renderer::PrimitiveType PriType,
    int StartIndex,
    int Count)
{
    glViewport(pCamera->vp.X, pCamera->vp.Y, pCamera->vp.width, pCamera->vp.height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMultMatrixf(&ProjectionMatrix._11);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMultMatrixf(&ViewMatrix._11);

    Lighting();
    glMultMatrixf(&WorldMatrix._11);

    // 頂点配列を有効化
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    VertexBuffer* pVtxBuf = (VertexBuffer*)pVertexBuffer;
    IndexBuffer* pidxBuf = (IndexBuffer*)pIndexBuffer;
    glBindBuffer(GL_ARRAY_BUFFER, pVtxBuf->vrtVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pidxBuf->idxVBO);

    // オフセットを設定
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));
    glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(sizeof(Vector3)));
    glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex), BUFFER_OFFSET(sizeof(Vector3) * 2));
    glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(sizeof(Vector3) * 2 + sizeof(Color)));

    switch (PriType)
    {
    case PRIMITIVE_TYPE_TRIANGLE_LIST:
        glDrawElements(GL_TRIANGLES, Count * 3, GL_UNSIGNED_INT, BUFFER_OFFSET(sizeof(int)*StartIndex));
        break;

    case PRIMITIVE_TYPE_TRIANGLE_STRIP:
        glDrawElements(GL_TRIANGLE_STRIP, Count + 2, GL_UNSIGNED_INT, BUFFER_OFFSET(sizeof(int)*StartIndex));
        break;

    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // 頂点配列を無効化
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

/******************************* 実装ここまで ********************************/
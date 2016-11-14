/*****************************************************************************/
/*!
@file   DirectXRenderer.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "DirectXRenderer.h"
#include "../Framework/Error.h"
#include "DirectXVertexBuffer.h"
#include "DirectXIndexBuffer.h"


using DirectX::Renderer;
using namespace Framework;
using namespace Windows;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/

DirectX::Renderer::Renderer()
{
    type = DIRECTX9;
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

DirectX::Renderer::~Renderer()
{
}

/******************************************************************************
@brief  初期化処理
@param  pGameWindow     ウインドウ情報
******************************************************************************/

void DirectX::Renderer::Init(GameWindow *pGameWindow)
{
    /*
    * デバイス初期化
    */

    HWND hWnd = pGameWindow->GetHandle();
    HRESULT hr;

    // Direct3Dオブジェクトの生成
    if ((pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
    {
        Error::Message("Direct3Dオブジェクトの生成に失敗しました");
        return;
    }

    // 現在のディスプレイモードを取得
    // ERR : D3DERR_INVALIDCALL
    D3DDISPLAYMODE d3ddm;
    if (FAILED(hr = pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
    {
        Error::Message("現在のディスプレイモードの取得に失敗しました");
        return;
    }

    // パラメータを初期化
    D3DPRESENT_PARAMETERS d3dpp; 
    ZeroMemory(&d3dpp, sizeof(d3dpp));

    // パラメータ設定
    d3dpp.BackBufferWidth           = pGameWindow->GetWidth();      // 画面の幅
    d3dpp.BackBufferHeight          = pGameWindow->GetHeight();     // 画面の高さ
    d3dpp.BackBufferFormat          = d3ddm.Format;                 // バックバッファのフォーマット
    d3dpp.BackBufferCount           = 1;                            // バックバッファの数
    d3dpp.SwapEffect                = D3DSWAPEFFECT_DISCARD;        // バッファの切替方法
    d3dpp.EnableAutoDepthStencil    = TRUE;                         // デプスバッファとステンシルバッファの生成
    d3dpp.AutoDepthStencilFormat    = D3DFMT_D24S8;                 // デプスバッファとして24ビット使用
    d3dpp.Windowed                  = !pGameWindow->IsFullScreen(); // ウインドウスクリーン

    if (pGameWindow->IsFullScreen())
    {// フルスクリーンモード
        d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;                   // バックバッファ
        d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; // リフレッシュレート
        d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; // インターバル
    }
    else
    {// ウィンドウモード
        d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;                    // バックバッファ
        d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; // リフレッシュレート
        d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; // インターバル
    }

    // Direct3Dデバイスの生成
    // ディスプレイアダプタを表すためのデバイスを作成
    // 描画と頂点処理をハードウェアで行なう
    if (FAILED(hr = pD3D->CreateDevice(D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        hWnd,
        D3DCREATE_HARDWARE_VERTEXPROCESSING,
        &d3dpp, &pD3DDev)))
    {
        // 上記の設定が失敗したら
        // 描画をハードウェアで行い、頂点処理はCPUで行なう
        if (FAILED(hr = pD3D->CreateDevice(D3DADAPTER_DEFAULT,
            D3DDEVTYPE_HAL,
            hWnd,
            D3DCREATE_SOFTWARE_VERTEXPROCESSING,
            &d3dpp, &pD3DDev)))
        {
            // 上記の設定が失敗したら
            // 描画と頂点処理をCPUで行なう
            if (FAILED(hr = pD3D->CreateDevice(D3DADAPTER_DEFAULT,
                D3DDEVTYPE_REF,
                hWnd,
                D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                &d3dpp, &pD3DDev)))
            {
                // 初期化失敗
                Error::Message("DirectXのデバイスの生成に失敗しました");
                return;
            }
        }
    }

    // レンダリングステートパラメータの設定
    pD3DDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);                // 裏面をカリング
    pD3DDev->SetRenderState(D3DRS_ZENABLE, TRUE);                        // Zバッファを使用
    pD3DDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);                   // Zバッファに書込を許可
    pD3DDev->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);              // Zテストの条件を設定
    pD3DDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);               // αブレンドを行う
    pD3DDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);          // αソースカラーの指定
    pD3DDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);      // αデスティネーションカラーの指定
    pD3DDev->SetRenderState(D3DRS_LIGHTING, TRUE);                       // ライティングをオン

    pD3DDev->SetRenderState(D3DRS_ALPHAREF, 0x00000001);                 // αテストの比較値を1に設定
    pD3DDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);                // αテスト有効化 
    pD3DDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);       // αテストの条件を「以上」に設定

    // サンプラーステートパラメータの設定
    pD3DDev->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);     // テクスチャU座標はリピート
    pD3DDev->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);     // テクスチャV座標はリピート
    pD3DDev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);      // 縮小時双線形補間
    pD3DDev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);      // 拡大時双線形補間

    // テクスチャステージステートパラメータの設定
    pD3DDev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);   // アルファブレンディング処理
    pD3DDev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);   // 最初のアルファ引数
    pD3DDev->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);   // ２番目のアルファ引数

}

/******************************************************************************
@brief  終了処理
******************************************************************************/

void DirectX::Renderer::Uninit()
{

    // Direct3Dデバイスの開放
    if (pD3DDev != NULL)
    {
        pD3DDev->Release();
        pD3DDev = NULL;
    }

    // Direct3Dオブジェクトの開放
    if (pD3D != NULL)
    {
        pD3D->Release();
        pD3D = NULL;
    }

}

/******************************************************************************
@brief  画面クリア
******************************************************************************/

void DirectX::Renderer::Clear()
{

    pD3DDev->Clear
        (0,
        NULL,
        (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL),
        D3DCOLOR_XRGB(0, 0, 0),
        1.0f,
        0);

    pD3DDev->BeginScene();
}

/******************************************************************************
@brief  バックバッファ表示
******************************************************************************/

void DirectX::Renderer::Flip()
{
    pD3DDev->EndScene();
    pD3DDev->Present(NULL, NULL, NULL, NULL);
}

/******************************************************************************
@brief  ライト設定
@param  index                   インデックス
@param  Framework::pLight       ライト情報
******************************************************************************/

void DirectX::Renderer::SetLight(int index, Framework::Light *pLight)
{
    D3DLIGHT9 light;
    ZeroMemory(&light, sizeof(D3DLIGHT9));
    switch (pLight->type)
    {
    case Light::POINT       :   light.Type = D3DLIGHT_POINT;        break;
    case Light::DIRECTIONAL :   light.Type = D3DLIGHT_DIRECTIONAL;  break;
    case Light::SPOT        :   light.Type = D3DLIGHT_SPOT;         break;
    }
    light.Diffuse = D3DXCOLOR(pLight->diffuse.r, pLight->diffuse.g, pLight->diffuse.b, pLight->diffuse.a);
    light.Ambient = D3DXCOLOR(pLight->ambient.r, pLight->ambient.g, pLight->ambient.b, pLight->ambient.a);
    D3DXVECTOR3 vecDir = D3DXVECTOR3(pLight->direction.x, pLight->direction.y, pLight->direction.z);
    D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);
    pD3DDev->SetLight(index, &light);

}

/******************************************************************************
@brief  ライト設定
@param  index       インデックス
@param  isLight     ライトがONかOFFかどうか
******************************************************************************/

void DirectX::Renderer::SetLight(int index, bool isLight)
{
    (isLight) ? (pD3DDev->LightEnable(index, TRUE)) : (pD3DDev->LightEnable(index, FALSE));
}

/******************************************************************************
@brief  ライトのONOFF設定
@param  isLight     ライトがONかOFFかどうか
******************************************************************************/

void DirectX::Renderer::SetLightEnable(bool isLight)
{
    (isLight) ? (pD3DDev->SetRenderState(D3DRS_LIGHTING, TRUE)) : (pD3DDev->SetRenderState(D3DRS_LIGHTING, FALSE));
}

/******************************************************************************
@brief  テクスチャ登録
@param  pTexture                登録するテクスチャ
******************************************************************************/

void DirectX::Renderer::SetTexture(Framework::Texture *pTexture)
{
    pTex = (DirectX::Texture*)pTexture;
    // テクスチャ設定
    if (pTex != NULL)
        pD3DDev->SetTexture(0, pTex->GetResource());
    else
        pD3DDev->SetTexture(0, NULL);
}

/******************************************************************************
@brief  マテリアル設定
@param  pMaterial   マテリアル
******************************************************************************/

void DirectX::Renderer::SetMaterial(Framework::Material *pMaterial)
{
    D3DMATERIAL9 material;

    if (pMaterial)
    {
        material.Diffuse.r = pMaterial->diffuse.r;
        material.Diffuse.g = pMaterial->diffuse.g;
        material.Diffuse.b = pMaterial->diffuse.b;
        material.Diffuse.a = pMaterial->diffuse.a;

        material.Ambient.r = pMaterial->ambient.r;
        material.Ambient.g = pMaterial->ambient.g;
        material.Ambient.b = pMaterial->ambient.b;
        material.Ambient.a = pMaterial->ambient.a;

        material.Specular.r = pMaterial->specular.r;
        material.Specular.g = pMaterial->specular.g;
        material.Specular.b = pMaterial->specular.b;
        material.Specular.a = pMaterial->specular.a;

        material.Emissive.r = pMaterial->emissive.r;
        material.Emissive.g = pMaterial->emissive.g;
        material.Emissive.b = pMaterial->emissive.b;
        material.Emissive.a = pMaterial->emissive.a;

        material.Power = pMaterial->power;
    }
    else
    {
        // 標準マテリアル設定
        material.Diffuse.r = 1.0f;
        material.Diffuse.g = 1.0f;
        material.Diffuse.b = 1.0f;
        material.Diffuse.a = 1.0f;

        material.Ambient.r = 0.8f;
        material.Ambient.g = 0.8f;
        material.Ambient.b = 0.8f;
        material.Ambient.a = 1.0f;

        material.Specular.r = 0.0f;
        material.Specular.g = 0.0f;
        material.Specular.b = 0.0f;
        material.Specular.a = 0.0f;

        material.Emissive.r = 0.0f;
        material.Emissive.g = 0.0f;
        material.Emissive.b = 0.0f;
        material.Emissive.a = 0.0f;

        material.Power = 0.0f;
    }

    pD3DDev->SetMaterial(&material);

}

/******************************************************************************
@brief  ブレンドモード設定
@param  SrcBlend    ソースブレンド
@param  DestBlend   ディストブレンド
******************************************************************************/

void DirectX::Renderer::SetBlend(Blend SrcBlend, Blend DestBlend)
{

    _D3DBLEND srcBlend, destBlend;

    switch (SrcBlend)
    {
    case BLEND_ZERO         : srcBlend = D3DBLEND_ZERO;         break;
    case BLEND_ONE          : srcBlend = D3DBLEND_ONE;          break;
    case BLEND_SRC_COLOR    : srcBlend = D3DBLEND_SRCCOLOR;     break;
    case BLEND_SRC_INVCOLOR : srcBlend = D3DBLEND_INVSRCCOLOR;  break;
    case BLEND_SRC_ALPHA    : srcBlend = D3DBLEND_SRCALPHA;     break;
    case BLEND_SRC_INVALPHA : srcBlend = D3DBLEND_INVSRCALPHA;  break;

    case BLEND_DEST_COLOR   : srcBlend = D3DBLEND_DESTCOLOR;    break;
    case BLEND_DEST_INVCOLOR: srcBlend = D3DBLEND_INVDESTCOLOR; break;
    case BLEND_DEST_ALPHA   : srcBlend = D3DBLEND_DESTALPHA;    break;
    case BLEND_DEST_INVALPHA: srcBlend = D3DBLEND_INVDESTALPHA; break;
    }

    switch (DestBlend)
    {
    case BLEND_ZERO         : destBlend = D3DBLEND_ZERO;         break;
    case BLEND_ONE          : destBlend = D3DBLEND_ONE;          break;
    case BLEND_SRC_COLOR    : destBlend = D3DBLEND_SRCCOLOR;     break;
    case BLEND_SRC_INVCOLOR : destBlend = D3DBLEND_INVSRCCOLOR;  break;
    case BLEND_SRC_ALPHA    : destBlend = D3DBLEND_SRCALPHA;     break;
    case BLEND_SRC_INVALPHA : destBlend = D3DBLEND_INVSRCALPHA;  break;

    case BLEND_DEST_COLOR   : destBlend = D3DBLEND_DESTCOLOR;    break;
    case BLEND_DEST_INVCOLOR: destBlend = D3DBLEND_INVDESTCOLOR; break;
    case BLEND_DEST_ALPHA   : destBlend = D3DBLEND_DESTALPHA;    break;
    case BLEND_DEST_INVALPHA: destBlend = D3DBLEND_INVDESTALPHA; break;
    }

    pD3DDev->SetRenderState(D3DRS_SRCBLEND, srcBlend);
    pD3DDev->SetRenderState(D3DRS_DESTBLEND, destBlend);

}

/******************************************************************************
@brief  ZテストONOFF設定
@param  isZEnable   Zテスト有効無効フラグ
******************************************************************************/

void DirectX::Renderer::SetZTestEnable(bool isZEnable)
{
    (isZEnable) ?
        (pD3DDev->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL)) :
        (pD3DDev->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS));
}

/******************************************************************************
@brief  Zバッファ書込ONOFF設定
@param  isZEnable   Zバッファ書込有効無効フラグ
******************************************************************************/

void DirectX::Renderer::SetZWriteEnable(bool isZEnable)
{
    (isZEnable) ?
        (pD3DDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE)) :
        (pD3DDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE));
}

/******************************************************************************
@brief  αテストONOFF設定
@param  isAlphaEnable   αテスト有効無効フラグ
******************************************************************************/

void DirectX::Renderer::SetAlphaTestEnable(bool isAlphaEnable)
{
    if (isAlphaEnable)
    {
        pD3DDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
        pD3DDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
        pD3DDev->SetRenderState(D3DRS_ALPHAREF, 0x88);
    }
    else
    {
        pD3DDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
        pD3DDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
    }
}

/******************************************************************************
@brief  サンプラーステート設定
@param  ssType      サンプラーステートタイプ
@param  ta          テクスチャアドレスタイプ
******************************************************************************/

void DirectX::Renderer::SetSamplerState(SamplerStateType ssType, TextureAddress ta)
{
    pD3DDev->SetSamplerState(0, (D3DSAMPLERSTATETYPE)ssType, (D3DSAMPLERSTATETYPE)ta);
}

/******************************************************************************
@brief  頂点カラーONOFF設定
@param  isEnable    頂点カラー有効無効フラグ
******************************************************************************/

void DirectX::Renderer::SetVertexColorEnable(bool isEnable)
{
    if (isEnable)
    {
        pD3DDev->SetRenderState(D3DRS_COLORVERTEX, TRUE);
        pD3DDev->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
        pD3DDev->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);
        pD3DDev->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_COLOR1);
        pD3DDev->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_COLOR1);
    }
    else
    {
        pD3DDev->SetRenderState(D3DRS_COLORVERTEX, FALSE);
        pD3DDev->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
        pD3DDev->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
        pD3DDev->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);
        pD3DDev->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);
    }
}

/******************************************************************************
@brief  テクスチャONOFF設定
@param  isEnable    テクスチャ有効無効フラグ
******************************************************************************/

void DirectX::Renderer::SetTextureEnable(bool isEnable)
{
    (isEnable) ?
        (pD3DDev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE)) :
        (pD3DDev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_DISABLE));
}

/******************************************************************************
@brief  ワイヤーフレームONOFF設定
@param  isEnable    ワイヤーフレーム有効無効フラグ
******************************************************************************/

void DirectX::Renderer::SetWireFrameEnable(bool isEnable)
{
    (isEnable) ? 
        (pD3DDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME)) :
        (pD3DDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID)) ;
}

/******************************************************************************
@brief  カリングONOFF設定
@param  isEnable    カリング有効無効フラグ
******************************************************************************/

void DirectX::Renderer::SetCullingEnable(bool isEnable)
{
    (isEnable) ?
        (pD3DDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW)) :
        (pD3DDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE));
}

/******************************************************************************
@brief  頂点バッファ生成
@param  vertexNum       頂点数
@return VertexBuffer*   生成された頂点バッファ
******************************************************************************/

Framework::VertexBuffer* DirectX::Renderer::CreateVertexBuffer(int vertexNum)
{
    VertexBuffer* pVertexBuffer = new VertexBuffer;

    pD3DDev->CreateVertexBuffer(sizeof(VERTEX_3D) * vertexNum,  // 頂点データ用に確保するバッファサイズ(バイト単位)
        D3DUSAGE_WRITEONLY,                                     // 頂点バッファの使用法　
        FVF_VERTEX_3D,                                          // 使用する頂点フォーマット
        D3DPOOL_MANAGED,                                        // リソースのバッファを保持するメモリクラスを指定
        &pVertexBuffer->pVertexBuffer,                          // 頂点バッファインターフェースへのポインタ
        NULL);

    pVertexBuffer->vertexNum = vertexNum;
    return pVertexBuffer;
}

/******************************************************************************
@brief  インデックスバッファ生成
@param  indexNum        インデックス数
@return IndexBuffer*    生成されたインデックスバッファ
******************************************************************************/

Framework::IndexBuffer* DirectX::Renderer::CreateIndexBuffer(int indexNum)
{
    IndexBuffer* pIndexBuffer = new IndexBuffer;

    pD3DDev->CreateIndexBuffer(sizeof(int) * indexNum,  // インデックスデータ用に確保するバッファサイズ(バイト単位)
        D3DUSAGE_WRITEONLY,                             // インデックスバッファの使用法　
        D3DFMT_INDEX32,                                 // 使用するインデックスフォーマット
        D3DPOOL_MANAGED,                                // リソースのバッファを保持するメモリクラスを指定
        &pIndexBuffer->pIndexBuffer,                    // インデックスバッファインターフェースへのポインタ
        NULL);

    pIndexBuffer->indexNum = indexNum;
    return pIndexBuffer;
}

/******************************************************************************
@brief  プリミティブ描画(そのまま)
@param  PriType     描画方法
@param  pVertex     頂点情報へのポインタ
@param  vtxNum      頂点数
******************************************************************************/

void DirectX::Renderer::DrawPrimitiveUP(
    Framework::Renderer::PrimitiveType PriType,
    const Framework::Vertex *pVertex, int PriNum)
{
    // ビューポートの設定
    pD3DDev->SetViewport((D3DVIEWPORT9*)&pCamera->vp);
    // プロジェクションマトリックスの設定
    pD3DDev->SetTransform(D3DTS_PROJECTION, (D3DXMATRIX*)&ProjectionMatrix);
    // ビューマトリックスの設定
    pD3DDev->SetTransform(D3DTS_VIEW, (D3DXMATRIX*)&ViewMatrix);
    // ワールドマトリックスの設定
    pD3DDev->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)&WorldMatrix);

    // ポリゴン描画
    pD3DDev->SetFVF(FVF_VERTEX_3D);
    switch (PriType)
    {
    case PRIMITIVE_TYPE_LINE_STRIP:
        pD3DDev->DrawPrimitiveUP(D3DPT_LINESTRIP, PriNum, pVertex, sizeof(Vertex));
        break;
    case PRIMITIVE_TYPE_TRIANGLE_STRIP:
        pD3DDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, PriNum, pVertex, sizeof(Vertex));
        break;
    }
}

/******************************************************************************
@brief  インデックス付きプリミティブ描画(そのまま)
@param  PriType             描画方法
@param  BaseVertexIndex     
@param  MinIndex            
@param  NumVertices         
@param  StartIndex          
@param  pVertex             頂点情報へのポインタ
@param  vtxNum              頂点数
******************************************************************************/

void DirectX::Renderer::DrawIndexedPrimitiveUP(
    Framework::Renderer::PrimitiveType PriType,
    unsigned int StartIndex,
    unsigned int VertexNum,
    const int *pIndex,
    const Framework::Vertex *pVertex,
    unsigned int Count)
{
    // ビューポートの設定
    pD3DDev->SetViewport((D3DVIEWPORT9*)&pCamera->vp);
    // プロジェクションマトリックスの設定
    pD3DDev->SetTransform(D3DTS_PROJECTION, (D3DXMATRIX*)&ProjectionMatrix);
    // ビューマトリックスの設定
    pD3DDev->SetTransform(D3DTS_VIEW, (D3DXMATRIX*)&ViewMatrix);
    // ワールドマトリックスの設定
    pD3DDev->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)&WorldMatrix);

    // ポリゴン描画
    pD3DDev->SetFVF(FVF_VERTEX_3D);
    switch (PriType)
    {
    case PRIMITIVE_TYPE_TRIANGLE_STRIP:
        pD3DDev->DrawIndexedPrimitiveUP(D3DPT_TRIANGLESTRIP, 0, VertexNum, Count - StartIndex - 2, &pIndex[StartIndex], D3DFMT_INDEX32, pVertex, sizeof(Vertex));
        break;

    case PRIMITIVE_TYPE_TRIANGLE_LIST:
        pD3DDev->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, VertexNum, Count, &pIndex[StartIndex], D3DFMT_INDEX32, pVertex, sizeof(Vertex));
        break;
    }
}

/******************************************************************************
@brief  プリミティブ描画(頂点バッファ)
@param  PriType     描画方法
******************************************************************************/

void DirectX::Renderer::DrawPrimitive(
    Framework::Renderer::PrimitiveType PriType)
{
    // ビューポートの設定
    pD3DDev->SetViewport((D3DVIEWPORT9*)&pCamera->vp);
    // プロジェクションマトリックスの設定
    pD3DDev->SetTransform(D3DTS_PROJECTION, (D3DXMATRIX*)&ProjectionMatrix);
    // ビューマトリックスの設定
    pD3DDev->SetTransform(D3DTS_VIEW, (D3DXMATRIX*)&ViewMatrix);
    // ワールドマトリックスの設定
    pD3DDev->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)&WorldMatrix);

    // ポリゴン描画
    VertexBuffer* pVtxBuf = (VertexBuffer*)pVertexBuffer;
    pD3DDev->SetStreamSource(0, pVtxBuf->pVertexBuffer, 0, sizeof(VERTEX_3D));
    pD3DDev->SetFVF(FVF_VERTEX_3D);
    switch (PriType)
    {
    case PRIMITIVE_TYPE_LINE_STRIP:
        pD3DDev->DrawPrimitive(D3DPT_LINESTRIP, 0, pVtxBuf->vertexNum-1);
        break;
    case PRIMITIVE_TYPE_TRIANGLE_STRIP:
        pD3DDev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, pVtxBuf->vertexNum-2);
        break;
    case PRIMITIVE_TYPE_TRIANGLE_LIST:
        pD3DDev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, pVtxBuf->vertexNum/3);
        break;
    }

}

/******************************************************************************
@brief  インデックス付きプリミティブ描画(頂点バッファ)
@param  PriType         描画方法
@param  StartIndex      開始インデックス
@param  Count           
******************************************************************************/

void DirectX::Renderer::DrawIndexedPrimitive(
    Framework::Renderer::PrimitiveType PriType,
    int StartIndex,
    int Count)
{
    // ビューポートの設定
    pD3DDev->SetViewport((D3DVIEWPORT9*)&pCamera->vp);
    // プロジェクションマトリックスの設定
    pD3DDev->SetTransform(D3DTS_PROJECTION, (D3DXMATRIX*)&ProjectionMatrix);
    // ビューマトリックスの設定
    pD3DDev->SetTransform(D3DTS_VIEW, (D3DXMATRIX*)&ViewMatrix);
    // ワールドマトリックスの設定
    pD3DDev->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)&WorldMatrix);

    // ポリゴン描画
    VertexBuffer* pVtxBuf = (VertexBuffer*)pVertexBuffer;
    IndexBuffer* pIdxBuf = (IndexBuffer*)pIndexBuffer;
    pD3DDev->SetStreamSource(0, pVtxBuf->pVertexBuffer, 0, sizeof(VERTEX_3D));
    pD3DDev->SetFVF(FVF_VERTEX_3D);
    pD3DDev->SetIndices(pIdxBuf->pIndexBuffer);
    switch (PriType)
    {
    case PRIMITIVE_TYPE_LINE_STRIP:
        pD3DDev->DrawIndexedPrimitive(D3DPT_LINESTRIP, 0, 0, pVtxBuf->vertexNum, StartIndex, Count);
        break;
    case PRIMITIVE_TYPE_TRIANGLE_STRIP:
        pD3DDev->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, pVtxBuf->vertexNum, StartIndex, Count);
        break;
    case PRIMITIVE_TYPE_TRIANGLE_LIST:
        pD3DDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, pVtxBuf->vertexNum, StartIndex, Count);
        break;
    }
}

/******************************* 実装ここまで ********************************/
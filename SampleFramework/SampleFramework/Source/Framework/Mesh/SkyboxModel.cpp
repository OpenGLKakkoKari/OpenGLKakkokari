/*****************************************************************************/
/*!
@file   SkyboxModel.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "SkyboxModel.h"
#include "..\Manager.h"


using namespace Framework;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/

SkyboxModel::SkyboxModel()
{
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

SkyboxModel::~SkyboxModel()
{
}

/******************************************************************************
@brief  描画処理
******************************************************************************/

void SkyboxModel::Draw()
{
    Matrix WorldMatrix;
    GetMatrix(&WorldMatrix);

    Manager::GetRenderer()->SetCullingEnable(false);
    Manager::GetRenderer()->SetVertexColorEnable(false);
    Manager::GetRenderer()->SetTranslationMode(true);
    Manager::GetRenderer()->SetLightEnable(false);
    Manager::GetRenderer()->SetWorldMatrix(&WorldMatrix);

    for (int i = 0; i < pMesh->subsetNum; i++)
    {
        Manager::GetRenderer()->SetTexture(pMesh->pMaterialList[pMesh->pSubsetList[i].materialIndex].pTexture);
        Manager::GetRenderer()->SetMaterial(NULL);

        Manager::GetRenderer()->SetVertexBuffer(pMesh->pVtxBuf);
        Manager::GetRenderer()->SetIndexBuffer(pMesh->pIdxBuf);
        Manager::GetRenderer()->DrawIndexedPrimitive(
            Renderer::PRIMITIVE_TYPE_TRIANGLE_LIST,
            pMesh->pSubsetList[i].startIndex,
            pMesh->pSubsetList[i].count
            );
    }

    Manager::GetRenderer()->SetVertexBuffer(NULL);
    Manager::GetRenderer()->SetIndexBuffer(NULL);
    Manager::GetRenderer()->SetMaterial(NULL);
    Manager::GetRenderer()->SetTexture(NULL);
    Manager::GetRenderer()->SetVertexColorEnable(true);
    Manager::GetRenderer()->SetCullingEnable(true);
    Manager::GetRenderer()->SetLightEnable(true);
}

/******************************************************************************
@brief  箱型モデル生成処理
@param  scale           テクスチャのファイル名
@param  FileName        テクスチャのファイル名
@return Model*          モデル情報へのポインタ
******************************************************************************/

SkyboxModel* SkyboxModel::CreateSkybox(const Vector3& scale)
{
    SkyboxModel* model = new SkyboxModel;

    model->pMesh = Mesh::CreateBox(scale);

    const Vector2 uvList[24] =
    {
        Vector2(0.0000f, 0.3333f),
        Vector2(0.2500f, 0.3333f),
        Vector2(0.0000f, 0.6666f),
        Vector2(0.2500f, 0.6666f),

        Vector2(0.2500f, 1.0000f),
        Vector2(0.2500f, 0.6666f),
        Vector2(0.5000f, 1.0000f),
        Vector2(0.5000f, 0.6666f),

        Vector2(0.7500f, 0.6666f),
        Vector2(0.5000f, 0.6666f),
        Vector2(0.7500f, 0.3333f),
        Vector2(0.5000f, 0.3333f),

        Vector2(0.5000f, 0.0000f),
        Vector2(0.5000f, 0.3333f),
        Vector2(0.2500f, 0.0000f),
        Vector2(0.2500f, 0.3333f),

        Vector2(0.2500f, 0.3333f),
        Vector2(0.5000f, 0.3333f),
        Vector2(0.2500f, 0.6666f),
        Vector2(0.5000f, 0.6666f),

        Vector2(0.7500f, 0.3333f),
        Vector2(1.0000f, 0.3333f),
        Vector2(0.7500f, 0.6666f),
        Vector2(1.0000f, 0.6666f),
    };


    Vertex* pVtx = model->pMesh->pVtxBuf->Lock();
    for (int i = 0; i < (int)model->pMesh->vertexNum; i++)
    {
        pVtx->tex = uvList[i];
        pVtx++;
    }
    model->pMesh->pVtxBuf->Unlock();

    return model;
}

/******************************** 実装ここまで *******************************/

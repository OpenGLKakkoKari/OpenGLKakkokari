/*****************************************************************************/
/*!
@file   Model.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Model.h"
#include "..\Manager.h"


using namespace Framework;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/

Model::Model() : pMesh(NULL)
{
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

Model::~Model()
{
    pMesh->Release();
}

/******************************************************************************
@brief  モデル描画処理
******************************************************************************/

void Model::Draw()
{
    Matrix WorldMatrix;
    GetMatrix(&WorldMatrix);

    Manager::GetRenderer()->SetVertexColorEnable(false);
    Manager::GetRenderer()->SetTranslationMode(true);
    Manager::GetRenderer()->SetLightEnable(true);
    Manager::GetRenderer()->SetWorldMatrix(&WorldMatrix);

    for (int i = 0; i < pMesh->subsetNum; i++)
    {
        Manager::GetRenderer()->SetTexture(pMesh->pMaterialList[pMesh->pSubsetList[i].materialIndex].pTexture);
        Manager::GetRenderer()->SetMaterial(&pMesh->pMaterialList[pMesh->pSubsetList[i].materialIndex]);

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
}

/******************************************************************************
@brief  モデル生成処理
@param  FileName        テクスチャのファイル名
@return Model*          モデル情報へのポインタ
******************************************************************************/

Model* Model::Load(const char *FileName)
{
    Model* model = new Model;
    model->pMesh = Mesh::Load(FileName);
    return model;
}

/******************************************************************************
@brief  箱型モデル生成処理
@param  scale           テクスチャのファイル名
@param  FileName        テクスチャのファイル名
@return Model*          モデル情報へのポインタ
******************************************************************************/

Model* Model::CreateBox(const Vector3& scale)
{
    Model* model = new Model;

    model->pMesh = Mesh::CreateBox(scale);

    return model;
}

/******************************** 実装ここまで *******************************/

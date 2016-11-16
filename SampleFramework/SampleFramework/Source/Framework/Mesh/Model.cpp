/*****************************************************************************/
/*!
@file   Model.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Model.h"
#include "..\Manager.h"


using namespace Framework;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

Model::Model() : pMesh(NULL)
{
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

Model::~Model()
{
    pMesh->Release();
}

/******************************************************************************
@brief  ���f���`�揈��
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
@brief  ���f����������
@param  FileName        �e�N�X�`���̃t�@�C����
@return Model*          ���f�����ւ̃|�C���^
******************************************************************************/

Model* Model::Load(const char *FileName)
{
    Model* model = new Model;
    model->pMesh = Mesh::Load(FileName);
    return model;
}

/******************************************************************************
@brief  ���^���f����������
@param  scale           �e�N�X�`���̃t�@�C����
@param  FileName        �e�N�X�`���̃t�@�C����
@return Model*          ���f�����ւ̃|�C���^
******************************************************************************/

Model* Model::CreateBox(const Vector3& scale)
{
    Model* model = new Model;

    model->pMesh = Mesh::CreateBox(scale);

    return model;
}

/******************************** ���������܂� *******************************/

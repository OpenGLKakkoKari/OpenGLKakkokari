/*****************************************************************************/
/*!
@file   MeshField.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include <math.h>
#include "MeshField.h"
#include "../Game/GameScene.h"
#include "../Game/Character/Player.h"
#include "../Framework/Manager.h"
#include "../Framework/Math/Random.h"
#include "../Framework/Math/Math.h"


using namespace Game;
using namespace Framework;
using namespace Framework::Math;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
@param  widthDiv        ���̕�����
@param  heightDiv       �c�̕�����
******************************************************************************/

MeshField::MeshField(
    const char* fileName,
    int widthDiv,
    int heightDiv,
    const Vector2& size,
    float* pHeightMap)
{
    this->widthDiv = widthDiv;
    this->heightDiv = heightDiv;
    pMesh = new Mesh;

    // �C���f�b�N�X���Z�o
    // ��s�̃C���f�b�N�X�� �~ �s���̃C���f�b�N�X�� �{ �܂�Ԃ���
    indexNum = ((2 * widthDiv + 2) * heightDiv) + ((heightDiv - 1) * 2);

    // �|���S�����Z�o
    pMesh->faceNum = indexNum - 2;
    // ���_��
    pMesh->vertexNum = (widthDiv + 1) * (heightDiv + 1);

    // ���_���m��
    pMesh->pVertex = new Vertex[pMesh->vertexNum];

    // ���_���ҏW
    if (pHeightMap == NULL)
    {
        for (int vtxNum = 0; vtxNum < (int)pMesh->vertexNum; vtxNum++)
        {
            Random::Seed();
            pMesh->pVertex[vtxNum].pos = Vector3(
                (0.0f - (size.x / widthDiv) * widthDiv / 2) + (size.x / widthDiv) * (vtxNum % (widthDiv + 1)),
                0.0f,
                //Random::Generate<float>(0.0f,10.0f),
                (0.0f + (size.y / heightDiv) * heightDiv / 2) - (size.y / widthDiv) * (vtxNum / (widthDiv + 1)));
            pMesh->pVertex[vtxNum].col = Color(255, 255, 255, 255);
            pMesh->pVertex[vtxNum].nor = Vector3(0.0f, 1.0f, 0.0f);
            pMesh->pVertex[vtxNum].tex = Vector2(
                1.0f * (vtxNum % (widthDiv + 1)),
                1.0f * (vtxNum / (widthDiv + 1)));
        }
    }
    else
    {
        for (int vtxNum = 0; vtxNum < (int)pMesh->vertexNum; vtxNum++)
        {
            pMesh->pVertex[vtxNum].pos = Vector3(
                (0.0f - (size.x / widthDiv) * widthDiv / 2) + (size.x / widthDiv) * (vtxNum % (widthDiv + 1)),
                pHeightMap[vtxNum],
                (0.0f + (size.y / heightDiv) * heightDiv / 2) - (size.y / widthDiv) * (vtxNum / (widthDiv + 1)));
            pMesh->pVertex[vtxNum].col = Color(255, 255, 255, 255);
            pMesh->pVertex[vtxNum].nor = Vector3(0.0f, 1.0f, 0.0f);
            pMesh->pVertex[vtxNum].tex = Vector2(
                1.0f * (vtxNum % (widthDiv + 1)),
                1.0f * (vtxNum / (widthDiv + 1)));
        }
    }

    // �C���f�b�N�X���m��
    pMesh->pIndexList = new int[indexNum];

    // ���_���W�ݒ�
    int x = 0, y = 0;
    int idx = 0;
    while (idx < indexNum)
    {
        // �s�̏���
        while (idx < (y + 1) * (2 * widthDiv + 4) - 2)
        {
            if (idx % 2 == 0)
            {
                pMesh->pIndexList[idx] = (widthDiv + 1) * (y + 1) + x;
            }
            else
            {
                pMesh->pIndexList[idx] = (widthDiv + 1) * y + x;
                x++;
            }
            idx++;
        }
        // ���̍s�Ɉړ�
        y++;
        x = 0;
        idx += 2;
    }

    // ��ԍŏ��̐܂�Ԃ��܂ňړ�
    idx = 2 * widthDiv + 2;
    //�܂�Ԃ��̏���
    for (y = 0; y < heightDiv - 1; y++)
    {
        pMesh->pIndexList[idx] = pMesh->pIndexList[idx - 1];
        pMesh->pIndexList[idx + 1] = pMesh->pIndexList[idx + 2];
        // ���̍s�ɐi��
        idx += 2 * widthDiv + 4;
    }

    // �e�N�X�`���ǂݍ���
    pTexture = Texture::Load(fileName);

}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

MeshField::~MeshField()
{
    if (pTexture)
    {
        pTexture->Release();
        pTexture = NULL;
    }
}

/******************************************************************************
@brief  �`�揈��
******************************************************************************/

void MeshField::Draw(void)
{
    Matrix WorldMatrix;
    Matrix::GetCalcMatrix(&WorldMatrix, &scale_, &rot_, &pos_);

    Manager::GetRenderer()->SetTranslationMode(true);
    Manager::GetRenderer()->SetTexture(pTexture);
    Manager::GetRenderer()->SetMaterial(NULL);
    Manager::GetRenderer()->SetLightEnable(false);
    Manager::GetRenderer()->SetWorldMatrix(&WorldMatrix);

    Manager::GetRenderer()->DrawIndexedPrimitiveUP(
        Framework::Renderer::PrimitiveType::PRIMITIVE_TYPE_TRIANGLE_STRIP,
        0,
        pMesh->vertexNum,
        pMesh->pIndexList,
        pMesh->pVertex,
        indexNum-2
        );
}

/******************************** ���������܂� *******************************/

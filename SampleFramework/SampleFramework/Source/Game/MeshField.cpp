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
        for (int vtxNum = 0; vtxNum < pMesh->vertexNum; vtxNum++)
        {
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
        Random::Seed();
        for (int vtxNum = 0; vtxNum < pMesh->vertexNum; vtxNum++)
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
@brief  �X�V����
******************************************************************************/

void MeshField::Update(void)
{
    //
    // �ʂ̖@�����Z�o
    //
    Vector3 *pNormal = new Vector3[pMesh->faceNum];
    for (int i = 0; i < pMesh->faceNum; i++)
    {
        if (i % 2 == 0)
        {
            Vector3 vec1 = pMesh->pVertex[pMesh->pIndexList[i + 1]].pos - pMesh->pVertex[pMesh->pIndexList[i + 0]].pos;
            Vector3 vec2 = pMesh->pVertex[pMesh->pIndexList[i + 2]].pos - pMesh->pVertex[pMesh->pIndexList[i + 0]].pos;
            Vector3::Cross(&pNormal[i], &vec1, &vec2);
        }
        else 
        {
            Vector3 vec1 = pMesh->pVertex[pMesh->pIndexList[i + 1]].pos - pMesh->pVertex[pMesh->pIndexList[i + 0]].pos;
            Vector3 vec2 = pMesh->pVertex[pMesh->pIndexList[i + 2]].pos - pMesh->pVertex[pMesh->pIndexList[i + 0]].pos;
            Vector3::Cross(&pNormal[i], &vec2, &vec1);
        }
        Vector3::Normalize(&pNormal[i], &pNormal[i]);
    }

    Vector3 pos = GameScene::GetCharacter(0)->GetPosition();
    Vector3 P;
    Vector3 X;
    Vector3 LineA = Vector3(pos.x, pos.y + 150.0f, pos.z);
    Vector3 LineB = Vector3(pos.x, pos.y, pos.z);
    for (int i = 0; i < pMesh->faceNum; i++)
    {
        //���ʏ�̓_X
        X = pMesh->pVertex[pMesh->pIndexList[i + 0]].pos;

        //XA XB�x�N�g��
        Vector3 XA = X - LineA;
        Vector3 XB = X - LineB;

        //XA XB���ꂼ��𕽖ʖ@���Ɠ���
        float dot_XA = Vector3::Dot(&XA, &pNormal[i]);
        float dot_XB = Vector3::Dot(&XB, &pNormal[i]);

        if (fabsf(dot_XA) < epsilon) { dot_XA = 0.0; }
        if (fabsf(dot_XB) < epsilon) { dot_XB = 0.0; }

        //�ђʔ���
        if (dot_XA * dot_XB <= 0.0f)
        {
            //���ς̕Е����v���X�ŕЕ����}�C�i�X�Ȃ̂ŁA�������Ă���
            Vector3 LineAB = LineB - LineA;

            //��_��A�̋��� : ��_��B�̋��� = dot_XA : dot_XB
            float hiritu = fabsf(dot_XA) / (abs(dot_XA) + abs(dot_XB));

            P.x = LineA.x + (LineAB.x * hiritu);
            P.y = LineA.y + (LineAB.y * hiritu);
            P.z = LineA.z + (LineAB.z * hiritu);

            // �B�|���S�������Ɋђʓ_���܂܂�邩���`�F�b�N
            Vector3 A = pMesh->pVertex[pMesh->pIndexList[i + 0]].pos;
            Vector3 B = pMesh->pVertex[pMesh->pIndexList[i + 1]].pos;
            Vector3 C = pMesh->pVertex[pMesh->pIndexList[i + 2]].pos;

            Vector3 AB = B - A;
            Vector3 BP = P - B;

            Vector3 BC = C - B;
            Vector3 CP = P - C;

            Vector3 CA = A - C;
            Vector3 AP = P - A;

            Vector3 cross[3];

            Vector3::Cross(&cross[0], &AB, &BP);
            Vector3::Cross(&cross[1], &BC, &CP);
            Vector3::Cross(&cross[2], &CA, &AP);

            float dot12 = Vector3::Dot(&cross[0], &cross[1]);
            float dot13 = Vector3::Dot(&cross[0], &cross[2]);
            float dot23 = Vector3::Dot(&cross[1], &cross[2]);

            if (fabsf(dot12) < 0.1f) { dot12 = 0.0f; }
            if (fabsf(dot13) < 0.1f) { dot13 = 0.0f; }
            if (fabsf(dot23) < 0.1f) { dot23 = 0.0f; }


            if (dot12 >= 0 && dot13 >= 0 && dot23 >= 0)
            {
                // �v���C���[�̍��W���ђʓ_�ɐݒ�
                GameScene::GetCharacter(0)->SetPosition(Vector3(P.x, P.y, P.z));
                Manager::GetDebug()->Print("PP : %.2f %.2f %.2f\n", P.x, P.y, P.z);
            }
        }
    }

    //
    // ���_�̖@�����Z�o
    //
    int blockNumX = widthDiv  + 1;
    int blockNumZ = heightDiv + 1;
    for (int i = 0; i < pMesh->vertexNum; i++)
    {
        Vector3 vec;
        int cnt = 0;

        // �E�㕔
        if (((i % blockNumX) < (blockNumX - 1)) && (i > (blockNumX - 1)))
        {// �g�p����ʃ|���S����1�ǉ�
            vec += pNormal[(((i / blockNumX) - 1) * (widthDiv * 2 + 4)) + ((i % blockNumX) * 2)];
            cnt++;
        }
        // ���㕔
        if ((0 < (i % blockNumX)) && (i > (blockNumX - 1)))
        {// �g�p����ʃ|���S����2�ǉ�
            // ��
            vec += pNormal[(((i / blockNumX) - 1) * (widthDiv * 2 + 4)) + ((i % blockNumX) * 2) - 2];
            // ��
            vec += pNormal[(((i / blockNumX) - 1) * (widthDiv * 2 + 4)) + ((i % blockNumX) * 2) - 1];
            cnt += 2;
        }
        // �E����
        if (((i % blockNumX) < (blockNumX - 1)) && (i < blockNumX*blockNumZ - blockNumX))
        {// �g�p����ʃ|���S����2�ǉ�
            // ��
            vec += pNormal[((i / blockNumX) * (widthDiv * 2 + 4)) + ((i % blockNumX) * 2)];
            // ��
            vec += pNormal[((i / blockNumX) * (widthDiv * 2 + 4)) + ((i % blockNumX) * 2) + 1];
            cnt += 2;
        }
        // ������
        if ((0 < (i % blockNumX)) && (i < blockNumX*blockNumZ - blockNumX))
        {// �g�p����ʃ|���S����1�ǉ�
            vec += pNormal[((i / blockNumX) * (widthDiv * 2 + 4)) + ((i % blockNumX) * 2) - 1];
            cnt++;
        }

        // �ʐ��Ŋ���
        vec /= (float)cnt;

        // ���K��
        Vector3::Normalize(&vec, &vec);
        pMesh->pVertex[i].nor = vec;
    }
    delete[] pNormal;
}

/******************************************************************************
@brief  �`�揈��
******************************************************************************/

void MeshField::Draw(void)
{
    Matrix WorldMatrix;

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
        indexNum - 2
        );

}

/******************************** ���������܂� *******************************/

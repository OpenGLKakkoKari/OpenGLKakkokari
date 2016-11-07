/*****************************************************************************/
/*!
@file   SkinMeshModel.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "SkinMeshModel.h"
#include "..\File\Reader\SkinMeshModelReader.h"
#include "..\Manager.h"
#include "..\Math\Vector4.h"


using namespace Framework;
using namespace Framework::File;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

SkinMeshModel::SkinMeshModel()
{
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

SkinMeshModel::~SkinMeshModel()
{
    for (int i = 0; i < (int)pMesh->vertexNum; i++)
    {
        delete[] pBoneIndexList[i];
        delete[] pWeightList[i];
    }
    delete[] pBoneIndexList;
    delete[] pWeightList;
    delete[] pBoneList;
    delete[] pVertexList;

    for (int i = 0; i < motionNum; i++)
    {
        for (int j = 0; j < pMotionList[i].keyframeNum; j++)
        {
            delete[] pMotionList[i].keyframeList[j].keyList;
        }
        delete[] pMotionList[i].keyframeList;
    }
    delete[] pMotionList;


    delete[] pCalcMatrix;
}

/******************************************************************************
@brief  ���[�V�������f���X�V
******************************************************************************/

void SkinMeshModel::Update()
{
    static int idx = -1;
    static int frame = -1;

    if (idx != activeMotionIndex || frame != pMotionList[activeMotionIndex].frame)
    {// ���b�V�����X�V
        CalcMesh();
    }

    idx = activeMotionIndex;
    frame = pMotionList[activeMotionIndex].frame;
}

/******************************************************************************
@brief  ���[�V�������f������
@param  ScriptFileName      �X�N���v�g�t�@�C����
@return SkinMeshModel*        ���[�V�������f��
******************************************************************************/

SkinMeshModel* SkinMeshModel::Load(const char *FileName)
{
    SkinMeshModel* motionModel = SkinMeshModelReader::Load(FileName);

    motionModel->pVertexList = new Vertex[motionModel->pMesh->vertexNum];
    memcpy_s(motionModel->pVertexList, sizeof(Vertex)*motionModel->pMesh->vertexNum, motionModel->pMesh->pVertex, sizeof(Vertex)*motionModel->pMesh->vertexNum);
    motionModel->pCalcMatrix = new Matrix[motionModel->boneNum];

    return motionModel;
}

/******************************************************************************
@brief  ���b�V���̒��_���{�[�����ɍ��킹�ĕϊ�
@brief  BOf�s��~���W�ϊ��s��~�tBOf�s��~�e���x
******************************************************************************/

void SkinMeshModel::CalcMesh()
{
    // ���W�ϊ��s��ƋtBOf�s����|���Z�������̂�\�ߎZ�o
    for (int i = 0; i < boneNum; i++)
        GetBoneMatrix(&pCalcMatrix[i], &pBoneList[i], i);

    Vertex* vtx = pMesh->pVtxBuf->Lock();
    for (int i = 0; i < (int)pMesh->vertexNum; i++)
    {
        // �v�Z�ςݍs��ABOf�s���p��
        Matrix calc[4], boneOff[4];

        for (int j = 0; j < 4; j++)
        {
            // BOf�����Ă���
            boneOff[j] = pBoneList[pBoneIndexList[i][j]].offset;
            // BOf�ƌv�Z�ςݍs����|���Z
            Matrix::Multiply(&calc[j], &boneOff[j], &pCalcMatrix[pBoneIndexList[i][j]]);
            // �e���x���|���Z
            calc[j] = calc[j] * pWeightList[i][j];
        }

        // �e�{�[���̌v�Z���ʂ𑫂����킹��
        Matrix sum = calc[0] + calc[1] + calc[2] + calc[3];

        // �v�Z���ʂ̍s��Œ��_��ό`
        Vector3::Transform(&vtx->pos, &pVertexList[i].pos, &sum);
        vtx++;
    }
    pMesh->pVtxBuf->Unlock();
}

/******************************************************************************
@brief  �{�[������s����v�Z
@param  pOut        �o�͍s��
@param  pBone       �{�[��
@param  pTransform  ���W�ϊ��s��
******************************************************************************/

void SkinMeshModel::GetBoneMatrix(Matrix* pOut, Bone* pBone, int boneIndex)
{
    Matrix transform, calc, parent;

    for (int i = 0; i < pMotionList[activeMotionIndex].keyframeNum - 1; i++)
    {
        if (pMotionList[activeMotionIndex].keyframeList[i].interval <= pMotionList[activeMotionIndex].frame &&
            pMotionList[activeMotionIndex].frame < pMotionList[activeMotionIndex].keyframeList[i + 1].interval)
        {
            // ��Ԏ������X�V
            int t_frame_diff = pMotionList[activeMotionIndex].keyframeList[i + 1].interval - pMotionList[activeMotionIndex].keyframeList[i].interval;
            float t = (float)(pMotionList[activeMotionIndex].frame - pMotionList[activeMotionIndex].keyframeList[i].interval) / (float)t_frame_diff;

            // ���`��ԂŊg�k�A��]�A�ړ��̌��݂̒l���Z�o
            Vector3 scale, trans, scale_diff, trans_diff;
            Quaternion rot;

            // �g�k�A��]�A�ړ��̒l�����݂̃t���[���ɍ��킹�ĕ��
            scale_diff = pMotionList[activeMotionIndex].keyframeList[i + 1].keyList[boneIndex].scale - pMotionList[activeMotionIndex].keyframeList[i].keyList[boneIndex].scale;
            trans_diff = pMotionList[activeMotionIndex].keyframeList[i + 1].keyList[boneIndex].trans - pMotionList[activeMotionIndex].keyframeList[i].keyList[boneIndex].trans;

            scale = pMotionList[activeMotionIndex].keyframeList[i].keyList[boneIndex].scale + (scale_diff * t);
            trans = pMotionList[activeMotionIndex].keyframeList[i].keyList[boneIndex].trans + (trans_diff * t);

            Quaternion::Slerp(&rot,
                &pMotionList[activeMotionIndex].keyframeList[i].keyList[boneIndex].rot,
                &pMotionList[activeMotionIndex].keyframeList[i + 1].keyList[boneIndex].rot,
                t);

            // ���݂̍��W�ϊ��s����|�����킹��
            Matrix::GetCalcMatrix(&transform, &scale, &rot, &trans);
            Matrix::Multiply(&calc, &calc, &transform);
        }
    }

    if (pBone->parent != -1)
    {
        // �v�Z�����s����g�p���Đe�̍s��𒲂ׂ�
        GetBoneMatrix(&parent, &pBoneList[pBone->parent], pBone->parent);
        Matrix::Multiply(pOut, &calc, &parent);
    }
}


/******************************** ���������܂� *******************************/

#pragma once
/******************************************************************************
/*!
@file   SkinMeshModel.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Model.h"
#include "Motion.h"
#include "Bone.h"


/*  �\���̒�`
******************************************************************************/


namespace Framework
{
    class SkinMeshModel : public Model
    {
    public:
        SkinMeshModel();
        virtual ~SkinMeshModel();

        void Update();
        
        static SkinMeshModel* Load(const char *FileName);

        void SetMotion(int index)           { activeMotionIndex = index; SetFrame(0); }
        void SetFrame(int frame)            { pMotionList[activeMotionIndex].SetFrame(frame); }
        void NextFrame(int addFrameCnt = 1) { pMotionList[activeMotionIndex].NextFrame(addFrameCnt); }
        bool IsMotionEnd(int index)         { return pMotionList[index].frame >= pMotionList[index].frameMax - 1; }
        void SetLoop(bool flag)             { pMotionList[activeMotionIndex].loop = flag; }


        int     boneNum;                // �{�[���s�񑍐�
        Bone*   pBoneList;              // �{�[�����X�g

        int**   pBoneIndexList;         // �{�[���C���f�b�N�X���X�g
        float** pWeightList;            // �{�[���̏d�݃��X�g

        Motion* pMotionList;            // ���[�V�������X�g
        int     motionNum;              // ���[�V��������
        int     activeMotionIndex;      // ���݂̃��[�V����

        Vertex* pVertexList;            // �����f���̒��_���X�g
        Matrix* pCalcMatrix;            // ���W�ϊ��s��ƋtBOf�s����|���Z��������


    protected:
        void CalcMesh();
        void GetBoneMatrix(Matrix* pOut, Bone* pBone, int boneIndex);

    };
}


/******************************* �w�b�_�����܂� ******************************/

#pragma once
/******************************************************************************
/*!
@file   OBB.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "..\Math\Vector3.h"
#include "..\Mesh\Mesh.h"


/*  �N���X��`
******************************************************************************/


namespace Framework
{
    class Model;
    class OBB
    {
    public:
        OBB();
        ~OBB();

        void Draw();
        void UpdateLength(Vertex* pVertexList, int vertexNum);
        void UpdateLength(Mesh* pMesh) { UpdateLength(pMesh->pVertex, pMesh->vertexNum); }

        Vector3 pos;        // ���S�_�̍��W
        Vector3 dir[3];     // XYZ �̊e���W���̌X����\�������x�N�g��
        Vector3 len;        // OBB �̊e���W���ɉ����������̔����i���S�_����ʂ܂ł̒����j
        Model*  pBox;       // �`��p

        static OBB* Create(Mesh* pMesh, Vector3 worldPos, Vector3 rot);
        static OBB* Create(Vector3 scale, Vector3 worldPos, Vector3 rot);
        static bool CheckCollision(OBB *pA, OBB *pB);
        static void ResolveCollision(OBB *pA, OBB *pB);
        static void ResolveCollision(OBB *pA, OBB *pB, Vector3 posOld);

    private:
        static float LenSegOnSeparateAxis(Vector3* v1, Vector3* v2, Vector3* v3, Vector3* v4);
        static float LenSegOnSeparateAxis(Vector3* v1, Vector3* v2, Vector3* v3);
    };
}


/****************************** �w�b�_�����܂� *******************************/

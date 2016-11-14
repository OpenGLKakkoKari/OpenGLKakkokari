#pragma once
/******************************************************************************
/*!
@file   SkinMeshData.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �\���̒�`
******************************************************************************/


namespace Framework
{
    struct SkinMeshDataHeader
    {
        int faceNum;            // �ʐ�
        int vertexNum;          // ���_��
        int materialNum;        // �}�e���A����
        int subsetNum;          // �T�u�Z�b�g��
        int boneNum;            // �{�[����
        int motionNum;          // ���[�V������
        int indexNum;           // �C���f�b�N�X��
    };
}


/******************************* �w�b�_�����܂� ******************************/

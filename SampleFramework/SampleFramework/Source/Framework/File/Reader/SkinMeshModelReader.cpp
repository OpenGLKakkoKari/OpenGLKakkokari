/*****************************************************************************/
/*!
@file   SkinMeshModelReader.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "SkinMeshModelReader.h"
#include "..\..\Mesh\SkinMeshDataHeader.h"
#include "..\..\Mesh\MaterialData.h"
#include <crtdbg.h>
#include "../File.h"
#include "../../Error.h"
#include "../../Manager.h"

using namespace Framework;
using namespace Framework::File;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  ファイル読み込み
@param  FileName    ファイル名
@return Texture     テクスチャ情報
******************************************************************************/

SkinMeshModel* SkinMeshModelReader::Load(const char *FileName)
{
    SkinMeshModel* pSkinMesh = NULL;
    File file;
    if (!file.Open(FileName, "rb"))
    {
        Error::Message("ファイル\"%s\"の読み込みに失敗しました。", FileName);
        return pSkinMesh;
    }
    fileSize = file.GetSize();

    SkinMeshDataHeader header;
    file.Read(&header, sizeof(SkinMeshDataHeader), 1);

    //
    // 領域確保
    //

    pSkinMesh = new SkinMeshModel;
    pSkinMesh->pMesh = new Mesh;
    
    pSkinMesh->pMesh->faceNum = header.faceNum;
    pSkinMesh->pMesh->vertexNum = header.vertexNum;
    pSkinMesh->pMesh->pVertex = new Vertex[header.vertexNum];
    pSkinMesh->pMesh->pIndexList = new int[header.indexNum];
    pSkinMesh->pMesh->pMaterialList = new Material[header.materialNum];
    pSkinMesh->pMesh->materialNum = header.materialNum;
    pSkinMesh->pMesh->pSubsetList = new Mesh::Subset[header.subsetNum];
    pSkinMesh->pMesh->subsetNum = header.subsetNum;

    pSkinMesh->boneNum = header.boneNum;
    pSkinMesh->pBoneList = new Bone[header.boneNum];
    pSkinMesh->pBoneIndexList = new int*[header.vertexNum];
    pSkinMesh->pWeightList = new float*[header.vertexNum];
    for (int i = 0; i < header.vertexNum; i++)
    {
        pSkinMesh->pBoneIndexList[i] = new int[4];
        pSkinMesh->pWeightList[i] = new float[4];
    }
    pSkinMesh->pMotionList = new Motion[header.motionNum];
    pSkinMesh->motionNum = header.motionNum;
    pSkinMesh->activeMotionIndex = 0;

    //
    // 領域にデータを格納
    //

    MaterialData* pMateralData = new MaterialData[header.materialNum];

    file.Read(pSkinMesh->pMesh->pVertex, sizeof(Vertex) * header.vertexNum, 1);
    file.Read(pSkinMesh->pMesh->pIndexList, sizeof(int) * header.indexNum, 1);

    file.Read(pMateralData, sizeof(MaterialData) * header.materialNum, 1);

    file.Read(pSkinMesh->pMesh->pSubsetList, sizeof(Mesh::Subset) * header.subsetNum, 1);
    file.Read(pSkinMesh->pBoneList, sizeof(Bone) * header.boneNum, 1);


    for (int i = 0; i < header.vertexNum; i++)
        for (int j = 0; j < 4; j++)
            file.Read(&pSkinMesh->pBoneIndexList[i][j], sizeof(int), 1);

    for (int i = 0; i < header.vertexNum; i++)
        for (int j = 0; j < 4; j++)
            file.Read(&pSkinMesh->pWeightList[i][j], sizeof(float), 1);


    for (int i = 0; i < header.motionNum; i++)
    {
        Motion::MotionDataHeader motionHeader;
        file.Read(&motionHeader, sizeof(Motion::MotionDataHeader), 1);
        pSkinMesh->pMotionList[i].frame = 0;
        pSkinMesh->pMotionList[i].frameMax = motionHeader.frameMax;
        pSkinMesh->pMotionList[i].loop = motionHeader.loop;
        pSkinMesh->pMotionList[i].keyframeNum = motionHeader.keyframeNum;
        pSkinMesh->pMotionList[i].keyframeList = new Motion::KeyFrame[motionHeader.keyframeNum];
        for (int j = 0; j < motionHeader.keyframeNum; j++)
        {
            pSkinMesh->pMotionList[i].keyframeList[j].keyList = new Motion::Key[header.boneNum];
            file.Read(&pSkinMesh->pMotionList[i].keyframeList[j].interval, sizeof(int), 1);
            
            for (int k = 0; k < header.boneNum; k++)
                file.Read(&pSkinMesh->pMotionList[i].keyframeList[j].keyList[k], sizeof(Motion::Key), 1);
        }
    }

    for (int i = 0; i < header.materialNum; i++)
    {
        pSkinMesh->pMesh->pMaterialList[i].ambient = pMateralData[i].ambient;
        pSkinMesh->pMesh->pMaterialList[i].diffuse = pMateralData[i].diffuse;
        pSkinMesh->pMesh->pMaterialList[i].emissive = pMateralData[i].emissive;
        pSkinMesh->pMesh->pMaterialList[i].specular = pMateralData[i].specular;
        pSkinMesh->pMesh->pMaterialList[i].power = pMateralData[i].power;
        if (pMateralData[i].fileName != NULL)
        {
            pSkinMesh->pMesh->pMaterialList[i].pTexture = Texture::Load(pMateralData[i].fileName);
        }
    }

    delete[] pMateralData;


    pSkinMesh->pMesh->pVtxBuf = Manager::GetRenderer()->CreateVertexBuffer(header.vertexNum);
    pSkinMesh->pMesh->pIdxBuf = Manager::GetRenderer()->CreateIndexBuffer(header.indexNum);
    Vertex* vtx = pSkinMesh->pMesh->pVtxBuf->Lock();
    for (int i = 0; i < header.vertexNum; i++)
    {
        *vtx = pSkinMesh->pMesh->pVertex[i];
        vtx++;
    }
    pSkinMesh->pMesh->pVtxBuf->Unlock();
    int* idx = pSkinMesh->pMesh->pIdxBuf->Lock();
    for (int i = 0; i < header.indexNum; i++)
    {
        *idx = pSkinMesh->pMesh->pIndexList[i];
        idx++;
    }
    pSkinMesh->pMesh->pIdxBuf->Unlock();

    return pSkinMesh;
}

/******************************* 関数ここまで ********************************/

/*****************************************************************************/
/*!
@file   ModelReader.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "ModelReader.h"
#include <crtdbg.h>
#include "../File.h"
#include "../../Error.h"
#include "../../Manager.h"
#include "../../TokenAnalyzer.h"


using namespace Framework;
using namespace Framework::File;


/*  ����
******************************************************************************/


char ModelReader::materialNameList[64][64];


/******************************************************************************
@brief  �t�@�C���ǂݍ���
@param  FileName    �t�@�C����
@return Mesh*       ���b�V�����
******************************************************************************/

Mesh* ModelReader::Load(const char *FileName)
{

    strcpy(fileName, FileName);
    GetExtension(FileName);
    CurrentDirectory(FileName);

    if (strcmp(ext, ".x") == 0)
    {
        return LoadX(FileName);
    }
    else if (strcmp(ext, ".obj") == 0)
    {
        return LoadOBJ(FileName);
    }

    return NULL;

}

/******************************************************************************
@brief  X�t�@�C���ǂݍ���
@param  FileName    �t�@�C����
@return Mesh*       ���b�V�����
******************************************************************************/

Mesh* ModelReader::LoadX(const char *FileName)
{
    Mesh* pMesh;

    File file;
    if (!file.Open(FileName, "rb"))
    {
        Error::Message("�t�@�C��\"%s\"�̓ǂݍ��݂Ɏ��s���܂����B", FileName);
        return NULL;
    }
    pMesh = new Mesh;
    fileSize = file.GetSize();

    // �o�b�t�@�Ƀt�@�C���f�[�^���i�[
    char* pBuf = new char[fileSize + 1];
    pBuf[fileSize] = '\0';
    file.Read(pBuf, fileSize, 1);
    file.Close();

    // �������ݒ�
    TokenAnalyzer* pToken = new TokenAnalyzer(pBuf);
    pToken->SetSkipChars(" \t\n\r,;\"");

    Material        *pMaterialList = NULL;
    Mesh::Subset    *pSubsetList = NULL;

    Vector3*        pPosList = NULL;
    Vector3*        pNormalList = NULL;
    Vector2*        pTexList = NULL;
    int             *pIndex = NULL;
    int             *pNormalIndex = NULL;

    int vertexCount = 0;
    int faceCount = 0;
    int materialCount = 0;
    int subsetCount = 0;
    int normalCount = 0;
    int uvCount = 0;

    /**
     * X�t�@�C���ǂݍ���
     * �@ �g�[�N�����擾
     * �A �`�����N���Ƃɕ���
     */

    // �t�@�C����� ////////////////////
    while (!pToken->IsScriptEnd())
    {

        pToken->GetToken();

        //�@template���X�L�b�v
        if (pToken->CheckToken("template"))
        {
            pToken->SkipBracket();
        }

        //�@Mesh�̏ꍇ
        else if (pToken->CheckToken("Mesh"))
        {
            // �g�[�N�����擾
            pToken->GetToken();

            // " { " ���o��܂Ń��[�v
            while (!pToken->CheckToken("{"))
            {
                pToken->GetToken();
            }

            // �g�[�N�����璸�_�����擾
            vertexCount = 0;
            vertexCount = pToken->GetIntToken();

            pPosList = new Vector3[vertexCount];
            for (int i = 0; i < vertexCount; i++)
            { // ���_�����擾
                pPosList[i].x = pToken->GetFloatToken();
                pPosList[i].y = pToken->GetFloatToken();
                pPosList[i].z = pToken->GetFloatToken();
            }

            // �g�[�N������ʐ����擾
            faceCount = 0;
            faceCount = pToken->GetIntToken();

            pIndex = new int[faceCount * 3];
            // �g�[�N������ʃf�[�^���擾
            for (int i = 0; i < faceCount; i++)
            {
                pToken->GetToken();

                pIndex[i * 3 + 0] = pToken->GetIntToken();
                pIndex[i * 3 + 1] = pToken->GetIntToken();
                pIndex[i * 3 + 2] = pToken->GetIntToken();
            }


        }//�@MeshMaterialList�̏ꍇ
        else if (pToken->CheckToken("MeshMaterialList"))
        {
            //�@�g�[�N��"{"���擾
            pToken->GetToken();

            //�@�g�[�N������}�e���A�������擾
            materialCount = 0;
            materialCount = pToken->GetIntToken();

            //�@�ʐ����`�F�b�N
            int materialFaceCount = pToken->GetIntToken();
            _ASSERT(materialFaceCount == faceCount);

            pMaterialList = new Material[materialCount];
            pSubsetList = new Mesh::Subset[100];

            int mi, oldmi;
            oldmi = pToken->GetIntToken();

            subsetCount = 0;
            pSubsetList[0].startIndex = 0;
            pSubsetList[0].materialIndex = oldmi;

            //�@�g�[�N������}�e���A���C���f�b�N�X���擾
            for (int i = 1; i < faceCount; i++)
            {
                mi = pToken->GetIntToken();

                if (mi != oldmi)
                {
                    pSubsetList[subsetCount].count = i - pSubsetList[subsetCount].startIndex / 3;
                    subsetCount++;

                    pSubsetList[subsetCount].startIndex = i * 3;
                    pSubsetList[subsetCount].materialIndex = mi;

                    oldmi = mi;
                }
            }

            pSubsetList[subsetCount].count = faceCount - pSubsetList[subsetCount].startIndex / 3;
            subsetCount++;

            for (int i = 0; i < materialCount; i++)
            {
                // �g�[�N��"Material"���擾
                pToken->GetToken();
                // �g�[�N��"{"���擾
                pToken->GetToken();

                //�@�g�[�N����" { "�łȂ��ꍇ
                if (!pToken->CheckToken("{"))
                {
                    //�@�g�[�N��"{"���擾
                    pToken->GetToken();
                }

                //�@Diffuse Color
                pMaterialList[i].diffuse.r = pToken->GetFloatToken();
                pMaterialList[i].diffuse.g = pToken->GetFloatToken();
                pMaterialList[i].diffuse.b = pToken->GetFloatToken();
                pMaterialList[i].diffuse.a = pToken->GetFloatToken();

                //�@Ambient Color
                pMaterialList[i].ambient.r = 0.0f;
                pMaterialList[i].ambient.g = 0.0f;
                pMaterialList[i].ambient.b = 0.0f;
                pMaterialList[i].ambient.a = 1.0f;

                //�@Shiness
                pMaterialList[i].power = pToken->GetFloatToken();

                //�@Specular Color
                pMaterialList[i].specular.r = pToken->GetFloatToken();
                pMaterialList[i].specular.g = pToken->GetFloatToken();
                pMaterialList[i].specular.b = pToken->GetFloatToken();
                pMaterialList[i].specular.a = 1.0f;

                //�@Emissive Color
                pMaterialList[i].emissive.r = pToken->GetFloatToken();
                pMaterialList[i].emissive.g = pToken->GetFloatToken();
                pMaterialList[i].emissive.b = pToken->GetFloatToken();
                pMaterialList[i].emissive.a = 1.0f;

                // �g�[�N�����擾
                pToken->GetToken();
                pMaterialList[i].pTexture = 0;

                // TextureFileName�̏ꍇ
                if (pToken->CheckToken("TextureFilename"))
                {
                    // �g�[�N��"{"���擾
                    pToken->GetToken();

                    // �t�@�C�������Z�b�g
                    pMaterialList[i].pTexture = Texture::Load(pToken->GetToken());

                    // �g�[�N��"���擾
                    pToken->GetToken();
                    // �g�[�N��"}"���擾
                    pToken->GetToken();
                }
            }
        }
        //�@MeshNormals�̏ꍇ
        else if (pToken->CheckToken("MeshNormals"))
        {
            // �g�[�N��"{"���擾
            pToken->GetToken();

            // �g�[�N������@�������擾
            normalCount = 0;
            normalCount = pToken->GetIntToken();

            pNormalList = new Vector3[normalCount];

            // �g�[�N������@���f�[�^���擾
            for (int i = 0; i < normalCount; i++)
            {
                pNormalList[i].x = pToken->GetFloatToken();
                pNormalList[i].y = pToken->GetFloatToken();
                pNormalList[i].z = pToken->GetFloatToken();
            }

            //�@�ʐ����`�F�b�N
            int normFaceCount = pToken->GetIntToken();
            pNormalIndex = new int[normFaceCount * 3];
            for (int i = 0; i < normFaceCount; i++)
            {
                // �g�[�N�����擾
                pToken->GetToken();

                pNormalIndex[i * 3 + 0] = pToken->GetIntToken();
                pNormalIndex[i * 3 + 1] = pToken->GetIntToken();
                pNormalIndex[i * 3 + 2] = pToken->GetIntToken();
            }

        }
        //�@MeshTextureCoords�̏ꍇ
        else if (pToken->CheckToken("MeshTextureCoords"))
        {
            //�@�g�[�N��"{"���擾
            pToken->GetToken();

            //�@�g�[�N������e�N�X�`�����W�����擾
            uvCount = 0;
            uvCount = pToken->GetIntToken();
            pTexList = new Vector2[uvCount];

            for (int i = 0; i < uvCount; i++)
            { // �e�N�X�`�����W��}��
                pTexList[i].x = pToken->GetFloatToken();
                pTexList[i].y = pToken->GetFloatToken();
            }
        }
    }
    delete pToken;

    // �o�b�t�@�J��
    delete[] pBuf;

    pMesh->vertexNum = faceCount * 3;
    pMesh->faceNum = faceCount;

    pMesh->pVertex = new Vertex[faceCount * 3];
    for (int i = 0; i < faceCount * 3; i++)
    {
        pMesh->pVertex[i].pos = pPosList[pIndex[i]];
        pMesh->pVertex[i].nor = pNormalList[pNormalIndex[i]];
        pMesh->pVertex[i].tex = pTexList[pIndex[i]];
        pMesh->pVertex[i].col = Color(255, 255, 255, 255);
    }

    pMesh->pIndexList = new int[faceCount * 3];
    for (int i = 0; i < faceCount * 3; i++)
        pMesh->pIndexList[i] = i;


    pMesh->pVtxBuf = Manager::GetRenderer()->CreateVertexBuffer(faceCount * 3);
    pMesh->pIdxBuf = Manager::GetRenderer()->CreateIndexBuffer(faceCount * 3);
    Vertex* vtx  = pMesh->pVtxBuf->Lock();
    for (int i = 0; i < faceCount * 3; i++)
    {
        vtx->pos = pPosList[pIndex[i]];
        vtx->nor = pNormalList[pNormalIndex[i]];
        vtx->tex = pTexList[pIndex[i]];
        vtx->col = Color(255, 255, 255, 255);
        vtx++;
    }
    pMesh->pVtxBuf->Unlock();
    int* idx = pMesh->pIdxBuf->Lock();
    for (int i = 0; i < faceCount * 3; i++)
    {
        *idx = i;
        idx++;
    }
    pMesh->pIdxBuf->Unlock();

    pMesh->pMaterialList = pMaterialList;
    pMesh->materialNum = materialCount;

    pMesh->pSubsetList = pSubsetList;
    pMesh->subsetNum = subsetCount;

    delete[] pPosList;
    delete[] pNormalList;
    delete[] pTexList;
    delete[] pIndex;
    delete[] pNormalIndex;

    return pMesh;
}

/******************************************************************************
@brief  OBJ�t�@�C���ǂݍ���
@param  FileName    �t�@�C����
@return Mesh*       ���b�V�����
******************************************************************************/

Mesh* ModelReader::LoadOBJ(const char *FileName)
{
    Mesh* pMesh;

    File file;
    if (!file.Open(FileName, "rb"))
    {
        Error::Message("�t�@�C��\"%s\"�̓ǂݍ��݂Ɏ��s���܂����B", FileName);
        return NULL;
    }
    pMesh = new Mesh;
    fileSize = file.GetSize();

    // �o�b�t�@�Ƀt�@�C���f�[�^���i�[
    char* pBuf = new char[fileSize + 1];
    pBuf[fileSize] = '\0';
    file.Read(pBuf, fileSize, 1);
    file.Close();

    // �������ݒ�
    TokenAnalyzer* pToken = new TokenAnalyzer(pBuf);
    pToken->SetSkipChars(" \t\n\r,;\"");

    Vector3         *pPosList = nullptr;
    Vector2         *pTexList = nullptr;
    Vector3         *pNormalList = nullptr;

    int vertexCount = 0;
    int normalCount = 0;
    int uvCount = 0;
    int faceCount = 0;
    int subsetCount = 0;

/**
 * OBJ�t�@�C���ǂݍ���
 * �@ ���_�����擾
 * �A �`�����N���Ƃɕ���
 */

    // �t�@�C����� ////////////////////
    while (!pToken->IsScriptEnd())
    {

        pToken->GetToken();

        // mtllib��ǂݍ���
        if (pToken->CheckToken("mtllib"))
        {
            // �t�@�C�����ǂݍ���
            LoadMTL(pToken->GetToken(), &pMesh->materialNum, &pMesh->pMaterialList);
        }

        // �ʐ���ǂݍ���
        if (pToken->CheckToken("f"))
        {
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();

            faceCount++;
        }
        //���_���W�������X�g�ɓǂݍ���
        else if (pToken->CheckToken("v"))
        {
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();

            vertexCount++;
        }
        // ���_UV���W�������X�g�ɓǂݍ���
        else if (pToken->CheckToken("vt"))
        {
            pToken->GetToken();
            pToken->GetToken();

            uvCount++;
        }
        // ���_�@���������X�g�ɓǂݍ���
        else if (pToken->CheckToken("vn"))
        {
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();

            normalCount++;
        }
        // �T�u�Z�b�g����ǂݍ���
        else if (pToken->CheckToken("usemtl"))
        {
            pToken->GetToken();
            subsetCount++;
        }
    }

    // �J�[�\�������ɖ߂�
    pToken->Reset();

    // �o�b�t�@���m��
    pPosList = new Vector3[vertexCount];
    pTexList = new Vector2[uvCount];
    pNormalList = new Vector3[normalCount];

    // �̈���m��
    pMesh->pSubsetList = new Mesh::Subset[subsetCount];
    pMesh->pVertex     = new Vertex[faceCount * 3];
    pMesh->pIndexList  = new int[faceCount * 3];

    // ���l���
    pMesh->faceNum = faceCount;
    pMesh->vertexNum = faceCount * 3;
    pMesh->subsetNum = subsetCount;

    for (int i = 0; i < faceCount; i++)
    {
        pMesh->pIndexList[i * 3 + 0] = i * 3 + 0;
        pMesh->pIndexList[i * 3 + 1] = i * 3 + 1;
        pMesh->pIndexList[i * 3 + 2] = i * 3 + 2;
    }

    // �J�E���^�����Z�b�g
    subsetCount = 0;
    faceCount = 0;
    vertexCount = 0;
    normalCount = 0;
    uvCount = 0;
    int posCount = 0;

    // �t�@�C����� ////////////////////
    while (!pToken->IsScriptEnd())
    {

        pToken->GetToken();

        //���_���W�������X�g�ɓǂݍ���
        if (pToken->CheckToken("v"))
        {
            pPosList[posCount].x = pToken->GetFloatToken();
            pPosList[posCount].y = pToken->GetFloatToken();
            pPosList[posCount].z = pToken->GetFloatToken();

            posCount++;
        }
        //���_UV���W�������X�g�ɓǂݍ���
        if (pToken->CheckToken("vt"))
        {
            pTexList[uvCount].x = pToken->GetFloatToken();
            pTexList[uvCount].y = pToken->GetFloatToken();

            uvCount++;
        }
        //���_�@���������X�g�ɓǂݍ���
        if (pToken->CheckToken("vn"))
        {
            pNormalList[normalCount].x = pToken->GetFloatToken();
            pNormalList[normalCount].y = pToken->GetFloatToken();
            pNormalList[normalCount].z = pToken->GetFloatToken();

            normalCount++;
        }

        // �T�u�Z�b�g�P�ʂœǂݍ���
        else if (pToken->CheckToken("usemtl"))
        {
            pMesh->pSubsetList[subsetCount].materialIndex = GetMaterialIndex(pToken->GetToken());
            pMesh->pSubsetList[subsetCount].startIndex = vertexCount;
            faceCount = 0;

            // �g�[�N��"f"��ǂݍ���
            pToken->GetToken();

            //�@�ʐ���ǂݍ���
            while (pToken->CheckToken("f"))
            {
                pMesh->pVertex[vertexCount].pos = pPosList[pToken->GetIntToken() - 1];
                pMesh->pVertex[vertexCount].tex = pTexList[pToken->GetIntToken() - 1];
                pMesh->pVertex[vertexCount].nor = pNormalList[pToken->GetIntToken() - 1];
                vertexCount++;

                pMesh->pVertex[vertexCount].pos = pPosList[pToken->GetIntToken() - 1];
                pMesh->pVertex[vertexCount].tex = pTexList[pToken->GetIntToken() - 1];
                pMesh->pVertex[vertexCount].nor = pNormalList[pToken->GetIntToken() - 1];
                vertexCount++;

                pMesh->pVertex[vertexCount].pos = pPosList[pToken->GetIntToken() - 1];
                pMesh->pVertex[vertexCount].tex = pTexList[pToken->GetIntToken() - 1];
                pMesh->pVertex[vertexCount].nor = pNormalList[pToken->GetIntToken() - 1];
                vertexCount++;

                faceCount++;

                // ���̃g�[�N����ǂݍ���
                pToken->GetToken();

            }
            pMesh->pSubsetList[subsetCount].count = faceCount;
            subsetCount++;
        }

    }
    delete pToken;

    // �o�b�t�@�J��
    delete[] pPosList;
    delete[] pTexList;
    delete[] pNormalList;

    delete[] pBuf;

    return pMesh;
}

/******************************************************************************
@brief  MTL�t�@�C���ǂݍ���
@param  FileName    �t�@�C����
@param  pMatNum     �}�e���A����
@param  pMatList    �}�e���A�����X�g
******************************************************************************/

void ModelReader::LoadMTL(const char *FileName, int *pMatNum, Material** pMatList)
{

    File file;
    char FilePath[MAX_PATH];
    memset(FilePath, 0, MAX_PATH);
    strcat(FilePath, dir);
    strcat(FilePath, FileName);
    if (!file.Open(FilePath, "rb"))
    {
        Error::Message("�t�@�C��\"%s\"�̓ǂݍ��݂Ɏ��s���܂����B", FileName);
        return;
    }
    fileSize = file.GetSize();

    // �o�b�t�@�Ƀt�@�C���f�[�^���i�[
    char* pBuf = new char[fileSize + 1];
    pBuf[fileSize] = '\0';
    file.Read(pBuf, fileSize, 1);
    file.Close();

    TokenAnalyzer* pToken = new TokenAnalyzer(pBuf);

    Material        *pMatBuf = nullptr;
    int materialCnt = 0;

    // �o�b�t�@���m��
    pMatBuf = new Material[100];

    
/**
 * MTL�t�@�C���ǂݍ���
 * �@ �g�[�N�����擾
 * �A �`�����N���Ƃɕ���
 */

    // �t�@�C����� ////////////////////
    while (!pToken->IsScriptEnd())
    {
        pToken->GetToken();

        //�@�}�e���A����ǂݍ���
        if (pToken->CheckToken("newmtl"))
        {
            strcpy(materialNameList[materialCnt], pToken->GetToken());
            pToken->GetToken();
            memset(&pMatBuf[materialCnt], 0, sizeof(Material));
            if (pToken->CheckToken("Ka"))
            {
                pMatBuf[materialCnt].ambient.r = pToken->GetFloatToken();
                pMatBuf[materialCnt].ambient.g = pToken->GetFloatToken();
                pMatBuf[materialCnt].ambient.b = pToken->GetFloatToken();
                pMatBuf[materialCnt].ambient.a = 255;
                pToken->GetToken();
            }
            if (pToken->CheckToken("Kd"))
            {
                pMatBuf[materialCnt].diffuse.r = pToken->GetFloatToken();
                pMatBuf[materialCnt].diffuse.g = pToken->GetFloatToken();
                pMatBuf[materialCnt].diffuse.b = pToken->GetFloatToken();
                pMatBuf[materialCnt].diffuse.a = 255;
                pToken->GetToken();
            }
            if (pToken->CheckToken("Ks"))
            {
                pMatBuf[materialCnt].specular.r = pToken->GetFloatToken();
                pMatBuf[materialCnt].specular.g = pToken->GetFloatToken();
                pMatBuf[materialCnt].specular.b = pToken->GetFloatToken();
                pMatBuf[materialCnt].specular.a = 255;
                pToken->GetToken();
            }
            if (pToken->CheckToken("illum"))
            {
                pToken->GetToken();
                pToken->GetToken();
            }
            if (pToken->CheckToken("Ns"))
            {
                pMatBuf[materialCnt].power = pToken->GetFloatToken();
                pToken->GetToken();
            }
            if (pToken->CheckToken("Tr"))
            {
                pToken->GetToken();
                pToken->GetToken();
            }
            if (pToken->CheckToken("map_Kd"))
            {
                char TexPath[MAX_PATH];
                memset(TexPath, 0, MAX_PATH);
                strcat(TexPath, dir);
                strcat(TexPath, pToken->GetToken());
                pMatBuf[materialCnt].pTexture = Texture::Load(TexPath);
                pToken->GetToken();
            }

            materialCnt++;
        }
    }

    delete pToken;

    // �擾�����}�e���A������ݒ�
    *pMatNum = materialCnt;
    *pMatList = new Material[materialCnt];
    memcpy(*pMatList, pMatBuf, sizeof(Material) * materialCnt);
    
    // �o�b�t�@�J��
    delete[] pBuf;
    delete[] pMatBuf;

}

/******************************************************************************
@brief  �}�e���A�������C���f�b�N�X�ɕϊ�
@param  MaterialName        �}�e���A����
@return int                 �C���f�b�N�X
******************************************************************************/

int ModelReader::GetMaterialIndex(const char* MaterialName)
{
    for (int i = 0; i < 64; i++)
    {
        if (strcmp(&materialNameList[i][0], MaterialName) == 0)
        {
            return i;
        }
    }
    return 0;
}

/******************************* �֐������܂� ********************************/

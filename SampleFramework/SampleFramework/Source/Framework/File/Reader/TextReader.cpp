/*****************************************************************************/
/*!
@file   TextReader.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "TextReader.h"
#include "ModelReader.h"
#include "../File.h"
#include "../../Error.h"
#include "../../Math/Math.h"
#include "../../TokenAnalyzer.h"
#include "../../../Game/MeshField.h"
#include "../../../Game/Plant.h"

using Framework::File::File;
using Framework::File::TextReader;
using Framework::File::ModelReader;
using namespace Framework;
using namespace Framework::Math;
using namespace Game;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  ���[�V�������f���ǂݍ���
@param  FileName    �t�@�C����
@return MotionModel ���[�V�������f�����
******************************************************************************/

MotionModel* TextReader::LoadMotionModel(const char *FileName)
{
    MotionModel* pMotionModel = NULL;

    // �t�@�C���ǂݍ���
    File file;
    if (!file.Open(FileName, "r"))
    {
        Error::Message("�t�@�C��\"%s\"�̓ǂݍ��݂Ɏ��s���܂����B", FileName);
        return pMotionModel;
    }
    fileSize = file.GetSize();

    // �o�b�t�@�Ƀt�@�C���f�[�^���i�[
    char* pBuf = new char[fileSize + 1];
    pBuf[fileSize] = '\0';
    file.Read(pBuf, fileSize, 1);
    file.Close();

    TokenAnalyzer* pToken = new TokenAnalyzer(pBuf);
    pToken->SetSkipChars(" \t\n\r,;\"");

    int modelLoadCnt = 0;
    int partsLoadCnt = 0;
    int motionLoadCnt = 0;

    pMotionModel = new MotionModel;
    
/**
 * TXT�t�@�C��(���[�V�����X�N���v�g)�ǂݍ���
 * �@ �g�[�N�����擾
 * �A �`�����N���Ƃɕ���
 */

    // �t�@�C����� ////////////////////
    while (!pToken->IsScriptEnd())
    {
        pToken->GetToken();

        // NUM_MODEL
        if (pToken->CheckToken("NUM_MODEL"))
        {
            // = ���X�L�b�v
            pToken->GetToken();
            pMotionModel->modelNum = pToken->GetIntToken();
            pMotionModel->pModelList = new Model*[pMotionModel->modelNum];
        }
        // MODEL_FILENAME
        if (pToken->CheckToken("MODEL_FILENAME"))
        {
            // = ���X�L�b�v
            pToken->GetToken();
            // �t�@�C�������擾
            pMotionModel->pModelList[modelLoadCnt] = Model::Load(pToken->GetToken());
            modelLoadCnt++;
        }

        // CHARACTERSET
        if (pToken->CheckToken("CHARACTERSET"))
        {
            // MOVE ���X�L�b�v
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();
            // JUMP ���X�L�b�v
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();
            // RADIUS ���X�L�b�v
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();
            // NUM_PARTS ��Ǎ�
            pToken->GetToken();
            pToken->GetToken();
            pMotionModel->partsNum = pToken->GetIntToken();
            pMotionModel->pPartsModelList = new Model*[pMotionModel->modelNum];
            pToken->GetToken();
            pToken->GetToken();
        }

        // PARTSSET
        // �p�[�c�ƃ��f���̑Ή��֌W�Ƀo�O����
        if (pToken->CheckToken("PARTSSET"))
        {
            // INDEX ��ǂݍ���
            pToken->GetToken();
            pToken->GetToken();
            // ���f�����R�s�[
            pMotionModel->pPartsModelList[partsLoadCnt] = pMotionModel->pModelList[pToken->GetIntToken()];
            pToken->GetToken();
            pToken->GetToken();
            
            // PARENT ��ǂݍ���
            pToken->GetToken();
            pToken->GetToken();
            int parentIndex = pToken->GetIntToken();
            if (parentIndex == -1)
                pMotionModel->pPartsModelList[partsLoadCnt]->SetParent(pMotionModel);
            else
                pMotionModel->pPartsModelList[partsLoadCnt]->SetParent(pMotionModel->pPartsModelList[parentIndex]);
            pToken->GetToken();
            pToken->GetToken();
            
            // POS ��ǂݍ���
            pToken->GetToken();
            pToken->GetToken();
            pMotionModel->pPartsModelList[partsLoadCnt]->pos_.x = pToken->GetFloatToken();
            pMotionModel->pPartsModelList[partsLoadCnt]->pos_.y = pToken->GetFloatToken();
            pMotionModel->pPartsModelList[partsLoadCnt]->pos_.z = pToken->GetFloatToken();

            // ROT ��ǂݍ���
            pToken->GetToken();
            pToken->GetToken();
            pMotionModel->pPartsModelList[partsLoadCnt]->rot_.x = pToken->GetFloatToken();
            pMotionModel->pPartsModelList[partsLoadCnt]->rot_.y = pToken->GetFloatToken();
            pMotionModel->pPartsModelList[partsLoadCnt]->rot_.z = pToken->GetFloatToken();

            partsLoadCnt++;
        }

        // NUM_MOTION
        if (pToken->CheckToken("NUM_MOTION"))
        {
            // = ��ǂݍ���
            pToken->GetToken();
            pMotionModel->motionNum = pToken->GetIntToken();
            pMotionModel->pMotionList = new Motion[pMotionModel->motionNum];
        }

        // MOTIONSET
        if (pToken->CheckToken("MOTIONSET"))
        {
            // LOOP ��ǂݍ���
            pToken->GetToken();
            pToken->GetToken();
            pMotionModel->pMotionList[motionLoadCnt].loop = (pToken->GetIntToken() == 0) ? (false) : (true);
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();

            // NUM_KEY ��ǂݍ���
            pToken->GetToken();
            pToken->GetToken();
            pMotionModel->pMotionList[motionLoadCnt].keyframeNum = pToken->GetIntToken();
            pToken->GetToken();
            pToken->GetToken();

            pMotionModel->pMotionList[motionLoadCnt].keyframeList = new Motion::KeyFrame[pMotionModel->pMotionList[motionLoadCnt].keyframeNum];
            for (int i = 0; i < pMotionModel->pMotionList[motionLoadCnt].keyframeNum; i++)
            {
                pMotionModel->pMotionList[motionLoadCnt].keyframeList[i].keyList = new Motion::Key[pMotionModel->partsNum];
            }

            // KEYSET ��ǂݍ���
            for (int i = 0; i < pMotionModel->pMotionList[motionLoadCnt].keyframeNum; i++)
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
                pToken->GetToken();
                pToken->GetToken();
                // FRAME ��ǂݍ���
                pToken->GetToken();
                pToken->GetToken();
                pMotionModel->pMotionList[motionLoadCnt].keyframeList[i].interval = pToken->GetIntToken();
                // ���v�t���[�����Z�o
                pMotionModel->pMotionList[motionLoadCnt].frameMax += pMotionModel->pMotionList[motionLoadCnt].keyframeList[i].interval;
                
                for (int j = 0; j < pMotionModel->partsNum; j++)
                {
                    pToken->GetToken();
                    pToken->GetToken();
                    pToken->GetToken();
                    pToken->GetToken();
                    pToken->GetToken();
                    pToken->GetToken();
                    pToken->GetToken();
                    // POS ��ǂݍ���
                    pToken->GetToken();
                    pToken->GetToken();
                    pMotionModel->pMotionList[motionLoadCnt].keyframeList[i].keyList[j].trans.x = pToken->GetFloatToken();
                    pMotionModel->pMotionList[motionLoadCnt].keyframeList[i].keyList[j].trans.y = pToken->GetFloatToken();
                    pMotionModel->pMotionList[motionLoadCnt].keyframeList[i].keyList[j].trans.z = pToken->GetFloatToken();

                    // ROT ��ǂݍ���
                    pToken->GetToken();
                    pToken->GetToken();
                    pMotionModel->pMotionList[motionLoadCnt].keyframeList[i].keyList[j].rot.x = pToken->GetFloatToken();
                    pMotionModel->pMotionList[motionLoadCnt].keyframeList[i].keyList[j].rot.y = pToken->GetFloatToken();
                    pMotionModel->pMotionList[motionLoadCnt].keyframeList[i].keyList[j].rot.z = pToken->GetFloatToken();

                    // END_KEY ��ǂݍ���
                    pToken->GetToken();
                }
                // END_KEYSET ��ǂݍ���
                pToken->GetToken();
            }

            motionLoadCnt++;
        }
    }

    delete pToken;
    delete[] pBuf;

    return pMotionModel;
}

/******************************************************************************
@brief  �X�e�[�W�ǂݍ���
@param  FileName    �t�@�C����
@return Stage       �X�e�[�W���
******************************************************************************/

Stage* TextReader::LoadStage(const char *FileName)
{
    Stage* pStage = NULL;

    // �t�@�C���ǂݍ���
    File file;
    if (!file.Open(FileName, "r"))
    {
        Error::Message("�t�@�C��\"%s\"�̓ǂݍ��݂Ɏ��s���܂����B", FileName);
        return pStage;
    }
    fileSize = file.GetSize();

    // �o�b�t�@�Ƀt�@�C���f�[�^���i�[
    char* pBuf = new char[fileSize + 1];
    pBuf[fileSize] = '\0';
    file.Read(pBuf, fileSize, 1);
    file.Close();

    TokenAnalyzer* pToken = new TokenAnalyzer(pBuf);
    pToken->SetSkipChars(" \t\n\r,;\"");
    pStage = new Stage;

    int modelCount = 0;
    int plantCount = 0;
    
    /**
    * TXT�t�@�C��(�X�e�[�W�X�N���v�g)�ǂݍ���
    * �@ �g�[�N�����擾
    * �A �`�����N���Ƃɕ���
    */

    // �t�@�C����� ////////////////////
    while (!pToken->IsScriptEnd())
    {
        pToken->GetToken();

        // MODELSET
        if (pToken->CheckToken("MODELSET"))
        {
            pToken->GetToken(); pToken->GetToken(); pToken->GetToken();
            pToken->GetToken(); pToken->GetToken(); pToken->GetToken();
            pToken->GetToken(); pToken->GetToken(); pToken->GetToken();
            pToken->GetToken(); pToken->GetToken(); pToken->GetToken();
            pToken->GetToken(); pToken->GetToken();
            modelCount++;
        }

        // PLANTSET
        if (pToken->CheckToken("PLANTSET"))
        {
            pToken->GetToken(); pToken->GetToken(); pToken->GetToken();
            pToken->GetToken(); pToken->GetToken(); pToken->GetToken();
            pToken->GetToken(); pToken->GetToken(); pToken->GetToken();
            pToken->GetToken(); pToken->GetToken(); pToken->GetToken();
            pToken->GetToken();
            plantCount++;
        }
    }

    pStage->modelNum = modelCount;
    pStage->plantNum = plantCount;

    pStage->pModelList = new Model*[modelCount];
    pStage->pPlantList = new Plant*[plantCount];

    modelCount = 0;
    plantCount = 0;

    pToken->Reset();

    // �t�@�C����� ////////////////////
    while (!pToken->IsScriptEnd())
    {
        pToken->GetToken();

//
// �t�B�[���h
// 

        if (pToken->CheckToken("FIELD"))
        {
            pToken->GetToken();
            pToken->GetToken();
            char fileName[256];
            strcpy_s(fileName, 256, pToken->GetToken());

            pToken->GetToken();
            pToken->GetToken();
            float size_x = pToken->GetFloatToken();
            float size_y = pToken->GetFloatToken();

            pToken->GetToken();
            pToken->GetToken();
            int widthDiv  = pToken->GetIntToken();
            int heightDiv = pToken->GetIntToken();

            pToken->GetToken();
            pToken->GetToken();

            File dataFile;
            int dataFileSize;
            if (dataFile.Open(pToken->GetToken(), "r"))
            {
                dataFileSize = file.GetSize();

                // �o�b�t�@�Ƀt�@�C���f�[�^���i�[
                float* pHeightMap = new float[dataFileSize / 4];
                dataFile.Read(pHeightMap, dataFileSize, 1);
                dataFile.Close();

                pStage->pMeshField = new MeshField(fileName, widthDiv, heightDiv, Vector2(size_x, size_y), pHeightMap);
                delete pHeightMap;
            }
            else
            {
                Error::Message("�����}�b�v�̓ǂݍ��݂Ɏ��s���܂����B");
            }

        }
        
//
// ���f��
// 

        if (pToken->CheckToken("MODELSET"))
        {
            pToken->GetToken();
            pToken->GetToken();
            pStage->pModelList[modelCount] = Model::Load(pToken->GetToken());

            pToken->GetToken();
            pToken->GetToken();
            pStage->pModelList[modelCount]->pos_.x = pToken->GetFloatToken();
            pStage->pModelList[modelCount]->pos_.y = pToken->GetFloatToken();
            pStage->pModelList[modelCount]->pos_.z = pToken->GetFloatToken();

            pToken->GetToken();
            pToken->GetToken();
            pStage->pModelList[modelCount]->rot_.x = ToRad(pToken->GetFloatToken());
            pStage->pModelList[modelCount]->rot_.y = ToRad(pToken->GetFloatToken());
            pStage->pModelList[modelCount]->rot_.z = ToRad(pToken->GetFloatToken());

            pToken->GetToken();
            modelCount++;
        }

//
// ����
// 

        if (pToken->CheckToken("PLANTSET"))
        {
            pToken->GetToken();
            pToken->GetToken();
            pStage->pPlantList[plantCount] = Plant::Create(pToken->GetToken(), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f), 0);

            pToken->GetToken();
            pToken->GetToken();
            pStage->pPlantList[plantCount]->SetPolygonNum(pToken->GetIntToken());

            pToken->GetToken();
            pToken->GetToken();
            pStage->pPlantList[plantCount]->pos_.x = pToken->GetFloatToken();
            pStage->pPlantList[plantCount]->pos_.y = pToken->GetFloatToken();
            pStage->pPlantList[plantCount]->pos_.z = pToken->GetFloatToken();

            pToken->GetToken();
            pToken->GetToken();
            pStage->pPlantList[plantCount]->scale_.x = pToken->GetFloatToken();
            pStage->pPlantList[plantCount]->scale_.y = pToken->GetFloatToken();

            pToken->GetToken();
            plantCount++;
        }
    }

    delete pToken;
    delete[] pBuf;

    return pStage;
}

/******************************* �֐������܂� ********************************/

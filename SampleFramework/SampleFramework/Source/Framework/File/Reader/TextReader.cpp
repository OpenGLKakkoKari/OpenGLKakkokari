/*****************************************************************************/
/*!
@file   TextReader.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
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


/*  実装
******************************************************************************/

/******************************************************************************
@brief  モーションモデル読み込み
@param  FileName    ファイル名
@return MotionModel モーションモデル情報
******************************************************************************/

MotionModel* TextReader::LoadMotionModel(const char *FileName)
{
    MotionModel* pMotionModel = NULL;

    // ファイル読み込み
    File file;
    if (!file.Open(FileName, "r"))
    {
        Error::Message("ファイル\"%s\"の読み込みに失敗しました。", FileName);
        return pMotionModel;
    }
    fileSize = file.GetSize();

    // バッファにファイルデータを格納
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
 * TXTファイル(モーションスクリプト)読み込み
 * ① トークンを取得
 * ② チャンクごとに分岐
 */

    // ファイル解析 ////////////////////
    while (!pToken->IsScriptEnd())
    {
        pToken->GetToken();

        // NUM_MODEL
        if (pToken->CheckToken("NUM_MODEL"))
        {
            // = をスキップ
            pToken->GetToken();
            pMotionModel->modelNum = pToken->GetIntToken();
            pMotionModel->pModelList = new Model*[pMotionModel->modelNum];
        }
        // MODEL_FILENAME
        if (pToken->CheckToken("MODEL_FILENAME"))
        {
            // = をスキップ
            pToken->GetToken();
            // ファイル名を取得
            pMotionModel->pModelList[modelLoadCnt] = Model::Load(pToken->GetToken());
            modelLoadCnt++;
        }

        // CHARACTERSET
        if (pToken->CheckToken("CHARACTERSET"))
        {
            // MOVE をスキップ
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();
            // JUMP をスキップ
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();
            // RADIUS をスキップ
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();
            // NUM_PARTS を読込
            pToken->GetToken();
            pToken->GetToken();
            pMotionModel->partsNum = pToken->GetIntToken();
            pMotionModel->pPartsModelList = new Model*[pMotionModel->modelNum];
            pToken->GetToken();
            pToken->GetToken();
        }

        // PARTSSET
        // パーツとモデルの対応関係にバグあり
        if (pToken->CheckToken("PARTSSET"))
        {
            // INDEX を読み込む
            pToken->GetToken();
            pToken->GetToken();
            // モデルをコピー
            pMotionModel->pPartsModelList[partsLoadCnt] = pMotionModel->pModelList[pToken->GetIntToken()];
            pToken->GetToken();
            pToken->GetToken();
            
            // PARENT を読み込む
            pToken->GetToken();
            pToken->GetToken();
            int parentIndex = pToken->GetIntToken();
            if (parentIndex == -1)
                pMotionModel->pPartsModelList[partsLoadCnt]->SetParent(pMotionModel);
            else
                pMotionModel->pPartsModelList[partsLoadCnt]->SetParent(pMotionModel->pPartsModelList[parentIndex]);
            pToken->GetToken();
            pToken->GetToken();
            
            // POS を読み込む
            pToken->GetToken();
            pToken->GetToken();
            pMotionModel->pPartsModelList[partsLoadCnt]->pos_.x = pToken->GetFloatToken();
            pMotionModel->pPartsModelList[partsLoadCnt]->pos_.y = pToken->GetFloatToken();
            pMotionModel->pPartsModelList[partsLoadCnt]->pos_.z = pToken->GetFloatToken();

            // ROT を読み込む
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
            // = を読み込む
            pToken->GetToken();
            pMotionModel->motionNum = pToken->GetIntToken();
            pMotionModel->pMotionList = new Motion[pMotionModel->motionNum];
        }

        // MOTIONSET
        if (pToken->CheckToken("MOTIONSET"))
        {
            // LOOP を読み込む
            pToken->GetToken();
            pToken->GetToken();
            pMotionModel->pMotionList[motionLoadCnt].loop = (pToken->GetIntToken() == 0) ? (false) : (true);
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();

            // NUM_KEY を読み込む
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

            // KEYSET を読み込む
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
                // FRAME を読み込む
                pToken->GetToken();
                pToken->GetToken();
                pMotionModel->pMotionList[motionLoadCnt].keyframeList[i].interval = pToken->GetIntToken();
                // 合計フレームを算出
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
                    // POS を読み込む
                    pToken->GetToken();
                    pToken->GetToken();
                    pMotionModel->pMotionList[motionLoadCnt].keyframeList[i].keyList[j].trans.x = pToken->GetFloatToken();
                    pMotionModel->pMotionList[motionLoadCnt].keyframeList[i].keyList[j].trans.y = pToken->GetFloatToken();
                    pMotionModel->pMotionList[motionLoadCnt].keyframeList[i].keyList[j].trans.z = pToken->GetFloatToken();

                    // ROT を読み込む
                    pToken->GetToken();
                    pToken->GetToken();
                    pMotionModel->pMotionList[motionLoadCnt].keyframeList[i].keyList[j].rot.x = pToken->GetFloatToken();
                    pMotionModel->pMotionList[motionLoadCnt].keyframeList[i].keyList[j].rot.y = pToken->GetFloatToken();
                    pMotionModel->pMotionList[motionLoadCnt].keyframeList[i].keyList[j].rot.z = pToken->GetFloatToken();

                    // END_KEY を読み込む
                    pToken->GetToken();
                }
                // END_KEYSET を読み込む
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
@brief  ステージ読み込み
@param  FileName    ファイル名
@return Stage       ステージ情報
******************************************************************************/

Stage* TextReader::LoadStage(const char *FileName)
{
    Stage* pStage = NULL;

    // ファイル読み込み
    File file;
    if (!file.Open(FileName, "r"))
    {
        Error::Message("ファイル\"%s\"の読み込みに失敗しました。", FileName);
        return pStage;
    }
    fileSize = file.GetSize();

    // バッファにファイルデータを格納
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
    * TXTファイル(ステージスクリプト)読み込み
    * ① トークンを取得
    * ② チャンクごとに分岐
    */

    // ファイル解析 ////////////////////
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

    // ファイル解析 ////////////////////
    while (!pToken->IsScriptEnd())
    {
        pToken->GetToken();

//
// フィールド
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

                // バッファにファイルデータを格納
                float* pHeightMap = new float[dataFileSize / 4];
                dataFile.Read(pHeightMap, dataFileSize, 1);
                dataFile.Close();

                pStage->pMeshField = new MeshField(fileName, widthDiv, heightDiv, Vector2(size_x, size_y), pHeightMap);
                delete pHeightMap;
            }
            else
            {
                Error::Message("高さマップの読み込みに失敗しました。");
            }

        }
        
//
// モデル
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
// 草木
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

/******************************* 関数ここまで ********************************/

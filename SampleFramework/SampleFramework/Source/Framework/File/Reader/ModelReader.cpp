/*****************************************************************************/
/*!
@file   ModelReader.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "ModelReader.h"
#include <crtdbg.h>
#include "../File.h"
#include "../../Error.h"
#include "../../Manager.h"
#include "../../TokenAnalyzer.h"


using namespace Framework;
using namespace Framework::File;


/*  実装
******************************************************************************/


char ModelReader::materialNameList[64][64];


/******************************************************************************
@brief  ファイル読み込み
@param  FileName    ファイル名
@return Mesh*       メッシュ情報
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
@brief  Xファイル読み込み
@param  FileName    ファイル名
@return Mesh*       メッシュ情報
******************************************************************************/

Mesh* ModelReader::LoadX(const char *FileName)
{
    Mesh* pMesh;

    File file;
    if (!file.Open(FileName, "rb"))
    {
        Error::Message("ファイル\"%s\"の読み込みに失敗しました。", FileName);
        return NULL;
    }
    pMesh = new Mesh;
    fileSize = file.GetSize();

    // バッファにファイルデータを格納
    char* pBuf = new char[fileSize + 1];
    pBuf[fileSize] = '\0';
    file.Read(pBuf, fileSize, 1);
    file.Close();

    // 文字列を設定
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
     * Xファイル読み込み
     * ① トークンを取得
     * ② チャンクごとに分岐
     */

    // ファイル解析 ////////////////////
    while (!pToken->IsScriptEnd())
    {

        pToken->GetToken();

        //　templateをスキップ
        if (pToken->CheckToken("template"))
        {
            pToken->SkipBracket();
        }

        //　Meshの場合
        else if (pToken->CheckToken("Mesh"))
        {
            // トークンを取得
            pToken->GetToken();

            // " { " が出るまでループ
            while (!pToken->CheckToken("{"))
            {
                pToken->GetToken();
            }

            // トークンから頂点数を取得
            vertexCount = 0;
            vertexCount = pToken->GetIntToken();

            pPosList = new Vector3[vertexCount];
            for (int i = 0; i < vertexCount; i++)
            { // 頂点情報を取得
                pPosList[i].x = pToken->GetFloatToken();
                pPosList[i].y = pToken->GetFloatToken();
                pPosList[i].z = pToken->GetFloatToken();
            }

            // トークンから面数を取得
            faceCount = 0;
            faceCount = pToken->GetIntToken();

            pIndex = new int[faceCount * 3];
            // トークンから面データを取得
            for (int i = 0; i < faceCount; i++)
            {
                pToken->GetToken();

                pIndex[i * 3 + 0] = pToken->GetIntToken();
                pIndex[i * 3 + 1] = pToken->GetIntToken();
                pIndex[i * 3 + 2] = pToken->GetIntToken();
            }


        }//　MeshMaterialListの場合
        else if (pToken->CheckToken("MeshMaterialList"))
        {
            //　トークン"{"を取得
            pToken->GetToken();

            //　トークンからマテリアル数を取得
            materialCount = 0;
            materialCount = pToken->GetIntToken();

            //　面数をチェック
            int materialFaceCount = pToken->GetIntToken();
            _ASSERT(materialFaceCount == faceCount);

            pMaterialList = new Material[materialCount];
            pSubsetList = new Mesh::Subset[100];

            int mi, oldmi;
            oldmi = pToken->GetIntToken();

            subsetCount = 0;
            pSubsetList[0].startIndex = 0;
            pSubsetList[0].materialIndex = oldmi;

            //　トークンからマテリアルインデックスを取得
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
                // トークン"Material"を取得
                pToken->GetToken();
                // トークン"{"を取得
                pToken->GetToken();

                //　トークンが" { "でない場合
                if (!pToken->CheckToken("{"))
                {
                    //　トークン"{"を取得
                    pToken->GetToken();
                }

                //　Diffuse Color
                pMaterialList[i].diffuse.r = pToken->GetFloatToken();
                pMaterialList[i].diffuse.g = pToken->GetFloatToken();
                pMaterialList[i].diffuse.b = pToken->GetFloatToken();
                pMaterialList[i].diffuse.a = pToken->GetFloatToken();

                //　Ambient Color
                pMaterialList[i].ambient.r = 0.0f;
                pMaterialList[i].ambient.g = 0.0f;
                pMaterialList[i].ambient.b = 0.0f;
                pMaterialList[i].ambient.a = 1.0f;

                //　Shiness
                pMaterialList[i].power = pToken->GetFloatToken();

                //　Specular Color
                pMaterialList[i].specular.r = pToken->GetFloatToken();
                pMaterialList[i].specular.g = pToken->GetFloatToken();
                pMaterialList[i].specular.b = pToken->GetFloatToken();
                pMaterialList[i].specular.a = 1.0f;

                //　Emissive Color
                pMaterialList[i].emissive.r = pToken->GetFloatToken();
                pMaterialList[i].emissive.g = pToken->GetFloatToken();
                pMaterialList[i].emissive.b = pToken->GetFloatToken();
                pMaterialList[i].emissive.a = 1.0f;

                // トークンを取得
                pToken->GetToken();
                pMaterialList[i].pTexture = 0;

                // TextureFileNameの場合
                if (pToken->CheckToken("TextureFilename"))
                {
                    // トークン"{"を取得
                    pToken->GetToken();

                    // ファイル名をセット
                    pMaterialList[i].pTexture = Texture::Load(pToken->GetToken());

                    // トークン"を取得
                    pToken->GetToken();
                    // トークン"}"を取得
                    pToken->GetToken();
                }
            }
        }
        //　MeshNormalsの場合
        else if (pToken->CheckToken("MeshNormals"))
        {
            // トークン"{"を取得
            pToken->GetToken();

            // トークンから法線数を取得
            normalCount = 0;
            normalCount = pToken->GetIntToken();

            pNormalList = new Vector3[normalCount];

            // トークンから法線データを取得
            for (int i = 0; i < normalCount; i++)
            {
                pNormalList[i].x = pToken->GetFloatToken();
                pNormalList[i].y = pToken->GetFloatToken();
                pNormalList[i].z = pToken->GetFloatToken();
            }

            //　面数をチェック
            int normFaceCount = pToken->GetIntToken();
            pNormalIndex = new int[normFaceCount * 3];
            for (int i = 0; i < normFaceCount; i++)
            {
                // トークンを取得
                pToken->GetToken();

                pNormalIndex[i * 3 + 0] = pToken->GetIntToken();
                pNormalIndex[i * 3 + 1] = pToken->GetIntToken();
                pNormalIndex[i * 3 + 2] = pToken->GetIntToken();
            }

        }
        //　MeshTextureCoordsの場合
        else if (pToken->CheckToken("MeshTextureCoords"))
        {
            //　トークン"{"を取得
            pToken->GetToken();

            //　トークンからテクスチャ座標数を取得
            uvCount = 0;
            uvCount = pToken->GetIntToken();
            pTexList = new Vector2[uvCount];

            for (int i = 0; i < uvCount; i++)
            { // テクスチャ座標を挿入
                pTexList[i].x = pToken->GetFloatToken();
                pTexList[i].y = pToken->GetFloatToken();
            }
        }
    }
    delete pToken;

    // バッファ開放
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
@brief  OBJファイル読み込み
@param  FileName    ファイル名
@return Mesh*       メッシュ情報
******************************************************************************/

Mesh* ModelReader::LoadOBJ(const char *FileName)
{
    Mesh* pMesh;

    File file;
    if (!file.Open(FileName, "rb"))
    {
        Error::Message("ファイル\"%s\"の読み込みに失敗しました。", FileName);
        return NULL;
    }
    pMesh = new Mesh;
    fileSize = file.GetSize();

    // バッファにファイルデータを格納
    char* pBuf = new char[fileSize + 1];
    pBuf[fileSize] = '\0';
    file.Read(pBuf, fileSize, 1);
    file.Close();

    // 文字列を設定
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
 * OBJファイル読み込み
 * ① 頂点数を取得
 * ② チャンクごとに分岐
 */

    // ファイル解析 ////////////////////
    while (!pToken->IsScriptEnd())
    {

        pToken->GetToken();

        // mtllibを読み込む
        if (pToken->CheckToken("mtllib"))
        {
            // ファイル名読み込み
            LoadMTL(pToken->GetToken(), &pMesh->materialNum, &pMesh->pMaterialList);
        }

        // 面数を読み込む
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
        //頂点座標数をリストに読み込む
        else if (pToken->CheckToken("v"))
        {
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();

            vertexCount++;
        }
        // 頂点UV座標数をリストに読み込む
        else if (pToken->CheckToken("vt"))
        {
            pToken->GetToken();
            pToken->GetToken();

            uvCount++;
        }
        // 頂点法線数をリストに読み込む
        else if (pToken->CheckToken("vn"))
        {
            pToken->GetToken();
            pToken->GetToken();
            pToken->GetToken();

            normalCount++;
        }
        // サブセット数を読み込む
        else if (pToken->CheckToken("usemtl"))
        {
            pToken->GetToken();
            subsetCount++;
        }
    }

    // カーソルを元に戻す
    pToken->Reset();

    // バッファを確保
    pPosList = new Vector3[vertexCount];
    pTexList = new Vector2[uvCount];
    pNormalList = new Vector3[normalCount];

    // 領域を確保
    pMesh->pSubsetList = new Mesh::Subset[subsetCount];
    pMesh->pVertex     = new Vertex[faceCount * 3];
    pMesh->pIndexList  = new int[faceCount * 3];

    // 数値代入
    pMesh->faceNum = faceCount;
    pMesh->vertexNum = faceCount * 3;
    pMesh->subsetNum = subsetCount;

    for (int i = 0; i < faceCount; i++)
    {
        pMesh->pIndexList[i * 3 + 0] = i * 3 + 0;
        pMesh->pIndexList[i * 3 + 1] = i * 3 + 1;
        pMesh->pIndexList[i * 3 + 2] = i * 3 + 2;
    }

    // カウンタをリセット
    subsetCount = 0;
    faceCount = 0;
    vertexCount = 0;
    normalCount = 0;
    uvCount = 0;
    int posCount = 0;

    // ファイル解析 ////////////////////
    while (!pToken->IsScriptEnd())
    {

        pToken->GetToken();

        //頂点座標数をリストに読み込む
        if (pToken->CheckToken("v"))
        {
            pPosList[posCount].x = pToken->GetFloatToken();
            pPosList[posCount].y = pToken->GetFloatToken();
            pPosList[posCount].z = pToken->GetFloatToken();

            posCount++;
        }
        //頂点UV座標数をリストに読み込む
        if (pToken->CheckToken("vt"))
        {
            pTexList[uvCount].x = pToken->GetFloatToken();
            pTexList[uvCount].y = pToken->GetFloatToken();

            uvCount++;
        }
        //頂点法線数をリストに読み込む
        if (pToken->CheckToken("vn"))
        {
            pNormalList[normalCount].x = pToken->GetFloatToken();
            pNormalList[normalCount].y = pToken->GetFloatToken();
            pNormalList[normalCount].z = pToken->GetFloatToken();

            normalCount++;
        }

        // サブセット単位で読み込む
        else if (pToken->CheckToken("usemtl"))
        {
            pMesh->pSubsetList[subsetCount].materialIndex = GetMaterialIndex(pToken->GetToken());
            pMesh->pSubsetList[subsetCount].startIndex = vertexCount;
            faceCount = 0;

            // トークン"f"を読み込む
            pToken->GetToken();

            //　面数を読み込む
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

                // 次のトークンを読み込む
                pToken->GetToken();

            }
            pMesh->pSubsetList[subsetCount].count = faceCount;
            subsetCount++;
        }

    }
    delete pToken;

    // バッファ開放
    delete[] pPosList;
    delete[] pTexList;
    delete[] pNormalList;

    delete[] pBuf;

    return pMesh;
}

/******************************************************************************
@brief  MTLファイル読み込み
@param  FileName    ファイル名
@param  pMatNum     マテリアル数
@param  pMatList    マテリアルリスト
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
        Error::Message("ファイル\"%s\"の読み込みに失敗しました。", FileName);
        return;
    }
    fileSize = file.GetSize();

    // バッファにファイルデータを格納
    char* pBuf = new char[fileSize + 1];
    pBuf[fileSize] = '\0';
    file.Read(pBuf, fileSize, 1);
    file.Close();

    TokenAnalyzer* pToken = new TokenAnalyzer(pBuf);

    Material        *pMatBuf = nullptr;
    int materialCnt = 0;

    // バッファを確保
    pMatBuf = new Material[100];

    
/**
 * MTLファイル読み込み
 * ① トークンを取得
 * ② チャンクごとに分岐
 */

    // ファイル解析 ////////////////////
    while (!pToken->IsScriptEnd())
    {
        pToken->GetToken();

        //　マテリアルを読み込む
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

    // 取得したマテリアル情報を設定
    *pMatNum = materialCnt;
    *pMatList = new Material[materialCnt];
    memcpy(*pMatList, pMatBuf, sizeof(Material) * materialCnt);
    
    // バッファ開放
    delete[] pBuf;
    delete[] pMatBuf;

}

/******************************************************************************
@brief  マテリアル名をインデックスに変換
@param  MaterialName        マテリアル名
@return int                 インデックス
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

/******************************* 関数ここまで ********************************/

#pragma once
/*****************************************************************************/
/*!
@file   EffectData.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "..\Math\Vector3.h"
#include "..\Color.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{

    struct EffectDataHeader
    {
        int             majorVer;           // メジャーバージョン
        int             minorVer;           // マイナーバージョン
        int             dataSize;           // データ部のサイズ
        int             nodeNum;            // ノード数
        int             frameStart;         // 開始フレーム
        int             frameEnd;           // 終了フレーム
    };
    struct EffectData
    {
        int             siblingIndex;       // 同階層のインデックス
        int             childIndex;         // 子供のインデックス

        bool            draw;               // 描画するかどうか
        bool            lifeDelete;         // 寿命で削除

        int             createNum;          // 生成数
        int             lifeMin;            // 最小寿命
        int             lifeMax;            // 最大寿命
        int             createIntervalMin;  // 最小生成間隔
        int             createIntervalMax;  // 最大生成間隔
        int             createStartMin;     // 最小生成開始時間
        int             createStartMax;     // 最大生成開始時間

        Vector3         posMin;             // 最小座標
        Vector3         posMax;             // 最大座標
        Vector3         posVelMin;          // 最小移動速度
        Vector3         posVelMax;          // 最大移動速度
        Vector3         posAccelMin;        // 最小移動加速度
        Vector3         posAccelMax;        // 最大移動加速度

        Vector3         rotMin;             // 最小角度
        Vector3         rotMax;             // 最大角度
        Vector3         rotVelMin;          // 最小回転速度
        Vector3         rotVelMax;          // 最大回転速度
        Vector3         rotAccelMin;        // 最小回転加速度
        Vector3         rotAccelMax;        // 最大回転加速度


        Vector3         sclMin;             // 最小スケール
        Vector3         sclMax;             // 最大スケール
        Vector3         sclVelMin;          // 最小拡縮速度
        Vector3         sclVelMax;          // 最大拡縮速度
        Vector3         sclAccelMin;        // 最小拡縮加速度
        Vector3         sclAccelMax;        // 最大拡縮加速度

        Color           startColorMin;      // 開始最小色
        Color           startColorMax;      // 開始最大色
        Color           endColorMin;        // 終了最小色
        Color           endColorMax;        // 終了最大色

        //Particle::TYPE  particleType;       // パーティクルの種類
        int             optionType;         // オプションの種類
        char            fileName[256];      // ファイル名

        int             blendType;          // ブレンド方法
        bool            depthWrite;         // 深度バッファ書込
        bool            depthTest;          // 深度テスト

        EffectData() :
            siblingIndex(0), childIndex(0), draw(true), createNum(1), lifeMin(100), lifeMax(100),
            createIntervalMin(1), createIntervalMax(1), createStartMin(0), createStartMax(0),
            sclMin(Vector3(10.0f, 10.0f, 10.0f)), sclMax(Vector3(10.0f, 10.0f, 10.0f)),
            startColorMin(Color(255, 255, 255, 255)), startColorMax(Color(255, 255, 255, 255)),
            endColorMin(Color(255, 255, 255, 255)), endColorMax(Color(255, 255, 255, 255)),
            optionType(0), blendType(0), depthWrite(0), depthTest(0)
        {}

    };
}


/****************************** ヘッダここまで *******************************/

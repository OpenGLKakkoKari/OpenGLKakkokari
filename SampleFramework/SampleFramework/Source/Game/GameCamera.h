#pragma once
/******************************************************************************
/*!
@file   GameCamera.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/


/*  インクルード
******************************************************************************/


#include "../Framework/Camera.h"


/*  クラス定義
******************************************************************************/


namespace Game
{
    class GameCamera : public Framework::Camera
    {
    public:
        GameCamera();
        ~GameCamera();

        void Init();
        void Uninit();
        void Update();

        Framework::Vector3 GetRotation(){ return rot; }

        Framework::Vector3 distEyetoModel; // 視点からモデルまでの距離
        Framework::Vector3 distModeltoAt;  // モデルから注視点までの距離
        
        Framework::Vector3 rot;            // カメラの向き
        float              fDistance;      // 距離
        Framework::Vector3 rotAim;         // カメラの目標角度
        Framework::Vector3 rotVec;         // カメラの角移動量
        Framework::Vector3 rotIner;        // カメラの慣性量
        Framework::Vector3 rotUnit;        // カメラの単位回転量
        
        Framework::Vector3 traEyeAim;      // 視点目標座標
        Framework::Vector3 traEyeVec;      // 視点移動量
        Framework::Vector3 traEyeIner;     // 視点慣性量
        Framework::Vector3 traEyeUnit;     // 視点単位移動量
        
        Framework::Vector3 traAtAim;       // 注視点目標座標
        Framework::Vector3 traAtVec;       // 注視点移動量
        Framework::Vector3 traAtIner;      // 注視点慣性量
        Framework::Vector3 traAtUnit;      // 注視点単位移動量

    };

}


/******************************* ヘッダここまで ******************************/

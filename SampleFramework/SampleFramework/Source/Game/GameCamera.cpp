/*****************************************************************************/
/*!
@file   GameCamera.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "GameCamera.h"
#include "../Game/GameScene.h"
#include "../Game/Character/Player.h"
#include "../Framework/Manager.h"
#include "../Framework/Math/Math.h"


using namespace Game;
using namespace Framework;
using namespace Framework::Math;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/

GameCamera::GameCamera()
{
    distModeltoAt = Vector3(0.0f, 130.0f, 0.0f);
    distEyetoModel = Vector3(0.0f, 200.0f, 200.0f);

    rot = Vector3(0.0f, 0.0f, 0.0f);
    rotAim = Vector3(0.0f, 0.0f, 0.0f);
    rotVec = Vector3(0.0f, 0.0f, 0.0f);
    rotIner = Vector3(0.95f, 0.95f, 0.95f);
    rotUnit = Vector3(0.0f, 0.0f, 0.0f);

    traEyeAim = Vector3(0.0f, 140.0f, -200.0f);
    traEyeVec = Vector3(0.0f, 0.0f, 0.0f);
    traEyeIner = Vector3(0.95f, 0.95f, 0.95f);
    traEyeUnit = Vector3(0.0f, 40.0f, 0.0f);

    traAtAim = Vector3(0.0f, 0.0f, 0.0f);
    traAtVec = Vector3(0.0f, 0.0f, 0.0f);
    traAtIner = Vector3(0.9f, 0.9f, 0.9f);
    traAtUnit = Vector3(0.0f, 40.0f, 0.0f);

    // トゥイーカに登録
    Manager::GetDebug()->Add("Camera");
    Manager::GetDebug()->SetDirectory("Camera");
    Manager::GetDebug()->Add("Eye", &Eye);
    Manager::GetDebug()->Add("At", &At);
    Manager::GetDebug()->Add("Up", &Up);
    Manager::GetDebug()->Add("distEyetoModel", &distEyetoModel);
    Manager::GetDebug()->Add("distModeltoAt", &distModeltoAt);
    Manager::GetDebug()->Add("rot", &rot);
    Manager::GetDebug()->Add("rotAim", &rotAim);
    Manager::GetDebug()->Add("rotVec", &rotVec);
    Manager::GetDebug()->Add("rotIner", &rotIner);
    Manager::GetDebug()->Add("rotUnit", &rotUnit);

    Manager::GetDebug()->Add("traEyeAim", &traEyeAim);
    Manager::GetDebug()->Add("traEyeVec", &traEyeVec);
    Manager::GetDebug()->Add("traEyeIner", &traEyeIner);
    Manager::GetDebug()->Add("traEyeUnit", &traEyeUnit);

    Manager::GetDebug()->Add("traAtAim", &traAtAim);
    Manager::GetDebug()->Add("traAtVec", &traAtVec);
    Manager::GetDebug()->Add("traAtIner", &traAtIner);
    Manager::GetDebug()->Add("traAtUnit", &traAtUnit);
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

GameCamera::~GameCamera()
{
    Manager::GetDebug()->Delete("Camera");
}

/******************************************************************************
@brief  初期化処理
******************************************************************************/

void GameCamera::Init(void)
{
}

/******************************************************************************
@brief  終了処理
******************************************************************************/

void GameCamera::Uninit(void)
{
}

/******************************************************************************
@brief  更新処理
******************************************************************************/

void GameCamera::Update(void)
{
//試作
	//プレイヤーデータ(位置、角度)を受け取り
    Vector3 posModel = GameScene::GetCharacter(0)->GetPosition();
    Vector3 rotModel = GameScene::GetCharacter(0)->GetRotation();
    Vector3 traVecModel = GameScene::GetCharacter(0)->traVec;
    Vector3 rotAimModel = GameScene::GetCharacter(0)->rotAim;

    /*
    * 視点移動
    */

    // 上移動
    if (Manager::GetKeyboard()->Press('Y'))
        distEyetoModel.y += 1.0f;
    // 下移動
    if (Manager::GetKeyboard()->Press('N'))
        distEyetoModel.y -= 1.0f;

    /*
    * 注視点移動
    */

    // 上移動
    if (Manager::GetKeyboard()->Press(VK_UP))
        distModeltoAt.y += 1.0f;
    // 下移動
    if (Manager::GetKeyboard()->Press(VK_DOWN))
        distModeltoAt.y -= 1.0f;
    // 右移動
    if (Manager::GetKeyboard()->Press(VK_RIGHT))
    // 左移動
    if (Manager::GetKeyboard()->Press(VK_LEFT))

    ///*
    //* その他操作
    //*/

    // 視点と注視点の距離調整
    if (Manager::GetKeyboard()->Press('U'))
    {
        distEyetoModel.y -= 1.0f;
        distEyetoModel.z += 3.0f;
    }
    if (Manager::GetKeyboard()->Press('M'))
    {
        distEyetoModel.y += 1.0f;
        distEyetoModel.z -= 3.0f;
    }

    // 注視点とモデルの単位距離から注視点の移動量を算出
    distModeltoAt.x = -sinf(rotModel.y) * 12.5f;
    distModeltoAt.z = -cosf(rotModel.y) * 12.5f;

    // 注視点目標をモデルから一定距離離れた地点に設定
    traAtAim.x = posModel.x + distModeltoAt.x + traVecModel.x * 10.0f;
    traAtAim.y = posModel.y + distModeltoAt.y + traVecModel.y * 10.0f;
    traAtAim.z = posModel.z + distModeltoAt.z + traVecModel.z * 10.0f;

    // 視点回転目標をモデル逆方向に設定
    rotAim.y = rotAimModel.y;

    traEyeAim.x = (posModel.x + sinf(rot.y) * distEyetoModel.z) + traVecModel.x;
    traEyeAim.y = (posModel.y + distEyetoModel.y + traVecModel.y);
    traEyeAim.z = (posModel.z + cosf(rot.y) * distEyetoModel.z) + traVecModel.z;

    // 移動量を算出
    traAtVec.x = traAtAim.x - At.x;
    traAtVec.y = traAtAim.y - At.y;
    traAtVec.z = traAtAim.z - At.z;

    traEyeVec.x = traEyeAim.x - Eye.x;
    traEyeVec.y = traEyeAim.y - Eye.y;
    traEyeVec.z = traEyeAim.z - Eye.z;

    rotVec.x = rotAim.x - rot.x;
    rotVec.y = rotAim.y - rot.y;
    rotVec.z = rotAim.z - rot.z;

    if (rotVec.y > _PI)
        rotVec.y -= _2PI;
    else if (rotVec.y < -_PI)
        rotVec.y += _2PI;

    // 慣性をかける
    traAtVec.x += -traAtVec.x * traAtIner.x;
    traAtVec.y += -traAtVec.y * traAtIner.y;
    traAtVec.z += -traAtVec.z * traAtIner.z;

    traEyeVec.x += -traEyeVec.x * traEyeIner.x;
    traEyeVec.y += -traEyeVec.y * traEyeIner.y;
    traEyeVec.z += -traEyeVec.z * traEyeIner.z;

    rotVec.x += -rotVec.x * rotIner.x;
    rotVec.y += -rotVec.y * rotIner.y;
    rotVec.z += -rotVec.z * rotIner.z;

    // 移動量を現在の座標に反映
    At.x += traAtVec.x;
    At.y += traAtVec.y;
    At.z += traAtVec.z;

    Eye.x = posModel.x + sinf(rot.y) * distEyetoModel.z;
    Eye.y = posModel.y + distEyetoModel.y;
    Eye.z = posModel.z + cosf(rot.y) * distEyetoModel.z;

    rot.x += rotVec.x;
    rot.y += rotVec.y;
    rot.z += rotVec.z;

    /*
    * 範囲調整
    */

    // 角度を範囲内に収める
    if (rot.y > _PI)
    {
        rot.y -= _2PI;
    }
    if (rot.y < -_PI)
    {
        rot.y += _2PI;
    }
    // 角度を範囲内に収める
    if (rotAim.y > _PI)
    {
        rotAim.y -= _2PI;
    }
    if (rotAim.y < -_PI)
    {
        rotAim.y += _2PI;
    }

//べース
	////プレイヤーデータ(位置、角度)を受け取り
    //Vector3 posModel = GameScene::GetCharacter(0)->GetPosition();
    //Vector3 rotModel = GameScene::GetCharacter(0)->GetRotation();
    //Vector3 traVecModel = GameScene::GetCharacter(0)->traVec;
    //Vector3 rotAimModel = GameScene::GetCharacter(0)->rotAim;

 //   /*
 //   * 視点移動
 //   */

 //   // 上移動
 //   if (Manager::GetKeyboard()->Press('Y'))
 //       distEyetoModel.y += 1.0f;
 //   // 下移動
 //   if (Manager::GetKeyboard()->Press('N'))
 //       distEyetoModel.y -= 1.0f;

 //   /*
 //   * 注視点移動
 //   */

 //   // 上移動
 //   if (Manager::GetKeyboard()->Press('T'))
 //       distModeltoAt.y += 1.0f;
 //   // 下移動
 //   if (Manager::GetKeyboard()->Press('B'))
 //       distModeltoAt.y -= 1.0f;

 //   ///*
 //   //* その他操作
 //   //*/

 //   // 視点と注視点の距離調整
 //   if (Manager::GetKeyboard()->Press('U'))
 //   {
 //       distEyetoModel.y -= 1.0f;
 //       distEyetoModel.z += 3.0f;
 //   }
 //   if (Manager::GetKeyboard()->Press('M'))
 //   {
 //       distEyetoModel.y += 1.0f;
 //       distEyetoModel.z -= 3.0f;
 //   }

 //   // 注視点とモデルの単位距離から注視点の移動量を算出
 //   distModeltoAt.x = -sinf(rotModel.y) * 12.5f;
 //   distModeltoAt.z = -cosf(rotModel.y) * 12.5f;

 //   // 注視点目標をモデルから一定距離離れた地点に設定
 //   traAtAim.x = posModel.x + distModeltoAt.x + traVecModel.x * 10.0f;
 //   traAtAim.y = posModel.y + distModeltoAt.y + traVecModel.y * 10.0f;
 //   traAtAim.z = posModel.z + distModeltoAt.z + traVecModel.z * 10.0f;

 //   // 視点回転目標をモデル逆方向に設定
 //   rotAim.y = rotAimModel.y;

 //   traEyeAim.x = (posModel.x + sinf(rot.y) * distEyetoModel.z) + traVecModel.x;
 //   traEyeAim.y = (posModel.y + distEyetoModel.y + traVecModel.y);
 //   traEyeAim.z = (posModel.z + cosf(rot.y) * distEyetoModel.z) + traVecModel.z;

 //   // 移動量を算出
 //   traAtVec.x = traAtAim.x - At.x;
 //   traAtVec.y = traAtAim.y - At.y;
 //   traAtVec.z = traAtAim.z - At.z;

 //   traEyeVec.x = traEyeAim.x - Eye.x;
 //   traEyeVec.y = traEyeAim.y - Eye.y;
 //   traEyeVec.z = traEyeAim.z - Eye.z;

 //   rotVec.x = rotAim.x - rot.x;
 //   rotVec.y = rotAim.y - rot.y;
 //   rotVec.z = rotAim.z - rot.z;

 //   if (rotVec.y > _PI)
 //       rotVec.y -= _2PI;
 //   else if (rotVec.y < -_PI)
 //       rotVec.y += _2PI;

 //   // 慣性をかける
 //   traAtVec.x += -traAtVec.x * traAtIner.x;
 //   traAtVec.y += -traAtVec.y * traAtIner.y;
 //   traAtVec.z += -traAtVec.z * traAtIner.z;

 //   traEyeVec.x += -traEyeVec.x * traEyeIner.x;
 //   traEyeVec.y += -traEyeVec.y * traEyeIner.y;
 //   traEyeVec.z += -traEyeVec.z * traEyeIner.z;

 //   rotVec.x += -rotVec.x * rotIner.x;
 //   rotVec.y += -rotVec.y * rotIner.y;
 //   rotVec.z += -rotVec.z * rotIner.z;

 //   // 移動量を現在の座標に反映
 //   At.x += traAtVec.x;
 //   At.y += traAtVec.y;
 //   At.z += traAtVec.z;

 //   Eye.x = posModel.x + sinf(rot.y) * distEyetoModel.z;
 //   Eye.y = posModel.y + distEyetoModel.y;
 //   Eye.z = posModel.z + cosf(rot.y) * distEyetoModel.z;

 //   rot.x += rotVec.x;
 //   rot.y += rotVec.y;
 //   rot.z += rotVec.z;

 //   /*
 //   * 範囲調整
 //   */

 //   // 角度を範囲内に収める
 //   if (rot.y > _PI)
 //   {
 //       rot.y -= _2PI;
 //   }
 //   if (rot.y < -_PI)
 //   {
 //       rot.y += _2PI;
 //   }
 //   // 角度を範囲内に収める
 //   if (rotAim.y > _PI)
 //   {
 //       rotAim.y -= _2PI;
 //   }
 //   if (rotAim.y < -_PI)
 //   {
 //       rotAim.y += _2PI;
 //   }

}

/******************************** 実装ここまで *******************************/

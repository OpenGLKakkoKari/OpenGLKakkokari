/*****************************************************************************/
/*!
@file   Computer.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Computer.h"
#include "../../Framework/Manager.h"
#include "../../Framework/StateManager.h"
#include "../../Framework/Collision/OBB.h"
#include "../../Framework/Math/Math.h"
#include "../../Framework/Mesh/SkinMeshModel.h"
#include "../GameScene.h"


using Game::Computer;
using Framework::Model;
using Framework::Vector2;
using Framework::Vector3;
using Framework::Color;
using Framework::Manager;
using namespace Framework;
using namespace Framework::Math;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

Computer::Computer()
{
    pSkinMeshModel_ = SkinMeshModel::Load("data/MODEL/jk_master3.model");
    pSkinMeshModel_->SetMotion(Motion::WALKING);

    pos_ = Vector3(0.0f, 0.0f, 0.0f);

    pSkinMeshModel_->SetFrame(0);
    pSkinMeshModel_->SetPosition(pos_);
    pSkinMeshModel_->SetRotation(rot_);
    pSkinMeshModel_->SetScale(scale_);
    pSkinMeshModel_->Update();

    // �g�D�C�[�J�ɓo�^
    Manager::GetDebug()->Add("Game/Computer");
    Manager::GetDebug()->SetDirectory("Game/Computer");
    Manager::GetDebug()->Add("pos", &pSkinMeshModel_->pos_);
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

Computer::~Computer()
{
}

/******************************************************************************
@brief  �X�V����
******************************************************************************/

void Computer::Update(void)
{
    pos_.z -= 0.1f;

    pSkinMeshModel_->SetPosition(pos_);
    pSkinMeshModel_->SetRotation(rot_);
    pSkinMeshModel_->SetScale(scale_);

    //pSkinMeshModel->NextFrame();
    //pSkinMeshModel->Update();
}

/******************************** ���������܂� *******************************/

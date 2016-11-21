/******************************************************************************
/*!
@file   Skybox.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Skybox.h"
#include "GameScene.h"
#include "Character/Player.h"
#include "../Framework/Manager.h"
#include "../Framework/Mesh/Model.h"
#include "../Framework/Math/Math.h"


using namespace Game;
using namespace Framework;
using namespace Framework::Math;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

Skybox::Skybox() : pBox(NULL)
{
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

Skybox::~Skybox()
{
    SAFE_DELETE(pBox);
}

/******************************************************************************
@brief  ����������
******************************************************************************/

void Skybox::Init(void)
{
    pBox = SkyboxModel::Load("data/MODEL/skydome.x");
    //pBox = SkyboxModel::CreateSkybox(Vector3(20000.0f, 20000.0f, 20000.0f));
}

/******************************************************************************
@brief  �X�V����
******************************************************************************/

void Skybox::Update(void)
{
    rot_.y += ToRad(0.015f);
    //pBox->SetRotation(rot_);

    Player* pPlayer = reinterpret_cast<Player*>(GameScene::GetCharacter(0));
    Vector3 playerPos = pPlayer->GetPosition();
    pBox->SetPosition(playerPos);
}

/******************************************************************************
@brief  �X�J�C�{�b�N�X�쐬
@param  FileName        �e�N�X�`���̃t�@�C����
@return Skybox*         ���������X�J�C�{�b�N�X
******************************************************************************/

Skybox* Skybox::Create(const char* FileName)
{
    Skybox* pSkybox = new Skybox;
    pSkybox->Init();
    //pSkybox->SetTexture(FileName);
    return pSkybox;
}

/******************************** ���������܂� *******************************/
/*****************************************************************************/
/*!
@file   GameScene.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "GameScene.h"
#include "GameCamera.h"
#include "Character/Player.h"
#include "Character/Computer.h"
#include "MeshField.h"
#include "Plant.h"
#include "../Title/TitleScene.h"
#include "../Framework/Manager.h"
#include "../Framework/File/Reader/EffectReader.h"
#include "../Framework/File/Reader/TextReader.h"
#include "../Framework/Math/Random.h"
#include "../Framework/Math/Math.h"
#include "../Framework/Sprite.h"
#include "../Framework/Effect/Effect.h"


using namespace Framework;
using namespace Game;
using namespace Framework::File;
using namespace Math;


/*  �ÓI�ϐ��錾
******************************************************************************/


GameCamera*                 Game::GameScene::pCamera;
Character**                 Game::GameScene::pCharacter;
Framework::Stage*           Game::GameScene::pStage;
Framework::Sprite*          Game::GameScene::pBackground;
Framework::Polygon*         Game::GameScene::pPolygon;
Framework::Effect*          Game::GameScene::pEffect;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

GameScene::GameScene()
{
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

GameScene::~GameScene()
{
}

/******************************************************************************
@brief  ������
******************************************************************************/

void GameScene::Init(void)
{
    pStage = TextReader::LoadStage("data/SCRIPT/stage1.txt");

    //pMeshfield = new MeshField(16, 16);
    //pGrass = Grass::Create("data/TEXTURE/grass512.png", Vector3(0.0f, 25.0f, 300.0f), Vector2(100.0f, 50.0f));

    pCamera = new GameCamera;
    Manager::GetRenderer()->SetCamera(pCamera);


    pCharacter = new Character*[CHARACTER_MAX];
    pCharacter[0] = new Player;
    pCharacter[1] = new Computer;

    pBackground = Sprite::Create(
        // ���W
        Vector2((float)Manager::GetWindow()->GetWidth() / 16 * 8, (float)Manager::GetWindow()->GetHeight() / 16),
        // �傫��
        Vector2((float)Manager::GetWindow()->GetWidth() / 4, (float)Manager::GetWindow()->GetHeight() / 8),
        // �F
        Color(255, 255, 255, 255),
        // �e�N�X�`���t�@�C����
        "data/TEXTURE/Game/score_logo.png");

    pPolygon = Polygon::Create(
        Vector3(0.0f, 0.0f, -50.0f),
        Vector2(100.0f, 100.0f),
        Color(255, 0, 0, 255),
        // �e�N�X�`���t�@�C����
        "data/TEXTURE/Game/score_logo.png");
    
    pPolygon->SetType(DrawObject::TYPE_ALPHAMESH);

    pEffect = EffectReader::LoadEffect("data/EFFECT/explosion.effect");
    pEffect->Pause();
    pEffect->SetLoop(true);
    pEffect->SetPosition(Vector3(0.0f, 0.0f, 1000.0f));


    Manager::GetDebug()->Add("Game");
}

/******************************************************************************
@brief  �I������
******************************************************************************/

void GameScene::Uninit(void)
{
    SAFE_DELETE(pCamera);
    
    for (int i = 0; i < 2; i++)
    {
        SAFE_DELETE(pCharacter[i]);
    }
    SAFE_DELETE_ARRAY(pCharacter);

    SAFE_DELETE(pStage);
    SAFE_DELETE(pBackground);
    SAFE_DELETE(pPolygon);
    SAFE_DELETE(pEffect);
    Manager::GetSound()->Stop();
    Manager::GetDebug()->Delete("Game");
}

/******************************************************************************
@brief  �X�V����
******************************************************************************/

void GameScene::Update(void)
{

    if (Manager::GetKeyboard()->Trigger('9'))
    {
        TitleScene *pTitleScene = new TitleScene;
        Manager::SetFade(Fade::FADE_OUT, pTitleScene);
    }
    if (Manager::GetKeyboard()->Trigger('1'))
    {
        pEffect->Play();
    }
}

/******************************** ���������܂� *******************************/

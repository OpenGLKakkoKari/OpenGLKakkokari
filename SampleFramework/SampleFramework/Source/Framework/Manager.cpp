/*****************************************************************************/
/*!
@file   Manager.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Manager.h"
#include "Fps.h"

#include "../OpenGL/OpenGLRenderer.h"
#include "../OpenGL/OpenGLTextureFactory.h"

#include "../DirectX/DirectXRenderer.h"
#include "../DirectX/DirectXTextureFactory.h"

#include "../Game/GameScene.h"
#include "DrawObject.h"


using namespace Framework::Input;
using namespace Framework;
using namespace Windows;


/*  �}�N����`
******************************************************************************/


#define SCREEN_WIDTH (1280)
#define SCREEN_HEIGHT (960)
#define WINDOW_MODE (true)


/*  �ÓI�ϐ��錾
******************************************************************************/


LPSTR                           OpenGLTitle  = "MultiPlatform(OpenGL)";
LPSTR                           DirectXTitle = "MultiPlatform(DirectX)";

Windows::GameWindow*            Manager::pGameWindow;
Windows::MainController*        Manager::pMainController;
Framework::Renderer*            Manager::pRenderer;
Framework::Input::Keyboard*     Manager::pKeyboard;
Framework::Input::Joystick*     Manager::pJoystick;
Framework::Error*               Manager::pError;

Framework::Light*               Manager::pLight[3];

Framework::SoundManager*        Manager::pSoundManager;
Framework::TextureFactory*      Manager::pTextureFactory;

Framework::SceneManager*        Manager::pSceneManager;
Framework::Fade*                Manager::fade;

Framework::Debug*               Manager::pDebug;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  ����������
@param  hInstance   �C���X�^���X�n���h��
******************************************************************************/

void Manager::Init(HINSTANCE hInstance)
{

    // FPS��ݒ�
    Fps::SetFPS(60);

    // �E�C���h�E�̐���
    pMainController = new MainController;
    pGameWindow = new GameWindow();
    pGameWindow->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    pGameWindow->SetWindowStyle(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);
    pGameWindow->FullScreen(false);
    if (FAILED(pGameWindow->Create(hInstance, "TripleCross", NULL, pMainController)))
        return;
    pGameWindow->Show();

    ///*
    //pGameWindow->Set(OpenGLTitle);
    // �����_���[�̏�����
    pRenderer = new OpenGL::Renderer();
    pRenderer->Init(pGameWindow);

    // �e�N�X�`���[�t�@�N�g���[�̏�����
    pTextureFactory = new OpenGL::TextureFactory;
    Texture::RegisterFactory(pTextureFactory);

    //*/

    /*
    //pGameWindow->SetTitle(DirectXTitle);
    // �����_���[�̏�����
    pRenderer = new DirectX::Renderer();
    pRenderer->Init(pGameWindow);

    // �e�N�X�`���[�t�@�N�g���[�̏�����
    DirectX::Renderer* pDirectXRenderer = (DirectX::Renderer*)pRenderer;
    pTextureFactory = new DirectX::TextureFactory(pDirectXRenderer->GetDevice());
    Texture::RegisterFactory(pTextureFactory);

    //*/

    // �G���[�����̏�����
    pError = new Error;
    pError->Init(pGameWindow->GetHandle());

    // �f�o�b�O���̏�����
    pDebug = new Debug;
    pDebug->Init();

    // ���C�g������
    pLight[0] = new Light;
    pLight[0]->type = Light::DIRECTIONAL;
    pLight[0]->diffuse = ColorValue(1.0f, 1.0f, 1.0f, 1.0f);
    pLight[0]->ambient = ColorValue(0.0f, 0.0f, 0.0f, 0.0f);
    pLight[0]->specular = ColorValue(0.0f, 0.0f, 0.0f, 0.0f);
    pLight[0]->direction = Vector3(0.6f, -1.0f, 0.6f);
    Vector3::Normalize(&pLight[0]->direction, &pLight[0]->direction);
    pRenderer->SetLight(0, pLight[0]);
    pRenderer->SetLight(0, true);

    pLight[1] = new Light;
    pLight[1]->type = Light::DIRECTIONAL;
    pLight[1]->diffuse = ColorValue(0.8f, 0.8f, 0.8f, 1.0f);
    pLight[1]->ambient = ColorValue(0.0f, 0.0f, 0.0f, 0.0f);
    pLight[1]->specular = ColorValue(0.0f, 0.0f, 0.0f, 0.0f);
    pLight[1]->direction = Vector3(-0.3f, 0.0f, 1.0f);
    Vector3::Normalize(&pLight[1]->direction, &pLight[1]->direction);
    pRenderer->SetLight(1, pLight[1]);
    pRenderer->SetLight(1, true);

    pLight[2] = new Light;
    pLight[2]->type = Light::DIRECTIONAL;
    pLight[2]->diffuse = ColorValue(0.2f, 0.2f, 0.2f, 1.0f);
    pLight[2]->ambient = ColorValue(0.0f, 0.0f, 0.0f, 0.0f);
    pLight[2]->specular = ColorValue(0.0f, 0.0f, 0.0f, 0.0f);
    pLight[2]->direction = Vector3(0.0f, -0.1f, -1.0f);
    Vector3::Normalize(&pLight[2]->direction, &pLight[2]->direction);
    pRenderer->SetLight(2, pLight[2]);
    pRenderer->SetLight(2, true);
    
    pRenderer->SetLightEnable(true);
    pRenderer->SetVertexColorEnable(true);
    pRenderer->SetCullingEnable(true);
    pRenderer->SetZWriteEnable(true);
    pRenderer->SetZTestEnable(true);
    pRenderer->SetBlend(Renderer::BLEND_SRC_ALPHA, Renderer::BLEND_SRC_INVALPHA);
    
    // ���͏�����
    pKeyboard = new Input::Keyboard;
    pJoystick = new Input::Joystick;

    // �����Ǘ��̏�����
    pSoundManager = new SoundManager;
    pSoundManager->Init();

    pSoundManager->Load("BGM1", "data/SOUND/bgm.wav");
    pSoundManager->Load("SE1", "data/SOUND/se001.wav");
    pSoundManager->Load("SE2", "data/SOUND/se002.wav");
    pSoundManager->Load("SE3", "data/SOUND/se003.wav");
    pSoundManager->Load("SE4", "data/SOUND/se004.wav");
    pSoundManager->Load("SE5", "data/SOUND/se005.wav");
    pSoundManager->Load("SE6", "data/SOUND/se006.wav");

    fade = new Fade;
    pSceneManager = new SceneManager;
    pSceneManager->SetScene(new Game::GameScene);

}

/******************************************************************************
@brief  �I������
******************************************************************************/

void Manager::Uninit()
{

    SAFE_DELETE(fade);
    SAFE_DELETE(pSceneManager);
    SAFE_DELETE(pLight[0]);
    SAFE_DELETE(pLight[1]);
    SAFE_DELETE(pLight[2]);
    SAFE_UNINIT(pSoundManager);
    SAFE_DELETE(pTextureFactory);
    SAFE_UNINIT(pError);
    SAFE_DELETE(pKeyboard);
    SAFE_DELETE(pJoystick);
    SAFE_UNINIT(pDebug);
    SAFE_UNINIT(pRenderer);
    SAFE_DELETE(pGameWindow);
    SAFE_DELETE(pMainController);

}

/******************************************************************************
@brief  ���[�v����
******************************************************************************/

void Manager::Loop()
{
    while (pGameWindow->Exists())
    {
        if (pGameWindow->CanProcess())
        {
            if (Fps::IsNextFrame())
            {// �Q�[������
                Update();
                Draw();
            }
        }
    }
}

/******************************************************************************
@brief  �X�V����
******************************************************************************/

void Manager::Update()
{
    pDebug->TimerStart();

    fade->Update();

    pDebug->Update();
    pDebug->Print("FPS : %.2f AvgFPS : %.2f\n", Fps::GetFPS(), Fps::GetAverageFPS());

    pKeyboard->Update();
    pJoystick->Update();

    pSceneManager->Update();
    GameObject::UpdateAll();

    pDebug->TimerEnd();
    pDebug->Print("Update : %f\n", pDebug->GetTimerSecond());
    //pDebug->Print("Draw : %f\n", pDebug->GetTimerSecond());
    pDebug->SetUpdateTime(pDebug->GetTimerSecond());
}

/******************************************************************************
@brief  �`�揈��
******************************************************************************/

void Manager::Draw()
{
    pDebug->TimerStart();

    pRenderer->Clear();

    DrawObject::DrawAll();

    pDebug->TimerEnd();
    pDebug->Print("Draw : %f\n", pDebug->GetTimerSecond());
    pDebug->SetDrawTime(pDebug->GetTimerSecond());
    
    pRenderer->Flip();

}

/******************************************************************************
@brief  ���̃t�F�[�h��ݒ�
@param  newState    �V�����ݒ肷��X�e�[�g
******************************************************************************/

void Manager::SetFade(Fade::Type fadeType, Scene* newScene)
{
    if (fade->GetFade() == Fade::FADE_NONE)
    {
        fade->SetFade(fadeType, newScene);
    }
    else
    {
        delete newScene;
    }
}

/******************************** ���������܂� *******************************/

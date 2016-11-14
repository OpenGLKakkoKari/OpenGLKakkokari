/*****************************************************************************/
/*!
@file   Debug.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Debug.h"
#include <stdarg.h>
#include "../Manager.h"
#include "../Fps.h"


using Framework::Debug;
using Framework::Manager;
using Framework::DebugTimer;
using Framework::Tweaker::Tweaker;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

Debug::Debug()
{
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

Debug::~Debug()
{

}

/******************************************************************************
@brief  ������
******************************************************************************/

void Debug::Init(void)
{
    pTweaker = new Tweaker::Tweaker;

    pTweaker->Add("Debug");
    pTweaker->SetDirectory("Debug");
    pTweaker->Add("WireFrame", &isWireFrame);
    pTweaker->Add("Texture", &isTexture);
    pTweaker->Add("Culling", &isCulling);
    pTweaker->Add("Background", &isBackground);

    pTimer = new DebugTimer;

    pSprite = Sprite::Create(
        // ���W
        Vector2((float)(Manager::GetWindow()->GetWidth() / 4), (float)(Manager::GetWindow()->GetHeight() / 2)),
        // �傫��
        Vector2((float)(Manager::GetWindow()->GetWidth() / 2), (float)(Manager::GetWindow()->GetHeight())),
        // �F
        Color(  0,  0,  0, 120));
    pSprite->SetPriority(-10);

    pText = new Text;

    isShow          = true;
    isWireFrame     = false;
    isTexture       = true;
    isCulling       = true;
    isTweaker       = true;
    isBackground    = false;
}

/******************************************************************************
@brief  �I������
******************************************************************************/

void Debug::Uninit(void)
{
    SAFE_DELETE(pTweaker);
    SAFE_DELETE(pSprite);
    SAFE_DELETE(pText);
    SAFE_DELETE(pTimer);
}

/******************************************************************************
@brief  �X�V����
******************************************************************************/

void Debug::Update(void)
{
    pTweaker->Update();

    pText->ClearBuffer();

    Fps::Calc(500);

    // �\���ؑ�
    if (Manager::GetKeyboard()->Trigger(VK_F1))
        isShow = !isShow;

    // �g�D�C�[�J�A�e�L�X�g�؂�ւ�
    if (Manager::GetKeyboard()->Trigger(VK_F2))
        isTweaker = !isTweaker;

    if (isWireFrame)
        Manager::GetRenderer()->SetWireFrameEnable(true);
    else
        Manager::GetRenderer()->SetWireFrameEnable(false);

    if (isTexture)
        Manager::GetRenderer()->SetTextureEnable(true);
    else
        Manager::GetRenderer()->SetTextureEnable(false);

    if (isCulling)
        Manager::GetRenderer()->SetCullingEnable(true);
    else
        Manager::GetRenderer()->SetCullingEnable(false);

    if (isShow && isBackground)
        pSprite->SetUse(true);
    else
        pSprite->SetUse(false);

    if (isShow && !isTweaker)
        pText->SetUse(true);
    else
        pText->SetUse(false);

    if (isShow && isTweaker)
        pTweaker->SetUse(true);
    else
        pTweaker->SetUse(false);

    // �g�D�C�[�J����
    if (isShow && isTweaker)
    {
        if (Manager::GetKeyboard()->Repeat(VK_UP))
            pTweaker->CursorUp();
        if (Manager::GetKeyboard()->Repeat(VK_DOWN))
            pTweaker->CursorDown();
        if (Manager::GetKeyboard()->Repeat(VK_LEFT))
            pTweaker->Decrease();
        if (Manager::GetKeyboard()->Repeat(VK_RIGHT))
            pTweaker->Increase();
        if (Manager::GetKeyboard()->Trigger(VK_RETURN))
            pTweaker->Select();

        if (Manager::GetKeyboard()->Repeat('O') && Manager::GetKeyboard()->Press('1'))
            pTweaker->UpX();
        if (Manager::GetKeyboard()->Repeat('O') && Manager::GetKeyboard()->Press('2'))
            pTweaker->UpY();
        if (Manager::GetKeyboard()->Repeat('O') && Manager::GetKeyboard()->Press('3'))
            pTweaker->UpZ();
        if (Manager::GetKeyboard()->Repeat('L') && Manager::GetKeyboard()->Press('1'))
            pTweaker->DownX();
        if (Manager::GetKeyboard()->Repeat('L') && Manager::GetKeyboard()->Press('2'))
            pTweaker->DownY();
        if (Manager::GetKeyboard()->Repeat('L') && Manager::GetKeyboard()->Press('3'))
            pTweaker->DownZ();
    }
}

/******************************************************************************
@brief  �f�o�b�O�����`��
@param  format      ������
******************************************************************************/

void Debug::Print(const char *format, ...)
{

    va_list args;
    char buffer[256];
    va_start(args, format);
    vsprintf_s(buffer, 256, format, args);
    va_end(args);
    pText->Print(buffer);
}

/******************************** ���������܂� *******************************/

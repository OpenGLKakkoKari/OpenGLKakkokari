/******************************************************************************
/*!
@file   Manager.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Windows\MainController.h"
#include "Windows\GameWindow.h"
#include "Renderer.h"
#include "Input\Keyboard.h"
#include "Input\Joystick.h"
#include "Input\Mouse.h"
#include "Error.h"

#include "Texture\TextureFactory.h"
#include "Sound\SoundManager.h"

#include "Light.h"
#include "Camera.h"

#include "Fade.h"
#include "Debug\Debug.h"

#include "SceneManager.h"


/*  マクロ定義
******************************************************************************/


#define SAFE_DELETE(p) if (p)                           \
                        {                               \
                            delete p;                   \
                            p=NULL;                     \
                        }

#define SAFE_DELETE_ARRAY(p) if (p)                     \
                             {                          \
                                 delete[] p;            \
                                 p=NULL;                \
                             }

#define SAFE_UNINIT(p) if (p)                           \
                        {                               \
                            p->Uninit();                \
                            delete p;                   \
                            p=NULL;                     \
                        }

#define SAFE_RELEASE(p) if (p)                          \
                        {                               \
                            p->Release();               \
                            p=NULL;                     \
                        }


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class Manager
    {
    public:
        Manager() {}
        virtual ~Manager() {}

        static void Init(HINSTANCE hInstance);
        static void Uninit();
        static void Loop();

        static Windows::GameWindow  *GetWindow()  { return pGameWindow; }
        static Renderer             *GetRenderer(){ return pRenderer; }
        static Input::Keyboard      *GetKeyboard(){ return pKeyboard; }
        static Input::Joystick      *GetJoystick(){ return pJoystick; }
        static Debug                *GetDebug()   { return pDebug; }
        static SoundManager         *GetSound()   { return pSoundManager; }

        static void SetScene(Scene* newScene) { pSceneManager->SetScene(newScene); }
        static void SetFade(Fade::Type fadeType, Scene* newScene);

    private:
        static void Update();
        static void Draw();

        static Windows::GameWindow      *pGameWindow;
        static Windows::MainController  *pMainController;
        static Renderer                 *pRenderer;
        static Input::Keyboard          *pKeyboard;
        static Input::Joystick          *pJoystick;
        static Input::Mouse             *pMouse;
        static Error                    *pError;

        static TextureFactory           *pTextureFactory;
        static SoundManager             *pSoundManager;

        static Light                    *pLight[3];

        static SceneManager             *pSceneManager;
        static Fade                     *fade;

        static Debug                    *pDebug;

    };
}


/******************************* ヘッダここまで ******************************/

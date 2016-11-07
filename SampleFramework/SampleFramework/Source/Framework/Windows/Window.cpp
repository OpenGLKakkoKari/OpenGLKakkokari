/*****************************************************************************/
/*!
@file   Window.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Window.h"
using namespace Windows;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/


Window::Window()
    : handle(0), instance(0), controller(NULL), winStyle(WS_OVERLAPPEDWINDOW),
    x(CW_USEDEFAULT), y(CW_USEDEFAULT),
    width(CW_USEDEFAULT), height(CW_USEDEFAULT),
    parentHandle(NULL), menuHandle(0)
{
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

Window::~Window()
{
    ::UnregisterClass(className, instance);
}

/******************************************************************************
@brief  �E�C���h�E����
@return HWND        �E�C���h�E�n���h��
******************************************************************************/

HWND Window::Create(HINSTANCE hInst, const char* name, HWND hParent, Controller* ctrl)
{
    instance = hInst;
    parentHandle = hParent;
    controller = ctrl;

    strcpy_s(this->title, MAX_STRING - 1, name);
    strcpy_s(this->className, MAX_STRING - 1, name);

    winClass.cbSize = sizeof(WNDCLASSEX);
    winClass.style = 0;
    winClass.lpfnWndProc = Procedure;
    winClass.cbClsExtra = 0;
    winClass.cbWndExtra = 0;
    winClass.hInstance = instance;
    winClass.hCursor = LoadCursor(0, IDC_ARROW);
    winClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    winClass.lpszClassName = className;

    if (!::RegisterClassEx(&winClass)) return 0;
    RECT rect = {0, 0, width, height};
    if (winClass.lpszMenuName != NULL)
        AdjustWindowRect(&rect, winStyle, true);
    else
        AdjustWindowRect(&rect, winStyle, false);

    handle = ::CreateWindowEx(
        NULL,                   // �E�C���h�E�X�^�C��
        className,              // �N���X��
        title,                  // �^�C�g��
        winStyle,               // �E�C���h�E�X�^�C��
        x,                      // �ʒu(X)
        y,                      // �ʒu(Y)
        rect.right - rect.left,                  // ����
        rect.bottom - rect.top,                 // �c��
        parentHandle,           // �e�E�C���h�E�n���h��
        NULL,             // ���j���[�n���h��
        instance,               // �C���X�^���X
        (LPVOID)controller);    // ���[�U�[��`�f�[�^

    return handle;
}

/******************************************************************************
@brief  �E�C���h�E�̕\��
@param  cmdShow     �E�C���h�E�\���̃t���O
******************************************************************************/

void Window::Show(int cmdShow)
{
    ::ShowWindow(handle, cmdShow);
    ::UpdateWindow(handle);
}

/******************************************************************************
@brief  �E�C���h�E�v���V�[�W��
@param  hWnd        �E�C���h�E�n���h��
@param  uMsg        ���b�Z�[�W
@param  wParam      ���b�Z�[�W�̕t�����
@param  lParam      ���b�Z�[�W�̕t�����
@return LRESULT     ���b�Z�[�W
******************************************************************************/

LRESULT CALLBACK Window::Procedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    LRESULT returnValue = 0;

    // �E�C���h�E�n���h���Ɋ֘A�t����ꂽ�R���g���[�����擾
    static Controller *ctrl;
    ctrl = (Controller*)::GetWindowLongPtr(hWnd, GWL_USERDATA);

    if (msg == WM_NCCREATE)
    {
        // ��N���C�A���g�̈�̃p�[�c�������O��WM_NCCREATE���Ă΂��B
        // ���̃��b�Z�[�W�ƂƂ���CREATESTRUCT �� lpCreateParams �ɂ�
        // CreateWindowEX() �� lpPraram�������Ă���B
        // �܂��A�E�C���h�E���J�n����ۂɁA�R���g���[���[���擾����B
        ctrl = (Controller*)(((CREATESTRUCT*)lParam)->lpCreateParams);
        ctrl->setHandle(hWnd);

        // GWL_USERDATA�ɃR���g���[���[��ݒ肷��B
        // �������邱�Ƃɂ���āA���̃��b�Z�[�W�̓R���g���[���o�R��
        // ���b�Z�[�W���������邱�Ƃ��ł���B
        ::SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR)ctrl);

        return ::DefWindowProc(hWnd, msg, wParam, lParam);
    }

    // GWL_USERDATA�͍ŏ�0�ɏ���������A�L���ȃ|�C���^��
    // WM_NCCREATE���ɕۑ�����邽��NULL�`�F�b�N���s��
    if (!ctrl)
        return ::DefWindowProc(hWnd, msg, wParam, lParam);
    
    // �R���g���[���[�Ƀ��b�Z�[�W������������
    switch (msg)
    {
    case WM_CREATE:
        returnValue = ctrl->create();
        break;

    case WM_SIZE:
        returnValue = ctrl->size(LOWORD(lParam), HIWORD(lParam), (int)wParam);
        break;

    case WM_ENABLE:
    {
        bool flag;
        if (wParam) flag = true;
        else flag = false;
        returnValue = ctrl->enable(flag);
        break;
    }

    case WM_PAINT:
        ctrl->paint();
        returnValue = ::DefWindowProc(hWnd, msg, wParam, lParam);
        break;

    case WM_COMMAND:
        returnValue = ctrl->command(LOWORD(wParam), HIWORD(wParam), lParam);
        break;

    case WM_MOUSEMOVE:
        returnValue = ctrl->mouseMove(wParam, LOWORD(lParam), HIWORD(lParam));
        break;

    case WM_CLOSE:
        returnValue = ctrl->close();
        break;

    case WM_DESTROY:
        returnValue = ctrl->destroy();
        break;

    case WM_SYSCOMMAND:
        //returnValue = ctrl->sysCommand(wParam, lParam);
        returnValue = ::DefWindowProc(hWnd, msg, wParam, lParam);
        break;

    case WM_CHAR:
        //returnValue = ctrl->char(wParam, lParam);
        break;

    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
        returnValue = ctrl->keyDown((int)wParam, lParam);
        break;

    case WM_KEYUP:
    case WM_SYSKEYUP:
        returnValue = ctrl->keyUp((int)wParam, lParam);
        break;

    case WM_LBUTTONDOWN:
        returnValue = ctrl->lButtonDown(wParam, LOWORD(lParam), HIWORD(lParam));
        break;

    case WM_LBUTTONUP:
        returnValue = ctrl->lButtonUp(wParam, LOWORD(lParam), HIWORD(lParam));
        break;

    case WM_RBUTTONDOWN:
        returnValue = ctrl->rButtonDown(wParam, LOWORD(lParam), HIWORD(lParam));
        break;

    case WM_RBUTTONUP:
        returnValue = ctrl->rButtonUp(wParam, LOWORD(lParam), HIWORD(lParam));
        break;

    case WM_MBUTTONDOWN:
        returnValue = ctrl->mButtonDown(wParam, LOWORD(lParam), HIWORD(lParam));
        break;

    case WM_MBUTTONUP:
        returnValue = ctrl->mButtonUp(wParam, LOWORD(lParam), HIWORD(lParam));
        break;

    case WM_MOUSEWHEEL:
        break;

    case WM_HSCROLL:
        returnValue = ctrl->hScroll(wParam, lParam);
        break;

    case WM_VSCROLL:
        returnValue = ctrl->vScroll(wParam, lParam);
        break;

    case WM_TIMER:
        returnValue = ctrl->timer(LOWORD(wParam), HIWORD(wParam));
        break;

    case WM_NOTIFY:
        returnValue = ctrl->notify((int)wParam, lParam);
        break;

    case WM_CONTEXTMENU:
        returnValue = ctrl->contextMenu((HWND)wParam, LOWORD(lParam), HIWORD(lParam));

    default:
        returnValue = ::DefWindowProc(hWnd, msg, wParam, lParam);
    }

    return returnValue;
}

/******************************************************************************
@brief  �A�C�R���̓ǂݍ���
@param  id          �A�C�R��ID
@return HICON       �A�C�R���n���h��
******************************************************************************/

HICON Window::loadIcon(int id)
{
    return (HICON)::LoadImage(instance, MAKEINTRESOURCE(id), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE);
}

/******************************************************************************
@brief  �J�[�\���̓ǂݍ���
@param  id          �J�[�\��ID
@return HICON       �J�[�\���n���h��
******************************************************************************/

HCURSOR Window::loadCursor(int id)
{
    return (HCURSOR)::LoadImage(instance, MAKEINTRESOURCE(id), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE);
}

/******************************** ���������܂� *******************************/

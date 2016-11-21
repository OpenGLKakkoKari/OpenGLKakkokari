/*****************************************************************************/
/*!
@file   Tweaker.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Tweaker.h"
#include "../Manager.h"
#include "../TokenAnalyzer.h"
#include "../Math/Math.h"


using Framework::Text;
using Framework::Manager;

using Framework::Vector2;
using Framework::Vector3;
using Framework::Color;
using namespace Framework::Math;
using namespace Framework::Tweaker;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

Tweaker::Tweaker()
{
    pText = new Text;
    dirObjectList = new DirectoryObject[OBJECT_MAX];
    Init();
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

Tweaker::~Tweaker()
{
    SAFE_DELETE(pText);
    SAFE_DELETE(dirObjectList);
}

/******************************************************************************
@brief  ����������
******************************************************************************/

void Tweaker::Init(void)
{
    // root�ݒ�
    dirObjectList[0].SetName("root");
    dirObjectList[0].SetUse(true);
    currentDirectory = &dirObjectList[0];
    cursorPos = 0;
}

/******************************************************************************
@brief  �X�V����
******************************************************************************/

void Tweaker::Update(void)
{
    pText->ClearBuffer();
    PrintVersion();     // �o�[�W�����\��
    PrintBreadcrumb();  // �p���������X�g�\��

    int cnt = 0;
    // �e�f�B���N�g���ȊO�̏ꍇ
    if (!IsRoot(currentDirectory))
    {// �ЂƂ�ɖ߂��悤�ɂ���
        pText->Print("  [...]");

        // �J�[�\���̕`��
        if (IsCursorPosition(cnt))
            PrintCursor();
        pText->Print("\n");

        // ���̕`��
        PrintLine();
        cnt++;
    }

    // �f�B���N�g���̓��e��\��
    for (DirectoryObject* it = currentDirectory->child_; it != NULL; it = it->sibling_)
    {
        // �A�C�R����\��
        // } �̓t�H���_�[�̃A�C�R��
        // ~ �̓t�@�C���̃A�C�R��

        if (it->IsSameType(TYPE_FOLDER))
            pText->Print("}");
        else
            pText->Print("~");


        // �I�u�W�F�N�g����\��
        pText->Print("  %s    ", it->GetName());

        
        // �I�u�W�F�N�g�̎�ނɍ��킹�ē��e��\��
        Vector2 vec2;
        Vector3 vec3;
        Color col;

        switch (it->GetType())
        {
        case TYPE_INT       :   pText->Print("%d", *reinterpret_cast<int*>(it->pData));                             break;
        case TYPE_FLOAT     :   pText->Print("%f", *reinterpret_cast<float*>(it->pData));                           break;
        case TYPE_BOOL      :   pText->Print("%s", *reinterpret_cast<bool*>(it->pData) ? ("true") : ("false"));     break;
        case TYPE_VECTOR2   :
            vec2 = *reinterpret_cast<Vector2*>(it->pData);
            pText->Print("(%f, %f)", vec2.x, vec2.y);
            break;
        case TYPE_VECTOR3:
            vec3 = *reinterpret_cast<Vector3*>(it->pData);
            pText->Print("(%f, %f, %f)", vec3.x, vec3.y, vec3.z);
            break;
        case TYPE_COLOR:
            col = *reinterpret_cast<Color*>(it->pData);
            pText->Print("(%d, %d, %d, %d)", col.r, col.g, col.b, col.a);
            break;
        }

        // �J�[�\���̕`��
        if (IsCursorPosition(cnt))
            PrintCursor();
        pText->Print("\n");

        cnt++;
    }

    // ���̕`��
    if (!IsRoot(currentDirectory))
        PrintLine();

    // �J�[�\����͈͓��ɃN�����v
    if (cursorPos < 0)
        cursorPos = cnt - 1;
    if (cnt - 1 < cursorPos)
        cursorPos = 0;
}

/******************************************************************************
@brief  �o�[�W������`��
******************************************************************************/

void Tweaker::PrintVersion()
{
    pText->Print("Tweaker Edit ver 1.1\n");
}

/******************************************************************************
@brief  �p���������X�g��`��
******************************************************************************/

void Tweaker::PrintBreadcrumb()
{
    // �p���������X�g�\��
    // ex) "Game/Player"
    // ���݂̃f�B���N�g�����烋�[�g�f�B���N�g���܂ł�
    // �f�B���N�g���K�w��\��
    // ���ǂ�Ƃ��͎q���e�����\������Ƃ��́A�e���q�Ȃ̂�
    // �t���ŕ`�悵�Ă���
    const int dirMax = 16;
    DirectoryObject* route[dirMax];
    route[0] = currentDirectory;
    int cnt = 0;

    // ��ʊK�w�����[�g�K�w�ɂȂ�܂ők��
    DirectoryObject* obj = currentDirectory;
    while (!IsRoot(obj))
    {
        cnt++;
        DirectoryObject* above = GetAboveDirectory(obj);
        route[cnt] = above;
        obj = above;
    }

    // �擾�����f�B���N�g����\��
    // root�̏ꍇroot�ƕ\��
    pText->Print("\"");
    if (!IsRoot(currentDirectory))
    {
        for (int i = cnt; i >= 0; i--)
        {
            pText->Print("%s/", route[i]->GetName());
        }
    }
    else
    {
        pText->Print("root");
    }
    pText->Print("\"");
    pText->Print("\n\n");
}

/******************************************************************************
@brief  ����`��
******************************************************************************/

void Tweaker::PrintLine()
{
    pText->Print("------------------------------\n");
}

/******************************************************************************
@brief  �J�[�\����`��
******************************************************************************/

void Tweaker::PrintCursor()
{
    pText->Print("   @");
}

/******************************************************************************
@brief  �f�B���N�g�����Z�b�g
@param  DirName        �f�B���N�g����
******************************************************************************/

void Tweaker::SetDirectory(char* DirName)
{
    DirectoryObject* obj = GetRoot();
    TokenAnalyzer* pToken = new TokenAnalyzer(DirName);
    pToken->SetSkipChars("/\\");
    while (!pToken->IsScriptEnd())
    {
        pToken->GetToken();
        for (obj = obj->child_; obj != NULL; obj = obj->sibling_)
        {
            if (pToken->CheckToken(obj->GetName()) && obj->IsSameType(TYPE_FOLDER))
            {
                // �����t�H���_�[���̃t�H���_������Έړ�
                currentDirectory = obj;
                break;
            }
        }
    }
    delete pToken;
}

/******************************************************************************
@brief  �m�[�h��ǉ�
@param  DirName         �f�B���N�g����
@param  Text            �\���e�L�X�g
@param  value           �l
******************************************************************************/

void Tweaker::Add(char* DirName)
{
    DirectoryObject* obj = GetRoot();
    TokenAnalyzer* pToken = new TokenAnalyzer(DirName);
    pToken->SetSkipChars("/\\");

    while (!pToken->IsScriptEnd())
    {
        char* token = pToken->GetToken();

        // �����t�H���_�[���̃t�H���_������Έړ�
        DirectoryObject* it = obj;
        for (it = it->child_; it != NULL; it = it->sibling_)
        {
            if (pToken->CheckToken(it->GetName()) && it->IsSameType(TYPE_FOLDER))
            {
                obj = it;
                break;
            }
        }
        // �Ȃ���΍쐬
        if (it == NULL)
        {
            for (int i = 0; i < OBJECT_MAX; i++)
            {
                if (!dirObjectList[i].IsUsed())
                {
                    // �t�H���_�[���쐬
                    dirObjectList[i].SetName(token);
                    dirObjectList[i].type_ = TYPE_FOLDER;
                    dirObjectList[i].SetUse(true);


                    // �q���ɒǉ��ł��Ȃ��ꍇ��
                    // �����ɒǉ�
                    if (obj->child_ != NULL)
                    {
                        DirectoryObject* end = GetDirectoryEnd(obj);
                        end->sibling_ = &dirObjectList[i];
                        obj = end->sibling_;
                    }
                    else
                    {
                        obj->child_ = &dirObjectList[i];
                        obj = obj->child_;
                    }
                    break;
                }
            }
        }

    }
    delete pToken;
}
void Tweaker::Add(const char* Text, bool* value)
{
    for (int i = 0; i < OBJECT_MAX; i++)
    {
        if (!dirObjectList[i].IsUsed())
        {
            dirObjectList[i].SetName(Text);
            dirObjectList[i].Set(value);
            dirObjectList[i].SetUse(true);
            AddObject(&dirObjectList[i]);
            break;
        }
    }
}
void Tweaker::Add(const char* Text, float* value)
{
    for (int i = 0; i < OBJECT_MAX; i++)
    {
        if (!dirObjectList[i].IsUsed())
        {
            dirObjectList[i].SetName(Text);
            dirObjectList[i].Set(value);
            dirObjectList[i].SetUse(true);
            AddObject(&dirObjectList[i]);
            break;
        }
    }
}
void Tweaker::Add(const char* Text, int* value)
{
    for (int i = 0; i < OBJECT_MAX; i++)
    {
        if (!dirObjectList[i].IsUsed())
        {
            dirObjectList[i].SetName(Text);
            dirObjectList[i].Set(value);
            dirObjectList[i].SetUse(true);
            AddObject(&dirObjectList[i]);
            break;
        }
    }
}
void Tweaker::Add(const char* Text, Vector2* value)
{
    for (int i = 0; i < OBJECT_MAX; i++)
    {
        if (!dirObjectList[i].IsUsed())
        {
            dirObjectList[i].SetName(Text);
            dirObjectList[i].Set(value);
            dirObjectList[i].SetUse(true);
            AddObject(&dirObjectList[i]);
            break;
        }
    }
}
void Tweaker::Add(const char* Text, Vector3* value)
{
    for (int i = 0; i < OBJECT_MAX; i++)
    {
        if (!dirObjectList[i].IsUsed())
        {
            dirObjectList[i].SetName(Text);
            dirObjectList[i].Set(value);
            dirObjectList[i].SetUse(true);
            AddObject(&dirObjectList[i]);
            break;
        }
    }
}
void Tweaker::Add(const char* Text, Color* value)
{
    for (int i = 0; i < OBJECT_MAX; i++)
    {
        if (!dirObjectList[i].IsUsed())
        {
            dirObjectList[i].SetName(Text);
            dirObjectList[i].Set(value);
            dirObjectList[i].SetUse(true);
            AddObject(&dirObjectList[i]);
            break;
        }
    }
}

/******************************************************************************
@brief  �t�H���_�[���폜
@param  Text            �\���e�L�X�g
@param  type            �^�C�v
******************************************************************************/

void Tweaker::Delete(const char* Text)
{

    DirectoryObject* obj = GetRoot();
    TokenAnalyzer* pToken = new TokenAnalyzer(Text);
    pToken->SetSkipChars("/\\");

    // �w�肵���t�H���_�[�Ɉړ�
    while (!pToken->IsScriptEnd())
    {
        char* token = pToken->GetToken();

        for (obj = obj->child_; obj != NULL; obj = obj->sibling_)
        {
            if (pToken->CheckToken(obj->GetName()) && obj->IsSameType(TYPE_FOLDER))
            {
                // �t�H���_�[�𔭌�
                break;
            }
        }
    }
    delete pToken;

    // �e�f�B���N�g���̎q����ύX
    DirectoryObject* above = GetAboveDirectory(obj);
    if (above->child_ == obj)
        above->child_ = obj->sibling_;
    else
    {
        for (DirectoryObject* it = above->child_; it != NULL; it = it->sibling_)
        {
            if (it->sibling_ == obj)
            {
                it->sibling_ = obj->sibling_;
                break;
            }
        }
    }

    // �t�H���_�[�̒��g��S�폜
    DeleteFolder(obj, Text);
    // �t�H���_�[���폜
    DeleteObject(obj);

    // �J�����g�f�B���N�g�����폜����Ƃ܂����̂�
    // �J�����g�f�B���N�g����root�ɂ���
    currentDirectory = GetRoot();
}

/******************************************************************************
@brief  �J�[�\������Ɉړ�
******************************************************************************/

void Tweaker::CursorUp(void)
{
    cursorPos--;
}

/******************************************************************************
@brief  �J�[�\�������Ɉړ�
******************************************************************************/

void Tweaker::CursorDown(void)
{
    cursorPos++;
}

/******************************************************************************
@brief  �ϐ������炷
******************************************************************************/

void Tweaker::Decrease(void)
{
    int posCount = 0;
    if (!IsRoot(currentDirectory))
        posCount++;

    for (DirectoryObject* obj = currentDirectory->child_; obj != NULL; obj = obj->sibling_)
    {
        if (cursorPos == posCount)
        {
            switch (obj->GetType())
            {
            case TYPE_INT:      *reinterpret_cast<int*>(obj->pData) -= 1;                                       break;
            case TYPE_FLOAT:    *reinterpret_cast<float*>(obj->pData) -= 1.0f;                                  break;
            case TYPE_BOOL:     *reinterpret_cast<bool*>(obj->pData) = !*reinterpret_cast<bool*>(obj->pData);   break;
            default:                                                                                            break;
            }
            break;
        }
        posCount++;
    }
}

/******************************************************************************
@brief  �ϐ��𑝂₷
******************************************************************************/

void Tweaker::Increase(void)
{
    int posCount = 0;
    if (!IsRoot(currentDirectory))
        posCount++;

    for (DirectoryObject* obj = currentDirectory->child_; obj != NULL; obj = obj->sibling_)
    {
        if (cursorPos == posCount)
        {
            switch (obj->GetType())
            {
            case TYPE_INT:      *reinterpret_cast<int*>(obj->pData) += 1;                                       break;
            case TYPE_FLOAT:    *reinterpret_cast<float*>(obj->pData) += 1.0f;                                  break;
            case TYPE_BOOL:     *reinterpret_cast<bool*>(obj->pData) = !*reinterpret_cast<bool*>(obj->pData);   break;
            default:                                                                                            break;
            }
            break;
        }
        posCount++;
    }
}

/******************************************************************************
@brief  �ϐ��𑝂₷
******************************************************************************/

void Tweaker::UpX(void)
{
    int posCount = 0;
    if (!IsRoot(currentDirectory))
        posCount++;

    for (DirectoryObject* obj = currentDirectory->child_; obj != NULL; obj = obj->sibling_)
    {
        if (cursorPos == posCount)
        {
            switch (obj->GetType())
            {
            case TYPE_VECTOR3:  reinterpret_cast<Vector3*>(obj->pData)->x += 0.1f;  break;
            default:                                                                break;
            }
            break;
        }
        posCount++;
    }
}

/******************************************************************************
@brief  �ϐ��𑝂₷
******************************************************************************/

void Tweaker::UpY(void)
{
    int posCount = 0;
    if (!IsRoot(currentDirectory))
        posCount++;

    for (DirectoryObject* obj = currentDirectory->child_; obj != NULL; obj = obj->sibling_)
    {
        if (cursorPos == posCount)
        {
            switch (obj->GetType())
            {
            case TYPE_VECTOR3:  reinterpret_cast<Vector3*>(obj->pData)->y += 0.1f;  break;
            default:                                                                break;
            }
            break;
        }
        posCount++;
    }
}

/******************************************************************************
@brief  �ϐ��𑝂₷
******************************************************************************/

void Tweaker::UpZ(void)
{
    int posCount = 0;
    if (!IsRoot(currentDirectory))
        posCount++;

    for (DirectoryObject* obj = currentDirectory->child_; obj != NULL; obj = obj->sibling_)
    {
        if (cursorPos == posCount)
        {
            switch (obj->GetType())
            {
            case TYPE_VECTOR3:  reinterpret_cast<Vector3*>(obj->pData)->z += 0.1f;  break;
            default:                                                                break;
            }
            break;
        }
        posCount++;
    }
}

/******************************************************************************
@brief  �ϐ������炷
******************************************************************************/

void Tweaker::DownX(void)
{
    int posCount = 0;
    if (!IsRoot(currentDirectory))
        posCount++;

    for (DirectoryObject* obj = currentDirectory->child_; obj != NULL; obj = obj->sibling_)
    {
        if (cursorPos == posCount)
        {
            switch (obj->GetType())
            {
            case TYPE_VECTOR3:  reinterpret_cast<Vector3*>(obj->pData)->x -= 0.1f;  break;
            default:                                                                break;
            }
            break;
        }
        posCount++;
    }
}

/******************************************************************************
@brief  �ϐ������炷
******************************************************************************/

void Tweaker::DownY(void)
{
    int posCount = 0;
    if (!IsRoot(currentDirectory))
        posCount++;

    for (DirectoryObject* obj = currentDirectory->child_; obj != NULL; obj = obj->sibling_)
    {
        if (cursorPos == posCount)
        {
            switch (obj->GetType())
            {
            case TYPE_VECTOR3:  reinterpret_cast<Vector3*>(obj->pData)->y -= 0.1f;  break;
            default:                                                                break;
            }
            break;
        }
        posCount++;
    }
}

/******************************************************************************
@brief  �ϐ������炷
******************************************************************************/

void Tweaker::DownZ(void)
{
    int posCount = 0;
    if (!IsRoot(currentDirectory))
        posCount++;

    for (DirectoryObject* obj = currentDirectory->child_; obj != NULL; obj = obj->sibling_)
    {
        if (cursorPos == posCount)
        {
            switch (obj->GetType())
            {
            case TYPE_VECTOR3:  reinterpret_cast<Vector3*>(obj->pData)->z -= 0.1f;  break;
            default:                                                                break;
            }
            break;
        }
        posCount++;
    }
}

/******************************************************************************
@brief  ���݂̃J�[�\�����w���Ă�����̂�I��
******************************************************************************/

void Tweaker::Select(void)
{
    int posCount = 0;

    // ���݂̃f�B���N�g����root�łȂ��A
    if (!IsRoot(currentDirectory))
    {
        // ���X�g�̈�ԏ��I�������ꍇ
        // ���݂̃f�B���N�g�������̊K�w�Ɉړ�
        if (cursorPos == 0)
        {
            currentDirectory = GetAboveDirectory(currentDirectory);
            return;
        }
        // ��̊K�w�ɖ߂鍀��([...])
        // �̕��������炷
        posCount++;
    }

    // �t�H���_��I�����Ă���ꍇ�̂�
    // �t�H���_���Ɉړ�
    for (DirectoryObject* obj = currentDirectory->child_; obj != NULL; obj = obj->sibling_)
    {
        if (cursorPos == posCount && obj->IsSameType(TYPE_FOLDER))
        {
            currentDirectory = obj;
            break;
        }
        posCount++;
    }
}

/******************************************************************************
@brief  �g�D�C�[�J���̃I�u�W�F�N�g�����ׂă��Z�b�g
******************************************************************************/

void Tweaker::Reset(void)
{
    for (int i = 0; i < OBJECT_MAX; i++)
    {
        DeleteObject(&dirObjectList[i]);
    }
    Init();
}

/******************************************************************************
@brief  �w�肳�ꂽ�f�B���N�g���̈��̊K�w���擾
******************************************************************************/

DirectoryObject* Tweaker::GetAboveDirectory(DirectoryObject* dir)
{
    // �w��f�B���N�g�����q���Ɏ����Z��Ŏ��I�u�W�F�N�g������
    DirectoryObject* obj = dir;
    while (!IsRoot(obj))
    {
        for (int i = 0; i < OBJECT_MAX; i++)
        {
            // �q���Ɏ��I�u�W�F�N�g�̏ꍇ��
            // �T���I��
            if (dirObjectList[i].child_ == obj)
            {
                return &dirObjectList[i];
            }
            // �Z��Ɏ��I�u�W�F�N�g�̏ꍇ��
            // �T���Ώۂ�ύX���A������x�T��
            if (dirObjectList[i].sibling_ == obj)
            {
                obj = &dirObjectList[i];
            }
        }
    }
    return obj;
}

/******************************************************************************
@brief  �w�肳�ꂽ�f�B���N�g���̖����̃|�C���^���擾
******************************************************************************/

DirectoryObject* Tweaker::GetDirectoryEnd(DirectoryObject* dir)
{
    // ���݂̃f�B���N�g�����疖���܂ňړ�
    DirectoryObject* obj = dir->child_;
    if (obj == NULL)
        return dir;

    while (obj->sibling_ != NULL)
    {
        obj = obj->sibling_;
    }

    return obj;
}

/******************************************************************************
@brief  �I�u�W�F�N�g��ǉ�
******************************************************************************/

void Tweaker::AddObject(DirectoryObject* p)
{
    // ���݂̃f�B���N�g���ɑ��ɃI�u�W�F�N�g���Ȃ����
    // �q���ɒǉ�
    if (!currentDirectory->child_)
    {
        currentDirectory->child_ = p;
    }
    else
    {
        // ���݂̃f�B���N�g���̖����̃|�C���^���擾
        DirectoryObject* end = GetDirectoryEnd(currentDirectory);

        // �����ɒǉ�
        end->sibling_ = p;
    }
}

/******************************************************************************
@brief  �I�u�W�F�N�g���폜
******************************************************************************/

void Tweaker::DeleteObject(DirectoryObject* p)
{
    p->SetUse(false);
    p->SetName("");
    p->child_ = NULL;
    p->sibling_ = NULL;
    p->pData = NULL;
    p->type_ = TYPE_FOLDER;
}

/******************************************************************************
@brief  �t�H���_�[���폜
******************************************************************************/

void Tweaker::DeleteFolder(DirectoryObject* p, const char* filePath)
{
    // �t�H���_�[�̒��g��S�폜
    for (DirectoryObject* it = p->child_; it != NULL;)
    {
        DirectoryObject* tmp = it->sibling_;
        // �t�H���_�[�̏ꍇ�͍ċA�őS�č폜
        if (it->IsSameType(TYPE_FOLDER))
        {
            const char* str = it->GetName();
            char path[256] = { 0 };
            strcat_s(path, sizeof(path), filePath);
            strcat_s(path, sizeof(path), "/");
            strcat_s(path, sizeof(path), str);
            DeleteFolder(it, path);
        }
        DeleteObject(it);
        it = tmp;
    }
}

/******************************** ���������܂� *******************************/

/*****************************************************************************/
/*!
@file   Tweaker.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
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


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/

Tweaker::Tweaker()
{
    pText = new Text;
    dirObjectList = new DirectoryObject[OBJECT_MAX];
    Init();
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

Tweaker::~Tweaker()
{
    SAFE_DELETE(pText);
    SAFE_DELETE(dirObjectList);
}

/******************************************************************************
@brief  初期化処理
******************************************************************************/

void Tweaker::Init(void)
{
    // root設定
    dirObjectList[0].SetName("root");
    dirObjectList[0].SetUse(true);
    currentDirectory = &dirObjectList[0];
    cursorPos = 0;
}

/******************************************************************************
@brief  更新処理
******************************************************************************/

void Tweaker::Update(void)
{
    pText->ClearBuffer();
    PrintVersion();     // バージョン表示
    PrintBreadcrumb();  // パンくずリスト表示

    int cnt = 0;
    // 親ディレクトリ以外の場合
    if (!IsRoot(currentDirectory))
    {// ひとつ上に戻れるようにする
        pText->Print("  [...]");

        // カーソルの描画
        if (IsCursorPosition(cnt))
            PrintCursor();
        pText->Print("\n");

        // 線の描画
        PrintLine();
        cnt++;
    }

    // ディレクトリの内容を表示
    for (DirectoryObject* it = currentDirectory->child_; it != NULL; it = it->sibling_)
    {
        // アイコンを表示
        // } はフォルダーのアイコン
        // ~ はファイルのアイコン

        if (it->IsSameType(TYPE_FOLDER))
            pText->Print("}");
        else
            pText->Print("~");


        // オブジェクト名を表示
        pText->Print("  %s    ", it->GetName());

        
        // オブジェクトの種類に合わせて内容を表示
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

        // カーソルの描画
        if (IsCursorPosition(cnt))
            PrintCursor();
        pText->Print("\n");

        cnt++;
    }

    // 線の描画
    if (!IsRoot(currentDirectory))
        PrintLine();

    // カーソルを範囲内にクランプ
    if (cursorPos < 0)
        cursorPos = cnt - 1;
    if (cnt - 1 < cursorPos)
        cursorPos = 0;
}

/******************************************************************************
@brief  バージョンを描画
******************************************************************************/

void Tweaker::PrintVersion()
{
    pText->Print("Tweaker Edit ver 1.1\n");
}

/******************************************************************************
@brief  パンくずリストを描画
******************************************************************************/

void Tweaker::PrintBreadcrumb()
{
    // パンくずリスト表示
    // ex) "Game/Player"
    // 現在のディレクトリからルートディレクトリまでの
    // ディレクトリ階層を表示
    // たどるときは子→親だが表示するときは、親→子なので
    // 逆順で描画している
    const int dirMax = 16;
    DirectoryObject* route[dirMax];
    route[0] = currentDirectory;
    int cnt = 0;

    // 上位階層がルート階層になるまで遡る
    DirectoryObject* obj = currentDirectory;
    while (!IsRoot(obj))
    {
        cnt++;
        DirectoryObject* above = GetAboveDirectory(obj);
        route[cnt] = above;
        obj = above;
    }

    // 取得したディレクトリを表示
    // rootの場合rootと表示
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
@brief  線を描画
******************************************************************************/

void Tweaker::PrintLine()
{
    pText->Print("------------------------------\n");
}

/******************************************************************************
@brief  カーソルを描画
******************************************************************************/

void Tweaker::PrintCursor()
{
    pText->Print("   @");
}

/******************************************************************************
@brief  ディレクトリをセット
@param  DirName        ディレクトリ名
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
                // 同じフォルダー名のフォルダがあれば移動
                currentDirectory = obj;
                break;
            }
        }
    }
    delete pToken;
}

/******************************************************************************
@brief  ノードを追加
@param  DirName         ディレクトリ名
@param  Text            表示テキスト
@param  value           値
******************************************************************************/

void Tweaker::Add(char* DirName)
{
    DirectoryObject* obj = GetRoot();
    TokenAnalyzer* pToken = new TokenAnalyzer(DirName);
    pToken->SetSkipChars("/\\");

    while (!pToken->IsScriptEnd())
    {
        char* token = pToken->GetToken();

        // 同じフォルダー名のフォルダがあれば移動
        DirectoryObject* it = obj;
        for (it = it->child_; it != NULL; it = it->sibling_)
        {
            if (pToken->CheckToken(it->GetName()) && it->IsSameType(TYPE_FOLDER))
            {
                obj = it;
                break;
            }
        }
        // なければ作成
        if (it == NULL)
        {
            for (int i = 0; i < OBJECT_MAX; i++)
            {
                if (!dirObjectList[i].IsUsed())
                {
                    // フォルダーを作成
                    dirObjectList[i].SetName(token);
                    dirObjectList[i].type_ = TYPE_FOLDER;
                    dirObjectList[i].SetUse(true);


                    // 子供に追加できない場合は
                    // 末尾に追加
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
@brief  フォルダーを削除
@param  Text            表示テキスト
@param  type            タイプ
******************************************************************************/

void Tweaker::Delete(const char* Text)
{

    DirectoryObject* obj = GetRoot();
    TokenAnalyzer* pToken = new TokenAnalyzer(Text);
    pToken->SetSkipChars("/\\");

    // 指定したフォルダーに移動
    while (!pToken->IsScriptEnd())
    {
        char* token = pToken->GetToken();

        for (obj = obj->child_; obj != NULL; obj = obj->sibling_)
        {
            if (pToken->CheckToken(obj->GetName()) && obj->IsSameType(TYPE_FOLDER))
            {
                // フォルダーを発見
                break;
            }
        }
    }
    delete pToken;

    // 親ディレクトリの子供を変更
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

    // フォルダーの中身を全削除
    DeleteFolder(obj, Text);
    // フォルダーを削除
    DeleteObject(obj);

    // カレントディレクトリを削除するとまずいので
    // カレントディレクトリをrootにする
    currentDirectory = GetRoot();
}

/******************************************************************************
@brief  カーソルを上に移動
******************************************************************************/

void Tweaker::CursorUp(void)
{
    cursorPos--;
}

/******************************************************************************
@brief  カーソルを下に移動
******************************************************************************/

void Tweaker::CursorDown(void)
{
    cursorPos++;
}

/******************************************************************************
@brief  変数を減らす
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
@brief  変数を増やす
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
@brief  変数を増やす
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
@brief  変数を増やす
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
@brief  変数を増やす
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
@brief  変数を減らす
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
@brief  変数を減らす
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
@brief  変数を減らす
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
@brief  現在のカーソルが指しているものを選択
******************************************************************************/

void Tweaker::Select(void)
{
    int posCount = 0;

    // 現在のディレクトリがrootでなく、
    if (!IsRoot(currentDirectory))
    {
        // リストの一番上を選択した場合
        // 現在のディレクトリを一つ上の階層に移動
        if (cursorPos == 0)
        {
            currentDirectory = GetAboveDirectory(currentDirectory);
            return;
        }
        // 上の階層に戻る項目([...])
        // の分だけずらす
        posCount++;
    }

    // フォルダを選択している場合のみ
    // フォルダ内に移動
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
@brief  トゥイーカ内のオブジェクトをすべてリセット
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
@brief  指定されたディレクトリの一つ上の階層を取得
******************************************************************************/

DirectoryObject* Tweaker::GetAboveDirectory(DirectoryObject* dir)
{
    // 指定ディレクトリを子供に持つか兄弟で持つオブジェクトを検索
    DirectoryObject* obj = dir;
    while (!IsRoot(obj))
    {
        for (int i = 0; i < OBJECT_MAX; i++)
        {
            // 子供に持つオブジェクトの場合は
            // 探索終了
            if (dirObjectList[i].child_ == obj)
            {
                return &dirObjectList[i];
            }
            // 兄弟に持つオブジェクトの場合は
            // 探索対象を変更し、もう一度探索
            if (dirObjectList[i].sibling_ == obj)
            {
                obj = &dirObjectList[i];
            }
        }
    }
    return obj;
}

/******************************************************************************
@brief  指定されたディレクトリの末尾のポインタを取得
******************************************************************************/

DirectoryObject* Tweaker::GetDirectoryEnd(DirectoryObject* dir)
{
    // 現在のディレクトリから末尾まで移動
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
@brief  オブジェクトを追加
******************************************************************************/

void Tweaker::AddObject(DirectoryObject* p)
{
    // 現在のディレクトリに他にオブジェクトがなければ
    // 子供に追加
    if (!currentDirectory->child_)
    {
        currentDirectory->child_ = p;
    }
    else
    {
        // 現在のディレクトリの末尾のポインタを取得
        DirectoryObject* end = GetDirectoryEnd(currentDirectory);

        // 末尾に追加
        end->sibling_ = p;
    }
}

/******************************************************************************
@brief  オブジェクトを削除
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
@brief  フォルダーを削除
******************************************************************************/

void Tweaker::DeleteFolder(DirectoryObject* p, const char* filePath)
{
    // フォルダーの中身を全削除
    for (DirectoryObject* it = p->child_; it != NULL;)
    {
        DirectoryObject* tmp = it->sibling_;
        // フォルダーの場合は再帰で全て削除
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

/******************************** 実装ここまで *******************************/

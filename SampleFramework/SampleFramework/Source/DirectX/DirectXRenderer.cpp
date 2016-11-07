/*****************************************************************************/
/*!
@file   DirectXRenderer.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "DirectXRenderer.h"
#include "../Framework/Error.h"
#include "DirectXVertexBuffer.h"
#include "DirectXIndexBuffer.h"


using DirectX::Renderer;
using namespace Framework;
using namespace Windows;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

DirectX::Renderer::Renderer()
{
    type = DIRECTX9;
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

DirectX::Renderer::~Renderer()
{
}

/******************************************************************************
@brief  ����������
@param  pGameWindow     �E�C���h�E���
******************************************************************************/

void DirectX::Renderer::Init(GameWindow *pGameWindow)
{
    /*
    * �f�o�C�X������
    */

    HWND hWnd = pGameWindow->GetHandle();
    HRESULT hr;

    // Direct3D�I�u�W�F�N�g�̐���
    if ((pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
    {
        Error::Message("Direct3D�I�u�W�F�N�g�̐����Ɏ��s���܂���");
        return;
    }

    // ���݂̃f�B�X�v���C���[�h���擾
    // ERR : D3DERR_INVALIDCALL
    D3DDISPLAYMODE d3ddm;
    if (FAILED(hr = pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
    {
        Error::Message("���݂̃f�B�X�v���C���[�h�̎擾�Ɏ��s���܂���");
        return;
    }

    // �p�����[�^��������
    D3DPRESENT_PARAMETERS d3dpp; 
    ZeroMemory(&d3dpp, sizeof(d3dpp));

    // �p�����[�^�ݒ�
    d3dpp.BackBufferWidth           = pGameWindow->GetWidth();      // ��ʂ̕�
    d3dpp.BackBufferHeight          = pGameWindow->GetHeight();     // ��ʂ̍���
    d3dpp.BackBufferFormat          = d3ddm.Format;                 // �o�b�N�o�b�t�@�̃t�H�[�}�b�g
    d3dpp.BackBufferCount           = 1;                            // �o�b�N�o�b�t�@�̐�
    d3dpp.SwapEffect                = D3DSWAPEFFECT_DISCARD;        // �o�b�t�@�̐ؑ֕��@
    d3dpp.EnableAutoDepthStencil    = TRUE;                         // �f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@�̐���
    d3dpp.AutoDepthStencilFormat    = D3DFMT_D24S8;                 // �f�v�X�o�b�t�@�Ƃ���24�r�b�g�g�p
    d3dpp.Windowed                  = !pGameWindow->IsFullScreen(); // �E�C���h�E�X�N���[��

    if (pGameWindow->IsFullScreen())
    {// �t���X�N���[�����[�h
        d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;                   // �o�b�N�o�b�t�@
        d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; // ���t���b�V�����[�g
        d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; // �C���^�[�o��
    }
    else
    {// �E�B���h�E���[�h
        d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;                    // �o�b�N�o�b�t�@
        d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; // ���t���b�V�����[�g
        d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; // �C���^�[�o��
    }

    // Direct3D�f�o�C�X�̐���
    // �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
    // �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
    if (FAILED(hr = pD3D->CreateDevice(D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        hWnd,
        D3DCREATE_HARDWARE_VERTEXPROCESSING,
        &d3dpp, &pD3DDev)))
    {
        // ��L�̐ݒ肪���s������
        // �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
        if (FAILED(hr = pD3D->CreateDevice(D3DADAPTER_DEFAULT,
            D3DDEVTYPE_HAL,
            hWnd,
            D3DCREATE_SOFTWARE_VERTEXPROCESSING,
            &d3dpp, &pD3DDev)))
        {
            // ��L�̐ݒ肪���s������
            // �`��ƒ��_������CPU�ōs�Ȃ�
            if (FAILED(hr = pD3D->CreateDevice(D3DADAPTER_DEFAULT,
                D3DDEVTYPE_REF,
                hWnd,
                D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                &d3dpp, &pD3DDev)))
            {
                // ���������s
                Error::Message("DirectX�̃f�o�C�X�̐����Ɏ��s���܂���");
                return;
            }
        }
    }

    // �����_�����O�X�e�[�g�p�����[�^�̐ݒ�
    pD3DDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);                // ���ʂ��J�����O
    pD3DDev->SetRenderState(D3DRS_ZENABLE, TRUE);                        // Z�o�b�t�@���g�p
    pD3DDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);                   // Z�o�b�t�@�ɏ���������
    pD3DDev->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);              // Z�e�X�g�̏�����ݒ�
    pD3DDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);               // ���u�����h���s��
    pD3DDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);          // ���\�[�X�J���[�̎w��
    pD3DDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);      // ���f�X�e�B�l�[�V�����J���[�̎w��
    pD3DDev->SetRenderState(D3DRS_LIGHTING, TRUE);                       // ���C�e�B���O���I��

    pD3DDev->SetRenderState(D3DRS_ALPHAREF, 0x00000001);                 // ���e�X�g�̔�r�l��1�ɐݒ�
    pD3DDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);                // ���e�X�g�L���� 
    pD3DDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);       // ���e�X�g�̏������u�ȏ�v�ɐݒ�

    // �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
    pD3DDev->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);     // �e�N�X�`��U���W�̓��s�[�g
    pD3DDev->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);     // �e�N�X�`��V���W�̓��s�[�g
    pD3DDev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);      // �k�����o���`���
    pD3DDev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);      // �g�厞�o���`���

    // �e�N�X�`���X�e�[�W�X�e�[�g�p�����[�^�̐ݒ�
    pD3DDev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);   // �A���t�@�u�����f�B���O����
    pD3DDev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);   // �ŏ��̃A���t�@����
    pD3DDev->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);   // �Q�Ԗڂ̃A���t�@����

}

/******************************************************************************
@brief  �I������
******************************************************************************/

void DirectX::Renderer::Uninit()
{

    // Direct3D�f�o�C�X�̊J��
    if (pD3DDev != NULL)
    {
        pD3DDev->Release();
        pD3DDev = NULL;
    }

    // Direct3D�I�u�W�F�N�g�̊J��
    if (pD3D != NULL)
    {
        pD3D->Release();
        pD3D = NULL;
    }

}

/******************************************************************************
@brief  ��ʃN���A
******************************************************************************/

void DirectX::Renderer::Clear()
{

    pD3DDev->Clear
        (0,
        NULL,
        (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL),
        D3DCOLOR_XRGB(0, 0, 0),
        1.0f,
        0);

    pD3DDev->BeginScene();
}

/******************************************************************************
@brief  �o�b�N�o�b�t�@�\��
******************************************************************************/

void DirectX::Renderer::Flip()
{
    pD3DDev->EndScene();
    pD3DDev->Present(NULL, NULL, NULL, NULL);
}

/******************************************************************************
@brief  ���C�g�ݒ�
@param  index                   �C���f�b�N�X
@param  Framework::pLight       ���C�g���
******************************************************************************/

void DirectX::Renderer::SetLight(int index, Framework::Light *pLight)
{
    D3DLIGHT9 light;
    ZeroMemory(&light, sizeof(D3DLIGHT9));
    switch (pLight->type)
    {
    case Light::POINT       :   light.Type = D3DLIGHT_POINT;        break;
    case Light::DIRECTIONAL :   light.Type = D3DLIGHT_DIRECTIONAL;  break;
    case Light::SPOT        :   light.Type = D3DLIGHT_SPOT;         break;
    }
    light.Diffuse = D3DXCOLOR(pLight->diffuse.r, pLight->diffuse.g, pLight->diffuse.b, pLight->diffuse.a);
    light.Ambient = D3DXCOLOR(pLight->ambient.r, pLight->ambient.g, pLight->ambient.b, pLight->ambient.a);
    D3DXVECTOR3 vecDir = D3DXVECTOR3(pLight->direction.x, pLight->direction.y, pLight->direction.z);
    D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);
    pD3DDev->SetLight(index, &light);

}

/******************************************************************************
@brief  ���C�g�ݒ�
@param  index       �C���f�b�N�X
@param  isLight     ���C�g��ON��OFF���ǂ���
******************************************************************************/

void DirectX::Renderer::SetLight(int index, bool isLight)
{
    (isLight) ? (pD3DDev->LightEnable(index, TRUE)) : (pD3DDev->LightEnable(index, FALSE));
}

/******************************************************************************
@brief  ���C�g��ONOFF�ݒ�
@param  isLight     ���C�g��ON��OFF���ǂ���
******************************************************************************/

void DirectX::Renderer::SetLightEnable(bool isLight)
{
    (isLight) ? (pD3DDev->SetRenderState(D3DRS_LIGHTING, TRUE)) : (pD3DDev->SetRenderState(D3DRS_LIGHTING, FALSE));
}

/******************************************************************************
@brief  �e�N�X�`���o�^
@param  pTexture                �o�^����e�N�X�`��
******************************************************************************/

void DirectX::Renderer::SetTexture(Framework::Texture *pTexture)
{
    pTex = (DirectX::Texture*)pTexture;
    // �e�N�X�`���ݒ�
    if (pTex != NULL)
        pD3DDev->SetTexture(0, pTex->GetResource());
    else
        pD3DDev->SetTexture(0, NULL);
}

/******************************************************************************
@brief  �}�e���A���ݒ�
@param  pMaterial   �}�e���A��
******************************************************************************/

void DirectX::Renderer::SetMaterial(Framework::Material *pMaterial)
{
    D3DMATERIAL9 material;

    if (pMaterial)
    {
        material.Diffuse.r = pMaterial->diffuse.r;
        material.Diffuse.g = pMaterial->diffuse.g;
        material.Diffuse.b = pMaterial->diffuse.b;
        material.Diffuse.a = pMaterial->diffuse.a;

        material.Ambient.r = pMaterial->ambient.r;
        material.Ambient.g = pMaterial->ambient.g;
        material.Ambient.b = pMaterial->ambient.b;
        material.Ambient.a = pMaterial->ambient.a;

        material.Specular.r = pMaterial->specular.r;
        material.Specular.g = pMaterial->specular.g;
        material.Specular.b = pMaterial->specular.b;
        material.Specular.a = pMaterial->specular.a;

        material.Emissive.r = pMaterial->emissive.r;
        material.Emissive.g = pMaterial->emissive.g;
        material.Emissive.b = pMaterial->emissive.b;
        material.Emissive.a = pMaterial->emissive.a;

        material.Power = pMaterial->power;
    }
    else
    {
        // �W���}�e���A���ݒ�
        material.Diffuse.r = 1.0f;
        material.Diffuse.g = 1.0f;
        material.Diffuse.b = 1.0f;
        material.Diffuse.a = 1.0f;

        material.Ambient.r = 0.8f;
        material.Ambient.g = 0.8f;
        material.Ambient.b = 0.8f;
        material.Ambient.a = 1.0f;

        material.Specular.r = 0.0f;
        material.Specular.g = 0.0f;
        material.Specular.b = 0.0f;
        material.Specular.a = 0.0f;

        material.Emissive.r = 0.0f;
        material.Emissive.g = 0.0f;
        material.Emissive.b = 0.0f;
        material.Emissive.a = 0.0f;

        material.Power = 0.0f;
    }

    pD3DDev->SetMaterial(&material);

}

/******************************************************************************
@brief  �u�����h���[�h�ݒ�
@param  SrcBlend    �\�[�X�u�����h
@param  DestBlend   �f�B�X�g�u�����h
******************************************************************************/

void DirectX::Renderer::SetBlend(Blend SrcBlend, Blend DestBlend)
{

    _D3DBLEND srcBlend, destBlend;

    switch (SrcBlend)
    {
    case BLEND_ZERO         : srcBlend = D3DBLEND_ZERO;         break;
    case BLEND_ONE          : srcBlend = D3DBLEND_ONE;          break;
    case BLEND_SRC_COLOR    : srcBlend = D3DBLEND_SRCCOLOR;     break;
    case BLEND_SRC_INVCOLOR : srcBlend = D3DBLEND_INVSRCCOLOR;  break;
    case BLEND_SRC_ALPHA    : srcBlend = D3DBLEND_SRCALPHA;     break;
    case BLEND_SRC_INVALPHA : srcBlend = D3DBLEND_INVSRCALPHA;  break;

    case BLEND_DEST_COLOR   : srcBlend = D3DBLEND_DESTCOLOR;    break;
    case BLEND_DEST_INVCOLOR: srcBlend = D3DBLEND_INVDESTCOLOR; break;
    case BLEND_DEST_ALPHA   : srcBlend = D3DBLEND_DESTALPHA;    break;
    case BLEND_DEST_INVALPHA: srcBlend = D3DBLEND_INVDESTALPHA; break;
    }

    switch (DestBlend)
    {
    case BLEND_ZERO         : destBlend = D3DBLEND_ZERO;         break;
    case BLEND_ONE          : destBlend = D3DBLEND_ONE;          break;
    case BLEND_SRC_COLOR    : destBlend = D3DBLEND_SRCCOLOR;     break;
    case BLEND_SRC_INVCOLOR : destBlend = D3DBLEND_INVSRCCOLOR;  break;
    case BLEND_SRC_ALPHA    : destBlend = D3DBLEND_SRCALPHA;     break;
    case BLEND_SRC_INVALPHA : destBlend = D3DBLEND_INVSRCALPHA;  break;

    case BLEND_DEST_COLOR   : destBlend = D3DBLEND_DESTCOLOR;    break;
    case BLEND_DEST_INVCOLOR: destBlend = D3DBLEND_INVDESTCOLOR; break;
    case BLEND_DEST_ALPHA   : destBlend = D3DBLEND_DESTALPHA;    break;
    case BLEND_DEST_INVALPHA: destBlend = D3DBLEND_INVDESTALPHA; break;
    }

    pD3DDev->SetRenderState(D3DRS_SRCBLEND, srcBlend);
    pD3DDev->SetRenderState(D3DRS_DESTBLEND, destBlend);

}

/******************************************************************************
@brief  Z�e�X�gONOFF�ݒ�
@param  isZEnable   Z�e�X�g�L�������t���O
******************************************************************************/

void DirectX::Renderer::SetZTestEnable(bool isZEnable)
{
    (isZEnable) ?
        (pD3DDev->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL)) :
        (pD3DDev->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS));
}

/******************************************************************************
@brief  Z�o�b�t�@����ONOFF�ݒ�
@param  isZEnable   Z�o�b�t�@�����L�������t���O
******************************************************************************/

void DirectX::Renderer::SetZWriteEnable(bool isZEnable)
{
    (isZEnable) ?
        (pD3DDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE)) :
        (pD3DDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE));
}

/******************************************************************************
@brief  ���e�X�gONOFF�ݒ�
@param  isAlphaEnable   ���e�X�g�L�������t���O
******************************************************************************/

void DirectX::Renderer::SetAlphaTestEnable(bool isAlphaEnable)
{
    if (isAlphaEnable)
    {
        pD3DDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
        pD3DDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
        pD3DDev->SetRenderState(D3DRS_ALPHAREF, 0x88);
    }
    else
    {
        pD3DDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
        pD3DDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
    }
}

/******************************************************************************
@brief  �T���v���[�X�e�[�g�ݒ�
@param  ssType      �T���v���[�X�e�[�g�^�C�v
@param  ta          �e�N�X�`���A�h���X�^�C�v
******************************************************************************/

void DirectX::Renderer::SetSamplerState(SamplerStateType ssType, TextureAddress ta)
{
    pD3DDev->SetSamplerState(0, (D3DSAMPLERSTATETYPE)ssType, (D3DSAMPLERSTATETYPE)ta);
}

/******************************************************************************
@brief  ���_�J���[ONOFF�ݒ�
@param  isEnable    ���_�J���[�L�������t���O
******************************************************************************/

void DirectX::Renderer::SetVertexColorEnable(bool isEnable)
{
    if (isEnable)
    {
        pD3DDev->SetRenderState(D3DRS_COLORVERTEX, TRUE);
        pD3DDev->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
        pD3DDev->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);
        pD3DDev->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_COLOR1);
        pD3DDev->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_COLOR1);
    }
    else
    {
        pD3DDev->SetRenderState(D3DRS_COLORVERTEX, FALSE);
        pD3DDev->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
        pD3DDev->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
        pD3DDev->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);
        pD3DDev->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);
    }
}

/******************************************************************************
@brief  �e�N�X�`��ONOFF�ݒ�
@param  isEnable    �e�N�X�`���L�������t���O
******************************************************************************/

void DirectX::Renderer::SetTextureEnable(bool isEnable)
{
    (isEnable) ?
        (pD3DDev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE)) :
        (pD3DDev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_DISABLE));
}

/******************************************************************************
@brief  ���C���[�t���[��ONOFF�ݒ�
@param  isEnable    ���C���[�t���[���L�������t���O
******************************************************************************/

void DirectX::Renderer::SetWireFrameEnable(bool isEnable)
{
    (isEnable) ? 
        (pD3DDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME)) :
        (pD3DDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID)) ;
}

/******************************************************************************
@brief  �J�����OONOFF�ݒ�
@param  isEnable    �J�����O�L�������t���O
******************************************************************************/

void DirectX::Renderer::SetCullingEnable(bool isEnable)
{
    (isEnable) ?
        (pD3DDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW)) :
        (pD3DDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE));
}

/******************************************************************************
@brief  ���_�o�b�t�@����
@param  vertexNum       ���_��
@return VertexBuffer*   �������ꂽ���_�o�b�t�@
******************************************************************************/

Framework::VertexBuffer* DirectX::Renderer::CreateVertexBuffer(int vertexNum)
{
    VertexBuffer* pVertexBuffer = new VertexBuffer;

    pD3DDev->CreateVertexBuffer(sizeof(VERTEX_3D) * vertexNum,  // ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
        D3DUSAGE_WRITEONLY,                                     // ���_�o�b�t�@�̎g�p�@�@
        FVF_VERTEX_3D,                                          // �g�p���钸�_�t�H�[�}�b�g
        D3DPOOL_MANAGED,                                        // ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
        &pVertexBuffer->pVertexBuffer,                          // ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
        NULL);

    pVertexBuffer->vertexNum = vertexNum;
    return pVertexBuffer;
}

/******************************************************************************
@brief  �C���f�b�N�X�o�b�t�@����
@param  indexNum        �C���f�b�N�X��
@return IndexBuffer*    �������ꂽ�C���f�b�N�X�o�b�t�@
******************************************************************************/

Framework::IndexBuffer* DirectX::Renderer::CreateIndexBuffer(int indexNum)
{
    IndexBuffer* pIndexBuffer = new IndexBuffer;

    pD3DDev->CreateIndexBuffer(sizeof(int) * indexNum,  // �C���f�b�N�X�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
        D3DUSAGE_WRITEONLY,                             // �C���f�b�N�X�o�b�t�@�̎g�p�@�@
        D3DFMT_INDEX32,                                 // �g�p����C���f�b�N�X�t�H�[�}�b�g
        D3DPOOL_MANAGED,                                // ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
        &pIndexBuffer->pIndexBuffer,                    // �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
        NULL);

    pIndexBuffer->indexNum = indexNum;
    return pIndexBuffer;
}

/******************************************************************************
@brief  �v���~�e�B�u�`��(���̂܂�)
@param  PriType     �`����@
@param  pVertex     ���_���ւ̃|�C���^
@param  vtxNum      ���_��
******************************************************************************/

void DirectX::Renderer::DrawPrimitiveUP(
    Framework::Renderer::PrimitiveType PriType,
    const Framework::Vertex *pVertex, int PriNum)
{
    // �r���[�|�[�g�̐ݒ�
    pD3DDev->SetViewport((D3DVIEWPORT9*)&pCamera->vp);
    // �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
    pD3DDev->SetTransform(D3DTS_PROJECTION, (D3DXMATRIX*)&ProjectionMatrix);
    // �r���[�}�g���b�N�X�̐ݒ�
    pD3DDev->SetTransform(D3DTS_VIEW, (D3DXMATRIX*)&ViewMatrix);
    // ���[���h�}�g���b�N�X�̐ݒ�
    pD3DDev->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)&WorldMatrix);

    // �|���S���`��
    pD3DDev->SetFVF(FVF_VERTEX_3D);
    switch (PriType)
    {
    case PRIMITIVE_TYPE_LINE_STRIP:
        pD3DDev->DrawPrimitiveUP(D3DPT_LINESTRIP, PriNum, pVertex, sizeof(Vertex));
        break;
    case PRIMITIVE_TYPE_TRIANGLE_STRIP:
        pD3DDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, PriNum, pVertex, sizeof(Vertex));
        break;
    }
}

/******************************************************************************
@brief  �C���f�b�N�X�t���v���~�e�B�u�`��(���̂܂�)
@param  PriType             �`����@
@param  BaseVertexIndex     
@param  MinIndex            
@param  NumVertices         
@param  StartIndex          
@param  pVertex             ���_���ւ̃|�C���^
@param  vtxNum              ���_��
******************************************************************************/

void DirectX::Renderer::DrawIndexedPrimitiveUP(
    Framework::Renderer::PrimitiveType PriType,
    unsigned int StartIndex,
    unsigned int VertexNum,
    const int *pIndex,
    const Framework::Vertex *pVertex,
    unsigned int Count)
{
    // �r���[�|�[�g�̐ݒ�
    pD3DDev->SetViewport((D3DVIEWPORT9*)&pCamera->vp);
    // �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
    pD3DDev->SetTransform(D3DTS_PROJECTION, (D3DXMATRIX*)&ProjectionMatrix);
    // �r���[�}�g���b�N�X�̐ݒ�
    pD3DDev->SetTransform(D3DTS_VIEW, (D3DXMATRIX*)&ViewMatrix);
    // ���[���h�}�g���b�N�X�̐ݒ�
    pD3DDev->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)&WorldMatrix);

    // �|���S���`��
    pD3DDev->SetFVF(FVF_VERTEX_3D);
    switch (PriType)
    {
    case PRIMITIVE_TYPE_TRIANGLE_STRIP:
        pD3DDev->DrawIndexedPrimitiveUP(D3DPT_TRIANGLESTRIP, 0, VertexNum, Count - StartIndex - 2, &pIndex[StartIndex], D3DFMT_INDEX32, pVertex, sizeof(Vertex));
        break;

    case PRIMITIVE_TYPE_TRIANGLE_LIST:
        pD3DDev->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, VertexNum, Count, &pIndex[StartIndex], D3DFMT_INDEX32, pVertex, sizeof(Vertex));
        break;
    }
}

/******************************************************************************
@brief  �v���~�e�B�u�`��(���_�o�b�t�@)
@param  PriType     �`����@
******************************************************************************/

void DirectX::Renderer::DrawPrimitive(
    Framework::Renderer::PrimitiveType PriType)
{
    // �r���[�|�[�g�̐ݒ�
    pD3DDev->SetViewport((D3DVIEWPORT9*)&pCamera->vp);
    // �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
    pD3DDev->SetTransform(D3DTS_PROJECTION, (D3DXMATRIX*)&ProjectionMatrix);
    // �r���[�}�g���b�N�X�̐ݒ�
    pD3DDev->SetTransform(D3DTS_VIEW, (D3DXMATRIX*)&ViewMatrix);
    // ���[���h�}�g���b�N�X�̐ݒ�
    pD3DDev->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)&WorldMatrix);

    // �|���S���`��
    VertexBuffer* pVtxBuf = (VertexBuffer*)pVertexBuffer;
    pD3DDev->SetStreamSource(0, pVtxBuf->pVertexBuffer, 0, sizeof(VERTEX_3D));
    pD3DDev->SetFVF(FVF_VERTEX_3D);
    switch (PriType)
    {
    case PRIMITIVE_TYPE_LINE_STRIP:
        pD3DDev->DrawPrimitive(D3DPT_LINESTRIP, 0, pVtxBuf->vertexNum-1);
        break;
    case PRIMITIVE_TYPE_TRIANGLE_STRIP:
        pD3DDev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, pVtxBuf->vertexNum-2);
        break;
    case PRIMITIVE_TYPE_TRIANGLE_LIST:
        pD3DDev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, pVtxBuf->vertexNum/3);
        break;
    }

}

/******************************************************************************
@brief  �C���f�b�N�X�t���v���~�e�B�u�`��(���_�o�b�t�@)
@param  PriType         �`����@
@param  StartIndex      �J�n�C���f�b�N�X
@param  Count           
******************************************************************************/

void DirectX::Renderer::DrawIndexedPrimitive(
    Framework::Renderer::PrimitiveType PriType,
    int StartIndex,
    int Count)
{
    // �r���[�|�[�g�̐ݒ�
    pD3DDev->SetViewport((D3DVIEWPORT9*)&pCamera->vp);
    // �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
    pD3DDev->SetTransform(D3DTS_PROJECTION, (D3DXMATRIX*)&ProjectionMatrix);
    // �r���[�}�g���b�N�X�̐ݒ�
    pD3DDev->SetTransform(D3DTS_VIEW, (D3DXMATRIX*)&ViewMatrix);
    // ���[���h�}�g���b�N�X�̐ݒ�
    pD3DDev->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)&WorldMatrix);

    // �|���S���`��
    VertexBuffer* pVtxBuf = (VertexBuffer*)pVertexBuffer;
    IndexBuffer* pIdxBuf = (IndexBuffer*)pIndexBuffer;
    pD3DDev->SetStreamSource(0, pVtxBuf->pVertexBuffer, 0, sizeof(VERTEX_3D));
    pD3DDev->SetFVF(FVF_VERTEX_3D);
    pD3DDev->SetIndices(pIdxBuf->pIndexBuffer);
    switch (PriType)
    {
    case PRIMITIVE_TYPE_LINE_STRIP:
        pD3DDev->DrawIndexedPrimitive(D3DPT_LINESTRIP, 0, 0, pVtxBuf->vertexNum, StartIndex, Count);
        break;
    case PRIMITIVE_TYPE_TRIANGLE_STRIP:
        pD3DDev->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, pVtxBuf->vertexNum, StartIndex, Count);
        break;
    case PRIMITIVE_TYPE_TRIANGLE_LIST:
        pD3DDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, pVtxBuf->vertexNum, StartIndex, Count);
        break;
    }
}

/******************************* ���������܂� ********************************/
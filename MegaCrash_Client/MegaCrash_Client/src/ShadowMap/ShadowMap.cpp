#include "stdafx.h"
#include "Light/Light.h"
#include "ShadowMap.h"

CShadowMap::CShadowMap(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList*	pd3dCmdLst)
	: m_pLight{ nullptr }
{
	m_matTexture = { 
		  0.5f, 0.0f, 0.0f, 0.0f
		, 0.0f, -0.5f, 0.0f, 0.0f
		, 0.0f, 0.0f, 1.0f, 0.0f
		, 0.5f, 0.5f, 0.0f, 1.0f };

	m_pDSVDescHeap = make_shared<DescriptorHeap>(
		  pd3dDevice
		, D3D12_DESCRIPTOR_HEAP_TYPE_DSV
		, 1
		, D3D12_DESCRIPTOR_HEAP_FLAG_NONE);
	
	D3D12_CLEAR_VALUE d3dClearValue;
	d3dClearValue.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	d3dClearValue.DepthStencil.Depth = 1.0f;
	d3dClearValue.DepthStencil.Stencil = 0;

	m_DepthStencilBuf.pResource = CD3DBufMgr::Instance()->CreateTexture2DResource(
		  SHADOW_MAP_WIDTH
		, SHADOW_MAP_HEIGHT
		, DXGI_FORMAT_R24G8_TYPELESS
		, D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL
		, D3D12_RESOURCE_STATE_GENERIC_READ
		, &d3dClearValue
	);
	m_pDSVDescHeap->CreateView(pd3dDevice, m_DepthStencilBuf, 0);

	m_pLightCamera = new CCamera();
	m_pLightCamera->SetTimeLag(0.0f);
	m_pLightCamera->SetOffset(XMFLOAT3(0.0f, 0.0f, 0.0f));
	//m_pLightCamera->GenerateProjectionMatrix(1.01f, FAR_DISTANCE * 2, ASPECT_RATIO, 60.0f);
	m_pLightCamera->GenerateOrthographicMatrix(1.01f, 86603.f, 40000.f, 40000.f);
	m_pLightCamera->SetViewport(0, 0, SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT, 0.0f, 1.0f);
	m_pLightCamera->SetScissorRect(0, 0, SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT);
	m_pLightCamera->GenerateViewMatrix(
		  XMFLOAT3(0.0f, 40000.f, 0.0f)
		, XMFLOAT3(25000.f, 15000.f, 25000.f)
		, XMFLOAT3(0, 1, 0));
	m_pLightCamera->GenerateFrustum();

	m_cbInfo.m_matVPT = XMMatrixTranspose(XMLoadFloat4x4(
		&Matrix4x4::Multiply(Matrix4x4::Multiply(
			  m_pLightCamera->GetViewMatrix()
			, m_pLightCamera->GetProjectionMatrix())
			, m_matTexture)));
}

CShadowMap::~CShadowMap()
{
	delete m_pLightCamera;
}

void CShadowMap::CreateShaderVariables(ID3D12Device * pd3dDevice, ID3D12GraphicsCommandList * pd3dCmdLst)
{
	m_pLightCamera->CreateShaderVariables(pd3dDevice, pd3dCmdLst);
	CD3DBufMgr::Instance()->AllocUploadBuffer(m_cbDesc, sizeof(m_cbInfo));
	m_pcbMapped = static_cast<CB_INFO*>(m_cbDesc.pMappedPtr);
	m_cbDesc.RootParamIdx = ROOT_PARAMETER_CONSTANT2;
}

void CShadowMap::UpdateShaderVariables(ID3D12GraphicsCommandList * pd3dCmdLst)
{
	::memcpy(m_pcbMapped, &m_cbInfo, sizeof(m_cbInfo));
	pd3dCmdLst->SetGraphicsRootConstantBufferView(m_cbDesc.RootParamIdx, m_cbDesc.view_desc.BufferLocation);
}

void CShadowMap::Render(ID3D12GraphicsCommandList * pd3dCmdLst, CCamera * pCamera)
{
	UpdateShaderVariables(pd3dCmdLst);
}

void CShadowMap::RenderShadowMap(ID3D12GraphicsCommandList * pd3dCmdLst)
{
	m_pLightCamera->SetViewportsAndScissorRects(pd3dCmdLst);
	m_pLightCamera->UpdateShaderVariables(pd3dCmdLst);
}

void CShadowMap::SetLight(CLight::LIGHT_PARAMETER * pLight)
{
	m_pLight = pLight;
}
//-----------------------------------------------------------------------------
// File: Shader.h
//-----------------------------------------------------------------------------

#pragma once

#include "Object\Object.h"
#include "Camera\Camera.h"
#include "Texture\Texture.h"

class CShader {
public:
	CShader(ID3D12Device* pd3dDevice) {}
	virtual ~CShader() {}
	virtual void Render(ID3D12GraphicsCommandList *pd3dCmdLst, CCamera *pCamera) {
		pd3dCmdLst->SetPipelineState(m_pPipelineState->Get());
	}

protected:
	shared_ptr<GraphicsPipelineStateObject>		m_pPipelineState;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CSkyBoxShader : public CShader {
public:
	CSkyBoxShader(ID3D12Device* pd3dDevice);
	virtual ~CSkyBoxShader() {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CCubeShader : public CShader {
public:
	CCubeShader(ID3D12Device* pd3dDevice);
	virtual ~CCubeShader() {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CStageShader : public CShader {
public:
	CStageShader(ID3D12Device* pd3dDevice);
	virtual ~CStageShader() {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CModelShader : public CShader {
public:
	CModelShader(ID3D12Device* pd3dDevice);
	virtual ~CModelShader() {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CAnimationShader : public CShader {
public:
	CAnimationShader(ID3D12Device* pd3dDevice);
	virtual ~CAnimationShader() {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CSkyBoxDeferredShader : public CShader {
public:
	CSkyBoxDeferredShader(ID3D12Device* pd3dDevice);
	virtual ~CSkyBoxDeferredShader() {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CCubeDeferredShader : public CShader {
public:
	CCubeDeferredShader(ID3D12Device* pd3dDevice);
	virtual ~CCubeDeferredShader() {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CStageDeferredShader : public CShader {
public:
	CStageDeferredShader(ID3D12Device* pd3dDevice);
	virtual ~CStageDeferredShader() {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CModelDeferredShader : public CShader {
public:
	CModelDeferredShader(ID3D12Device* pd3dDevice);
	virtual ~CModelDeferredShader() {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CAnimationDeferredShader : public CShader {
public:
	CAnimationDeferredShader(ID3D12Device* pd3dDevice);
	virtual ~CAnimationDeferredShader() {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CDeferredLightingShader : public CShader {
public:
	CDeferredLightingShader(ID3D12Device* pd3dDevice);
	virtual ~CDeferredLightingShader() {}
	virtual void Render(ID3D12GraphicsCommandList *pd3dCmdLst, CCamera *pCamera);

	void SetRTTexture(const shared_ptr<CTexture>& pTexture) { m_pTexture = pTexture; }

private:
	shared_ptr<CTexture>			m_pTexture;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CBlendRenderTargetShader : public CShader {
public:
	CBlendRenderTargetShader(ID3D12Device* pd3dDevice);
	virtual ~CBlendRenderTargetShader() {}
	virtual void Render(ID3D12GraphicsCommandList *pd3dCmdLst, CCamera *pCamera);

	void SetRTTexture(const shared_ptr<CTexture>& pTexture) { m_pTexture = pTexture; }
	void SetRTIndex(UINT RT_IDX) { m_RT_IDX = RT_IDX; }

private:
	shared_ptr<CTexture>			m_pTexture;
	UINT							m_RT_IDX;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CHUDUIShader : public CShader {
public:
	CHUDUIShader(ID3D12Device* pd3dDevice);
	virtual ~CHUDUIShader() {}
	virtual void Render(ID3D12GraphicsCommandList *pd3dCmdLst, CCamera *pCamera);

private:
	CTexture*						m_pTexture;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CRaderUIShader : public CShader {
public:
	CRaderUIShader(ID3D12Device* pd3dDevice);
	virtual ~CRaderUIShader() {}
	virtual void Render(ID3D12GraphicsCommandList *pd3dCmdLst, CCamera *pCamera);

private:
	CTexture*						m_pTexture;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CSkillIconShader : public CShader {
public:
	CSkillIconShader(ID3D12Device* pd3dDevice);
	virtual ~CSkillIconShader() {}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CCrossHairShader : public CShader {
public:
	CCrossHairShader(ID3D12Device* pd3dDevice);
	virtual ~CCrossHairShader() {}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CFontShader : public CShader {
public:
	CFontShader(ID3D12Device* pd3dDevice);
	virtual ~CFontShader() {}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CLogoShader : public CShader {
public:
	CLogoShader(ID3D12Device* pd3dDevice);
	virtual ~CLogoShader() {}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CTitleShader : public CShader {
public:
	CTitleShader(ID3D12Device* pd3dDevice);
	virtual ~CTitleShader() {}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CLobbyWindowShader : public CShader {
public:
	CLobbyWindowShader(ID3D12Device* pd3dDevice);
	virtual ~CLobbyWindowShader() {}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CLobbyRoomSlotShader : public CShader {
public:
	CLobbyRoomSlotShader(ID3D12Device* pd3dDevice);
	virtual ~CLobbyRoomSlotShader() {}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CButtonShader : public CShader {
public:
	CButtonShader(ID3D12Device* pd3dDevice);
	virtual ~CButtonShader() {}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CGameoverShader : public CShader {
public:
	CGameoverShader(ID3D12Device* pd3dDevice);
	virtual ~CGameoverShader() {}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CDeathUIShader : public CShader {
public:
	CDeathUIShader(ID3D12Device* pd3dDevice);
	virtual ~CDeathUIShader() {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CPlayerUIShader : public CShader {
public:
	CPlayerUIShader(ID3D12Device* pd3dDevice);
	virtual ~CPlayerUIShader() {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CParticleBillboardShader : public CShader {
public:
	CParticleBillboardShader(ID3D12Device* pd3dDevice);
	virtual ~CParticleBillboardShader() {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CAdvancedParticleAdditiveBillboardShader : public CShader {
public:
	CAdvancedParticleAdditiveBillboardShader(ID3D12Device* pd3dDevice);
	virtual ~CAdvancedParticleAdditiveBillboardShader() {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CAdvancedParticleAlphaBlendBillboardShader : public CShader {
public:
	CAdvancedParticleAlphaBlendBillboardShader(ID3D12Device* pd3dDevice);
	virtual ~CAdvancedParticleAlphaBlendBillboardShader() {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CStageShadowMapShader : public CShader {
public:
	CStageShadowMapShader(ID3D12Device* pd3dDevice);
	virtual ~CStageShadowMapShader() {}
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CCubeShadowMapShader : public CShader {
public:
	CCubeShadowMapShader(ID3D12Device* pd3dDevice);
	virtual ~CCubeShadowMapShader() {}
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CModelShadowMapShader : public CShader {
public:
	CModelShadowMapShader(ID3D12Device* pd3dDevice);
	virtual ~CModelShadowMapShader() {}
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CAnimShadowMapShader : public CShader {
public:
	CAnimShadowMapShader(ID3D12Device* pd3dDevice);
	virtual ~CAnimShadowMapShader() {}
};
#pragma once

class CTexture
{
public:
	struct TextureSet
	{
		static constexpr UINT MAX_VIEWS{ 10 };
		vector<SR_DESC> tex_desc;
	};

private:
	eTex::Type								m_nTextureType;
	vector<TextureSet>						m_vecTextureSet;
	DescriptorHeap*							m_pHeap;
	ID3D12DescriptorHeap**					m_ppHeapSetter;

public:
	CTexture(
		  int							numTextureSet
		, ID3D12Device*					pd3dDevice
		, D3D12_DESCRIPTOR_HEAP_TYPE	heap_type
		, eTex::Type					eTextureType = eTex::Type::RESOURCE_TEXTURE2D);
	virtual ~CTexture();

	void CreateTextureSet(
		  UINT							set_idx
		, UINT							num_views
		, UINT							rootparam_idx);
	void SetTexture(
		  ID3D12Device*					pd3dDevice
		, UINT							set_idx
		, UINT							view_idx
		, ID3D12Resource*				pTexture);
	void SetTexture(
		  ID3D12Device*					pd3dDevice
		, UINT							set_idx
		, UINT							view_idx
		, ID3D12Resource*				pTexture
		, DXGI_FORMAT					view_format);

	void UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCmdLst);
	void UpdateShaderVariable(ID3D12GraphicsCommandList *pd3dCmdLst, UINT set_idx, UINT view_idx);

	eTex::Type GetTextureType() { return(m_nTextureType); }
};

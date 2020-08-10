#include "GuiButton.h"
#include "GuiUtils.h"

namespace Vektoria
{
	void CGuiButton::Init(CDeviceCursor* deviceCursor, CWritingFont* font)
	{
		this->Init(deviceCursor, font, m_zfrBase);
	}

	void CGuiButton::Init(CDeviceCursor* deviceCursor, CWritingFont* font, CFloatRect& floatRect)
	{
		CGuiElement::Init(deviceCursor, font, floatRect);
		m_acName = "CGuiButton";

		m_zmBase.MakeTextureSprite("gui\\resources\\GuiButton_Normal.png");
		m_zmBase.SetTransparencyOn();
		m_zmBase.SetTransparency(0.0f);

		m_zmHover.MakeTextureSprite("gui\\resources\\GuiButton_Hover.png");
		m_zmHover.SetTransparencyOn();
		m_proot->AddMaterial(&m_zmHover);

		m_zmClick.MakeTextureSprite("gui\\resources\\GuiButton_Click.png");
		m_zmClick.SetTransparencyOn();
		m_proot->AddMaterial(&m_zmClick);

		float fFontHeight = 0.4f;
		m_zwLabel.SetRect(CFloatRect(0.0f, 0.5f * (1.0f - fFontHeight), 1.0f, fFontHeight));
	}


	void CGuiButton::SetLabel(std::string text)
	{
		text = Center(text, m_iLabelLength);
		CGuiElement::SetLabel(text);
	}

	void CGuiButton::SetMaterialNormal(CMaterial& material)
	{
		m_zmBase = material;
	}

	void CGuiButton::SetMaterialHover(CMaterial& material)
	{
		m_zmHover = material;
	}

	void CGuiButton::SetMaterialClick(CMaterial& material)
	{
		m_zmClick = material;
	}

	void CGuiButton::Tick(float& fTimeDelta, CFloatRect& floatrectFather)
	{
		CGuiElement::Tick(fTimeDelta, floatrectFather);

		// Change button visuals depending on current state
		SetMaterial(&m_zmBase);

		if (m_bIsHovered) {
			SetMaterial(&m_zmHover);
		}

		if (m_bIsGrabbed || m_bIsClicked) {
			SetMaterial(&m_zmClick);
		}
	}
}
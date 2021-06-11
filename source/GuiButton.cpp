#include "GuiButton.h"
#include "GuiUtils.h"

namespace VektoriaGui
{
	void CGuiButton::Init(V::CDeviceCursor* deviceCursor, V::CWritingFont* font)
	{
		this->Init(deviceCursor, font, m_zfrBase);
	}

	void CGuiButton::Init(V::CDeviceCursor* deviceCursor, V::CWritingFont* font, V::CFloatRect& floatRect)
	{
		CGuiElement::Init(deviceCursor, font, floatRect);
		m_acName = "CGuiButton";

		m_zmBase.MakeTextureSprite(&(vektoria_gui_path + "\\resources\\GuiButton_Normal.png")[0]);
		m_zmBase.SetTransparencyOn();
		m_zmBase.SetTransparency(0.0f);

		m_zmHover.MakeTextureSprite(&(vektoria_gui_path + "\\resources\\GuiButton_Hover.png")[0]);
		m_zmHover.SetTransparencyOn();
		m_proot->AddMaterial(&m_zmHover);

		m_zmClick.MakeTextureSprite(&(vektoria_gui_path + "\\resources\\GuiButton_Click.png")[0]);
		m_zmClick.SetTransparencyOn();
		m_proot->AddMaterial(&m_zmClick);

		float fFontHeight = 0.4f;
		m_zwLabel.SetRect(V::CFloatRect(0.0f, 0.5f * (1.0f - fFontHeight), 1.0f, fFontHeight));
	}


	void CGuiButton::SetLabel(std::string text)
	{
		text = alignCenter(text, m_iLabelLength);
		CGuiElement::SetLabel(text);
	}

	void CGuiButton::SetMaterialNormal(V::CMaterial& material)
	{
		m_zmBase = material;
	}

	void CGuiButton::SetMaterialHover(V::CMaterial& material)
	{
		m_zmHover = material;
	}

	void CGuiButton::SetMaterialClick(V::CMaterial& material)
	{
		m_zmClick = material;
	}

	void CGuiButton::Tick(float& fTimeDelta, V::CFloatRect& floatrectFather)
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
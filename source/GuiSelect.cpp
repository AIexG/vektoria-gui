#include "GuiSelect.h"

namespace VektoriaGui
{
	CGuiSelect::~CGuiSelect()
	{
		// delete all option pointers
		for (auto itO : m_vOptions) {
			delete itO;
		}
		m_vOptions.clear();
	}

	void CGuiSelect::Init(V::CDeviceCursor* deviceCursor, V::CWritingFont* font)
	{
		this->Init(deviceCursor, font, 4, m_zfrBase);
	}

	void CGuiSelect::Init(V::CDeviceCursor* deviceCursor, V::CWritingFont* font, int optionsVisible)
	{
		this->Init(deviceCursor, font, optionsVisible, m_zfrBase);
	}

	void CGuiSelect::Init(V::CDeviceCursor* deviceCursor, V::CWritingFont* font, int optionsVisible, V::CFloatRect& floatRect)
	{
		CGuiElement::Init(deviceCursor, font, floatRect);
		m_acName = "CGuiSelect";

		// Styling base overlay
		m_zmBase.MakeTextureSprite(&(vektoria_gui_path + "\\resources\\GuiElement_Background.jpg")[0]);
		
		// Styling Interactable
		m_zoInteractable.SetRect(V::CFloatRect(0.05f, 0.25f, 0.9f, 0.7f));

		// Label writing
		SetLabelRect(V::CFloatRect(0.05f, 0.1f, 0.9f, 0.1f));

		// Options
		m_iOptionsVisible = optionsVisible;
		if (m_iOptionsVisible <= 0) {
			m_iOptionsVisible = 4;
		}
		m_zfrOptionBase = V::CFloatRect(0.0f, 0.0f, 0.8f, 1.0f / m_iOptionsVisible);

		// Option active states
		m_zmOptionActive.MakeTextureSprite(&(vektoria_gui_path + "\\resources\\GuiSelect_Option_Active.png")[0]);
		m_zmOptionActive.SetTransparencyOn();
		m_zmOptionActive.SetTransparency(0.2f);
		m_proot->AddMaterial(&m_zmOptionActive);
		m_zmOptionInactive.MakeTextureSprite(&(vektoria_gui_path + "\\resources\\GuiSelect_Option_Inactive.png")[0]);
		m_zmOptionInactive.SetTransparencyOn();
		m_zmOptionInactive.SetTransparency(0.2f);
		m_proot->AddMaterial(&m_zmOptionInactive);

		// Up/Down Button states
		m_zmArrowButtonNormal.MakeTextureSprite(&(vektoria_gui_path + "\\resources\\GuiSelect_UpButton_Normal.png")[0]);
		m_zmArrowButtonNormal.SetTransparencyOn();
		m_zmArrowButtonHover.MakeTextureSprite(&(vektoria_gui_path + "\\resources\\GuiSelect_UpButton_Hover.png")[0]);
		m_zmArrowButtonHover.SetTransparencyOn();
		m_zmArrowButtonClick.MakeTextureSprite(&(vektoria_gui_path + "\\resources\\GuiSelect_UpButton_Click.png")[0]);
		m_zmArrowButtonClick.SetTransparencyOn();

		// Up Button
		m_zgbUpButton.Init(m_pdc, m_pwfFont, V::CFloatRect(0.85f, 0.0f, 0.15f, 0.5f));
		m_zgbUpButton.SetMaterialNormal(m_zmArrowButtonNormal);
		m_zgbUpButton.SetMaterialHover(m_zmArrowButtonHover);
		m_zgbUpButton.SetMaterialClick(m_zmArrowButtonClick);
		m_zgbUpButton.SetInnerOn();
		m_zoInteractable.AddOverlay(&m_zgbUpButton);

		// Down Button
		m_zgbDownButton.Init(m_pdc, m_pwfFont, V::CFloatRect(0.85f, 0.5f, 0.15f, 0.5f));
		m_zgbDownButton.SetMaterialNormal(m_zmArrowButtonNormal);
		m_zgbDownButton.SetMaterialHover(m_zmArrowButtonHover);
		m_zgbDownButton.SetMaterialClick(m_zmArrowButtonClick);
		m_zgbDownButton.Rotate(PI);
		m_zgbDownButton.SetInnerOn();
		m_zoInteractable.AddOverlay(&m_zgbDownButton);
	}

	bool CGuiSelect::AddOption(std::string name)
	{
		// Label already exists
		for (auto it : m_vOptions) {
			if (it->GetLabel() == name) {
				return false;
			}
		}

		m_vOptions.emplace_back(new CGuiElement());
		m_vOptions.back()->Init(m_pdc, m_pwfFont);
		m_vOptions.back()->SetLabel(name);
		m_vOptions.back()->SetInnerOn();
		m_vOptions.back()->SetMaterial(&m_zmOptionInactive);
		m_vOptions.back()->SetLabelRect(V::CFloatRect(0.05f, 0.25f, 0.9f, 0.5f));
		m_zoInteractable.AddOverlay(m_vOptions.back());

		if (!IsFirstTick()) {
			UpdateOptions();
		}

		return true;
	}

	bool CGuiSelect::HasUpdated()
	{
		return m_bHasUpdated;
	}

	bool CGuiSelect::ScrollUp()
	{
		if (m_iPosition <= 0) {
			return false;
		}
		m_iPosition--;

		UpdateOptions();

		return true;
	}

	bool CGuiSelect::ScrollDown()
	{
		if (m_iPosition >= m_vOptions.size() - m_iOptionsVisible || m_vOptions.size() <= m_iOptionsVisible) {
			return false;
		}
		m_iPosition++;

		UpdateOptions();

		return true;
	}

	int CGuiSelect::GetActivePosition()
	{
		return m_iActive;
	}

	bool CGuiSelect::SetActivePosition(int pos)
	{
		if (pos == GUI_SELECT_POSITION_NONE || pos == m_iActive) {
			if (m_iActive != GUI_SELECT_POSITION_NONE) {
				m_vOptions[m_iActive]->SetMaterial(&m_zmOptionInactive);
			}
			m_iActive = GUI_SELECT_POSITION_NONE;
			m_bHasUpdated = true;
			return true;
		}

		if (pos != m_iActive && pos >= 0 && pos < m_vOptions.size()) {
			if (m_iActive != GUI_SELECT_POSITION_NONE) {
				m_vOptions[m_iActive]->SetMaterial(&m_zmOptionInactive);
			}
			m_vOptions[pos]->SetMaterial(&m_zmOptionActive);

			m_iActive = pos;
			m_bHasUpdated = true;
			return true;
		}

		return false;
	}

	std::string CGuiSelect::GetActiveName()
	{
		if (m_iActive != GUI_SELECT_POSITION_NONE) {
			return m_vOptions[m_iActive]->GetLabel();
		}
		return std::string();
	}

	void CGuiSelect::SetLayerGui(float layer)
	{
		CGuiElement::SetLayerGui(layer);

		m_zgbUpButton.SetLayerGui(m_zoInteractable.GetLayer() - 0.01f);
		m_zgbDownButton.SetLayerGui(m_zoInteractable.GetLayer() - 0.01f);

		for (auto it : m_vOptions) {
			it->SetLayerGui(m_zoInteractable.GetLayer() - 0.01);
		}
	}

	void CGuiSelect::UpdateOptions()
	{
		m_iOptionsScrollable = min(m_iOptionsVisible, m_vOptions.size());

		for (int i = 0; i < m_vOptions.size(); i++) {
			if (i >= m_iPosition && i < m_iPosition + m_iOptionsVisible) {
				m_zfrOptionBase.SetYPos((i - m_iPosition) * m_zfrOptionBase.GetYSize());
				m_vOptions[i]->SetRect(m_zfrOptionBase);
				m_vOptions[i]->SwitchOn();
			} else {
				m_vOptions[i]->SwitchOff();
			}
		}
	}

	void CGuiSelect::Tick(float& fTimeDelta, V::CFloatRect& floatrectFather)
	{
		if (IsFirstTick()) {
			SetLayerGui();
			UpdateOptions();
		}

		CGuiElement::Tick(fTimeDelta, floatrectFather);

		// Reset changed flag
		m_bHasUpdated = false;

		// Check if options have been added
		for (int i = m_iPosition; i < m_iOptionsScrollable + m_iPosition; i++) {
			if (m_vOptions[i]->IsClicked()) {
				SetActivePosition(i);
			}
		}

		if (m_zgbUpButton.IsClicked()) {
			ScrollUp();
		}

		if (m_zgbDownButton.IsClicked()) {
			ScrollDown();
		}
	}
}

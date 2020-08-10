#include "GuiElement.h"

namespace Vektoria
{
	void CGuiElement::Init(CDeviceCursor* deviceCursor, CWritingFont* font)
	{
		this->Init(deviceCursor, font, CFloatRect(0.0f, 0.0f, 0.0f, 0.0f));
	}

	void CGuiElement::Init(CDeviceCursor* deviceCursor, CWritingFont* font, CFloatRect& floatRect)
	{
		m_acName = "CGuiElement";

		// Init members
		m_pdc = deviceCursor;
		m_pwfFont = font;
		m_zfrBase = floatRect;

		// Init container
		COverlay::Init(&m_zmBase, m_zfrBase);

		// Init interactable area
		m_zmInteractable.SetTransparency(1.0f);
		m_zoInteractable.InitFull(&m_zmInteractable);
		m_zoInteractable.SetInnerOn();
		AddOverlay(&m_zoInteractable);

		// Creating the label
		m_zwLabel.Init(CFloatRect(), m_iLabelLength, m_pwfFont);
		m_zwLabel.SetInnerOn();
		AddWriting(&m_zwLabel);

		// Overlay display order
		SetLayerGui();
	}

	bool CGuiElement::IsHovered()
	{
		return m_bIsHovered;
	}

	bool CGuiElement::IsGrabbed()
	{
		return m_bIsGrabbed;
	}

	bool CGuiElement::IsClicked()
	{
		return m_bIsClicked;
	}

	void CGuiElement::SetLabel(std::string text)
	{
		m_sLabel = text;
		m_zwLabel.PrintString(&m_sLabel[0]);
	}

	std::string CGuiElement::GetLabel()
	{
		return m_sLabel;
	}

	void CGuiElement::SetSize(int iSize)
	{
		SetSize(iSize, iSize);
	}

	void CGuiElement::SetSize(int iWidth, int iHeight)
	{
		if (iWidth <= 0 && iHeight <= 0) {
			return;
		}

		m_iWidth = iWidth;
		m_iHeight = iHeight;

		if (m_pviewport == nullptr) {
			return;
		}

		float fWidth = (float)m_iWidth / (float)m_pviewport->m_iWidth;
		float fHeight = (float)m_iHeight / (float)m_pviewport->m_iHeight;

		m_zfrBase.SetXSize(fWidth);
		m_zfrBase.SetYSize(fHeight);

		this->SetRect(m_zfrBase);
	}

	void CGuiElement::SetPositionTopLeft(int iTop, int iLeft)
	{
		m_iPositionFlag = GUI_POSITION_TOP_LEFT;
		m_iTopBottom = iTop;
		m_iLeftRight = iLeft;

		if (m_pviewport == nullptr) {
			return;
		}

		m_zfrBase.SetYPos((float)m_iTopBottom / (float)m_pviewport->m_iHeight);
		m_zfrBase.SetXPos((float)m_iLeftRight / (float)m_pviewport->m_iWidth);
		this->SetRect(m_zfrBase);
	}

	void CGuiElement::SetPositionTopRight(int iTop, int iRight)
	{
		m_iPositionFlag = GUI_POSITION_TOP_RIGHT;
		m_iTopBottom = iTop;
		m_iLeftRight = iRight;

		if (m_pviewport == nullptr) {
			return;
		}

		m_zfrBase.SetYPos((float)m_iTopBottom / (float)m_pviewport->m_iHeight);
		m_zfrBase.SetXPos(1.0f - GetRect().GetXSize() - (float)m_iLeftRight / (float)m_pviewport->m_iWidth);
		this->SetRect(m_zfrBase);
	}

	void CGuiElement::SetPositionBottomLeft(int iBottom, int iLeft)
	{
		m_iPositionFlag = GUI_POSITION_BOTTOM_LEFT;
		m_iTopBottom = iBottom;
		m_iLeftRight = iLeft;

		if (m_pviewport == nullptr) {
			return;
		}

		m_zfrBase.SetYPos(1.0f - GetRect().GetYSize() - (float)m_iTopBottom / (float)m_pviewport->m_iHeight);
		m_zfrBase.SetXPos((float)m_iLeftRight / (float)m_pviewport->m_iWidth);
		this->SetRect(m_zfrBase);
	}

	void CGuiElement::SetPositionBottomRight(int iBottom, int iRight)
	{
		m_iPositionFlag = GUI_POSITION_BOTTOM_RIGHT;
		m_iTopBottom = iBottom;
		m_iLeftRight = iRight;

		if (m_pviewport == nullptr) {
			return;
		}

		m_zfrBase.SetYPos(1.0f - GetRect().GetYSize() - (float)m_iTopBottom / (float)m_pviewport->m_iHeight);
		m_zfrBase.SetXPos(1.0f - GetRect().GetXSize() - (float)m_iLeftRight / (float)m_pviewport->m_iWidth);
		this->SetRect(m_zfrBase);
	}

	void CGuiElement::SetLabelRect(CFloatRect& floatrect)
	{
		m_zwLabel.SetRect(floatrect);
	}

	void CGuiElement::SetLayerGui(float layer)
	{
		SetLayer(layer);
		m_zwLabel.SetLayer(layer - 0.02f);
		m_zoInteractable.SetLayer(layer - 0.03f);
	}

	void CGuiElement::ReSize()
	{
		SetSize(m_iWidth, m_iHeight);

		if (m_iPositionFlag == GUI_POSITION_TOP_LEFT) {
			SetPositionTopLeft(m_iTopBottom, m_iLeftRight);
		}
		else if (m_iPositionFlag == GUI_POSITION_TOP_RIGHT) {
			SetPositionTopRight(m_iTopBottom, m_iLeftRight);
		}
		else if (m_iPositionFlag == GUI_POSITION_BOTTOM_LEFT) {
			SetPositionBottomLeft(m_iTopBottom, m_iLeftRight);
		}
		else if (m_iPositionFlag == GUI_POSITION_BOTTOM_RIGHT) {
			SetPositionBottomRight(m_iTopBottom, m_iLeftRight);
		}
	}

	bool CGuiElement::IsFirstTick()
	{
		return m_bFirstTick;
	}

	void CGuiElement::Tick(float& fTimeDelta, CFloatRect& floatrectFather)
	{
		COverlay::Tick(fTimeDelta, floatrectFather);

		if (IsFirstTick()) {
			ReSize();
			m_bFirstTick = false;
		}

		m_bIsHovered = false;
		m_bIsClicked = false;

		// Detect if cursor is on top of element
		if (&m_zoInteractable == m_pdc->PickOverlay()) {
			m_bIsHovered = true;

			// Detect if element is grabbed
			if (m_pdc->ButtonDownLeft()) {
				m_bIsGrabbed = true;
			}

			// Detect if button left is released on top of the element
			if (m_bIsGrabbed && !m_pdc->ButtonPressedLeft()) {
				m_bIsClicked = true;
			}
		}

		// Element stays grabbed until button left is released
		if (!m_pdc->ButtonPressedLeft()) {
			m_bIsGrabbed = false;
		}
	}
}
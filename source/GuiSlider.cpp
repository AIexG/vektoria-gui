#include "GuiSlider.h"

namespace VektoriaGui
{
	void CGuiSlider::Init(V::CDeviceCursor* deviceCursor, V::CWritingFont* font)
	{
		this->Init(deviceCursor, font, m_zfrBase);
	}

	void CGuiSlider::Init(V::CDeviceCursor* deviceCursor, V::CWritingFont* font, V::CFloatRect& floatRect)
	{
		this->Init(deviceCursor, font, m_fMin, m_fMax, m_fDefault, m_fStep, m_zfrBase);
	}

	void CGuiSlider::Init(V::CDeviceCursor* deviceCursor, V::CWritingFont* font, float fMin, float fMax, float fDefault, float fStep)
	{
		this->Init(deviceCursor, font, fMin, fMax, fDefault, fStep, m_zfrBase);
	}

	void CGuiSlider::Init(V::CDeviceCursor* deviceCursor, V::CWritingFont* font, float fMin, float fMax, float fDefault, float fStep, V::CFloatRect& floatRect)
	{
		CGuiElement::Init(deviceCursor, font, floatRect);
		m_acName = "CGuiSlider";

		// Styling base overlay
		m_zmBase.MakeTextureSprite(&(vektoria_gui_path + "\\resources\\GuiElement_Background.jpg")[0]);
		m_zmBase.SetTransparency(0.0f);

		// Styling Interactable
		m_zoInteractable.SetTransparency(1.0f);
		m_zoInteractable.SetRect(V::CFloatRect(0.05f, 0.4f, 0.9f, 0.5f));

		// Label writing
		m_zwLabel.m_ixChars = 12;
		m_zwLabel.SetRect(V::CFloatRect(0.05f, 0.15f, 0.6f, 0.2f));

		// Value writing
		m_zwValue.Init(V::CFloatRect(0.65f, 0.15f, 0.3f, 0.2f), 4, m_pwfFont);
		m_zwValue.SetInnerOn();
		m_zwValue.SetLayer(m_zwLabel.GetLayer());
		AddWriting(&m_zwValue);

		// Styling Handle
		m_zmHandleBackground.MakeTextureSprite(&(vektoria_gui_path + "\\resources\\GuiSlider_Handle.png")[0]);
		m_zmHandleBackground.SetTransparencyOn();

		// Initialize Handle
		m_zfrHandle.SetXSize(m_fHandleWidth);
		m_zoHandle.Init(&m_zmHandleBackground, m_zfrHandle);
		m_zoHandle.SetInnerOn();
		m_zoInteractable.AddOverlay(&m_zoHandle);

		// Init & Styling Track
		m_zmTrackVisual.MakeTextureSprite(&(vektoria_gui_path + "\\resources\\GuiSlider_Track.png")[0]);
		m_zmTrackVisual.SetTransparencyOn();
		m_zoTrackVisual.Init(&m_zmTrackVisual, V::CFloatRect(0.0f, 0.45f, 1.0f, 0.1f));
		m_zoTrackVisual.SetInnerOn();
		m_zoInteractable.AddOverlay(&m_zoTrackVisual);

		// Init parameters
		m_fValue = fDefault;
		InitParameters(fMin, fMax, fDefault, fStep);
	}

	float CGuiSlider::GetValue()
	{
		return m_fValue;
	}
	
	void CGuiSlider::SetValue(float value)
	{
		if (value <= m_fMin) {
			m_fValue = m_fMin;
		} else if (value >= m_fMax) {
			m_fValue = m_fMax;
		} else {
			// Round value to closest step
			m_fValue = round(value * m_fStepInverse) * m_fStep;

			if (m_fValue == -0.0f) {
				m_fValue = 0.0f;
			}
		}

		// Update handle
		m_zfrHandle.SetXPos((m_fValue - m_fMin) * m_fValueToPositionFactor);
		m_zoHandle.SetRect(m_zfrHandle);

		// Update value writing
		m_zwValue.PrintFloat(m_fValue);

		m_bIsUpdating = true;
	}

	float CGuiSlider::GetMin()
	{
		return m_fMin;
	}

	bool CGuiSlider::SetMin(float fMin)
	{
		return InitParameters(fMin, m_fMax, m_fDefault, m_fStep);
	}

	float CGuiSlider::GetMax()
	{
		return m_fMax;
	}

	bool CGuiSlider::SetMax(float fMax)
	{
		return InitParameters(m_fMin, fMax, m_fDefault, m_fStep);
	}

	float CGuiSlider::GetDefault()
	{
		return m_fDefault;
	}

	bool CGuiSlider::SetDefault(float fDefault)
	{
		return InitParameters(m_fMin, m_fMax, fDefault, m_fStep);
	}

	float CGuiSlider::GetStep()
	{
		return m_fStep;
	}

	bool CGuiSlider::SetStep(float fStep)
	{
		return InitParameters(m_fMin, m_fMax, m_fDefault, fStep);
	}

	bool CGuiSlider::InitParameters(float fMin, float fMax, float fDefault, float fStep)
	{
		if (fMin >= fMax || fDefault > fMax || fMin > fDefault || (fMax - fMin) * 0.5f < fStep) {
			return false;
		}

		m_fMin = fMin;
		m_fMax = fMax;
		m_fDefault = fDefault;
		m_fStep = fStep;
		m_fRange = m_fMax - m_fMin;
		m_fStepInverse = 1.0f / m_fStep;
		m_fValueToPositionFactor = (m_fStep / m_fRange) * (1.0f - m_fHandleWidth) * m_fStepInverse;

		if (!IsFirstTick()) {
			ReSize();
		}

		SetValue(m_fValue);
		m_bIsUpdating = false; // Overwrite flag for this tick

		return true;
	}

	bool CGuiSlider::HasUpdated()
	{
		return m_bHasUpdated;
	}

	void CGuiSlider::SetLayerGui(float layer)
	{
		CGuiElement::SetLayerGui(layer);

		m_zoHandle.SetLayer(m_zoInteractable.GetLayer());
		m_zoTrackVisual.SetLayer(m_zoInteractable.GetLayer());
	}

	void CGuiSlider::ReSize()
	{
		CGuiElement::ReSize();

		V::CFloatRect frAbsoluteInteractable = fetchRectAbsolutePosition(&m_zoInteractable);

		float fHandleHeight = m_fHandleWidth * frAbsoluteInteractable.GetXSize() / frAbsoluteInteractable.GetYSize();
		if (m_pviewport != nullptr) {
			fHandleHeight = (m_fHandleWidth * frAbsoluteInteractable.GetXSize() * (float)m_pviewport->m_iWidth) / (frAbsoluteInteractable.GetYSize() * (float)m_pviewport->m_iHeight);
		}

		// Update rect size and position
		m_fPosAbsX = frAbsoluteInteractable.GetXPos();
		m_fCursorToValueFactor = m_fRange / (frAbsoluteInteractable.GetXSize() * (1.0f - 0.5f * m_fHandleWidth));

		// Update Handle
		m_zfrHandle.SetYPos(0.5f - fHandleHeight * 0.5f);
		m_zfrHandle.SetYSize(fHandleHeight);
		m_zoHandle.SetRect(m_zfrHandle);
	}

	void CGuiSlider::Tick(float& fTimeDelta, V::CFloatRect& floatrectFather)
	{
		if (IsFirstTick()) {
			m_bIsUpdating = false; // Don't trigger HasUpdated() on the first tick
			m_zoHandle.SetRect(m_zfrHandle);
		}

		CGuiElement::Tick(fTimeDelta, floatrectFather);

		m_bHasUpdated = false;

		if (m_bIsGrabbed) {
			SetValue((m_pdc->m_frxFrame - m_fPosAbsX) * m_fCursorToValueFactor + m_fMin);
		} else if (m_bIsUpdating) {
			m_bHasUpdated = true;
			m_bIsUpdating = false;
		}
	}
}

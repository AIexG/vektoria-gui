#include "GuiImageColorPicker.h"

namespace VektoriaGui
{
	void CGuiImageColorPicker::Init(V::CDeviceCursor* deviceCursor, V::CWritingFont* font)
	{
		this->Init(deviceCursor, font, m_zfrBase);
	}

	void CGuiImageColorPicker::Init(V::CDeviceCursor* deviceCursor, V::CWritingFont* font, V::CImage& image)
	{
		this->Init(deviceCursor, font, m_zfrBase, image);
	}

	void CGuiImageColorPicker::Init(V::CDeviceCursor* deviceCursor, V::CWritingFont* font, char* path)
	{
		this->Init(deviceCursor, font, m_zfrBase, &(vektoria_gui_path + "\\resources\\GuiImageColorPicker_Full.jpg")[0]);
	}

	void CGuiImageColorPicker::Init(V::CDeviceCursor* deviceCursor, V::CWritingFont* font, V::CFloatRect& floatRect)
	{
		V::CImage image;
		image.Init(&(vektoria_gui_path + "\\resources\\GuiImageColorPicker_Full.jpg")[0]);
		this->Init(deviceCursor, font, floatRect, image);
	}

	void CGuiImageColorPicker::Init(V::CDeviceCursor* deviceCursor, V::CWritingFont* font, V::CFloatRect& floatRect, V::CImage& image)
	{
		Initialisation(deviceCursor, font, floatRect);
		SetImage(image);
	}

	void CGuiImageColorPicker::Init(V::CDeviceCursor* deviceCursor, V::CWritingFont* font, V::CFloatRect& floatRect, char* path)
	{
		Initialisation(deviceCursor, font, floatRect);
		SetImage(path);
	}

	void CGuiImageColorPicker::SetImage(char* path)
	{
		m_ziImage.Init(path);
		SetImage(m_ziImage);
	}

	void CGuiImageColorPicker::SetImage(V::CImage& image)
	{
		m_ziImage.Copy(image);
		m_ztImage.Fini();
		m_ztImage.SetImage(&m_ziImage);
		m_zmInteractable.SetTextureSprite(&m_ztImage);
	}

	V::CColor CGuiImageColorPicker::GetColor()
	{
		return m_zcColor;
	}

	bool CGuiImageColorPicker::HasUpdated()
	{
		return m_bHasUpdated;
	}

	void CGuiImageColorPicker::SetLayerGui(float layer)
	{
		CGuiElement::SetLayerGui(layer);
		m_zoPreview.SetLayer(m_zoInteractable.GetLayer() - 0.01f);
	}

	void CGuiImageColorPicker::ReSize()
	{
		CGuiElement::ReSize();

		// Get absolute position
		V::CFloatRect frAbsolute = fetchRectAbsolutePosition(&m_zoInteractable);
		m_fPosAbsX = frAbsolute.GetXPos();
		m_fPosAbsY = frAbsolute.GetYPos();
		m_fInverseSizeAbsX = 1.0f / frAbsolute.GetXSize();
		m_fInverseSizeAbsY = 1.0f / frAbsolute.GetYSize();

		// Set sizes in px, hardcoded values for lazyness
		if (m_pviewport != nullptr) {
			m_fPreviewPosX = (12.0f / (float)m_pviewport->m_iWidth) - m_fPosAbsX; // Windows 10 cursor width + padding in px
			m_fPreviewPosY = (21.0f / (float)m_pviewport->m_iHeight) - m_fPosAbsY; // Windows 10 cursor height + padding in px
			m_frPreview = V::CFloatRect(
				m_fPreviewPosX, m_fPreviewPosY,
				20.0f / (float)m_pviewport->m_iWidth, // Preview circle width in px
				20.0f / (float)m_pviewport->m_iHeight // Preview circle height in px
			);
			m_zoPreview.SetRect(m_frPreview);
		}
	}
	
	void CGuiImageColorPicker::Initialisation(V::CDeviceCursor* deviceCursor, V::CWritingFont* font, V::CFloatRect& floatRect)
	{
		CGuiElement::Init(deviceCursor, font, floatRect);

		m_acName = "CGuiImageColorPicker";

		// Styling base overlay
		m_zmBase.MakeTextureSprite(&(vektoria_gui_path + "\\resources\\GuiElement_Background.jpg")[0]);

		// Styling Interactable
		m_zoInteractable.SetRect(V::CFloatRect(0.05f, 0.25f, 0.9f, 0.7f));
		m_zoInteractable.SetTransparency(0.0f);

		// Label
		m_zwLabel.SetRect(V::CFloatRect(0.05f, 0.1f, 0.9f, 0.1f));

		// Preview Overlay
		m_zmPreview.MakeTextureSprite(&(vektoria_gui_path + "\\resources\\GuiImageColorPicker_Preview.jpg")[0]);
		m_zmPreview.SetTransparencyOn();
		m_frPreview = V::CFloatRect(0.0f, 0.0f, 0.02f, 0.02f);
		m_zoPreview.Init(&m_zmPreview, m_frPreview);
		m_zoInteractable.AddOverlay(&m_zoPreview);
		m_zoPreview.SwitchOff();
	}

	void CGuiImageColorPicker::Tick(float& fTimeDelta, V::CFloatRect& floatrectFather)
	{
		CGuiElement::Tick(fTimeDelta, floatrectFather);

		// Reset changed flag
		m_bHasUpdated = false;

		if (m_bIsHovered) {
			m_zoPreview.SwitchOn();

			// Update the previews color
			m_zcPreview = m_ziImage.GetPixel(
				(unsigned int)(m_ziImage.GetResolutionX() * ((m_pdc->m_frxFrame - m_fPosAbsX) * m_fInverseSizeAbsX) + 0.333f),
				(unsigned int)(m_ziImage.GetResolutionY() * (m_pdc->m_fryFrame - m_fPosAbsY) * m_fInverseSizeAbsY)
			);
			m_zmPreview.Translate(m_zcPreview);

			// Update the previews position
			m_frPreview.SetXPos(m_pdc->m_frxFrame + m_fPreviewPosX);
			m_frPreview.SetYPos(m_pdc->m_fryFrame + m_fPreviewPosY);
			m_zoPreview.SetRect(m_frPreview);
			m_bHasUpdated = true;
		} else {
			m_zoPreview.SwitchOff();
		}

		// Set color for retrieval on click
		if (m_bIsClicked) {
			m_zcColor = m_zcPreview;
		}
	}
}
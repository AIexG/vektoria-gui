#pragma once
#include "GuiElement.h"
#include "GuiUtils.h"

//--------------------------------------------------------------------------------------------
// CGuiImageColorPicker
//
// Description: Color picker overlay element for Vektoria, allows retrieval
//              of a color value from an image with the cursor.
// Autor      : Alex Grüßhaber
// Copyright  : GNU GPL
//--------------------------------------------------------------------------------------------

namespace Vektoria
{
	class CGuiImageColorPicker : public CGuiElement
	{
	public:
		CGuiImageColorPicker() = default;
		~CGuiImageColorPicker() = default;

		///<summary>Initialisation method for a slider element.</summary>
		///<param name="deviceCursor">Cursor that interacts with the GuiElement</param>
		///<param name="font">Font to be used for labels and values</param>
		void Init(CDeviceCursor* deviceCursor, CWritingFont* font);

		///<summary>Initialisation method for a slider element.</summary>
		///<param name="deviceCursor">Cursor that interacts with the GuiElement</param>
		///<param name="font">Font to be used for labels and values</param>
		///<param name="floatRect">Size and position for the GuiElement</param>
		void Init(CDeviceCursor* deviceCursor, CWritingFont* font, CFloatRect& floatRect);

		///<summary>Initialisation method for a slider element.</summary>
		///<param name="deviceCursor">Cursor that interacts with the GuiElement</param>
		///<param name="font">Font to be used for labels and values</param>
		///<param name="floatRect">Size and position for the GuiElement</param>
		///<param name="image">Image to pick a color from</param>
		void Init(CDeviceCursor* deviceCursor, CWritingFont* font, CFloatRect& floatRect, CImage& image);

		void SetImage(char* path);
		///<summary>Set a new image for the picker.</summary>
		///<param name="image">Image to be set</param>
		void SetImage(CImage& image);

		///<summary>Returns last picked color.</summary>
		CColor GetColor();

		///<summary>Returns true if the color value has updated in the last tick.</summary>
		bool HasUpdated();

		///<summary>Sets the distance from viewport.</summary>
		///<param name="layer">Distance from viewport, less means closer, range: ]0;1[.</param>
		virtual void SetLayerGui(float layer = GUI_DEFAULT_LAYER) override;

		///<summary>Recalculates and updates the size and position of the rect, call when window resizes.</summary>
		virtual void ReSize() override;

	protected:
		bool m_bHasUpdated = false;

		CColor m_zcColor;
		CImage m_ziImage;
		CTexture m_ztImage;

		CTexture m_ztPreview;
		CImage m_ziPreview;
		CMaterial m_zmPreview;
		CFloatRect m_frPreview;
		CColor m_zcPreview;
		COverlay m_zoPreview;

		// Interactable absolute position and inverse size
		float m_fPosAbsX, m_fPosAbsY;
		float m_fInverseSizeAbsX, m_fInverseSizeAbsY;

		float m_fPreviewPosX, m_fPreviewPosY;

		///<summary>Method to be called every tick in the application.</summary>
		///<param name="fTimeDelta">Time since last tick</param>
		//void Tick(float& fTimeDelta) override;
		void Tick(float& fTimeDelta, CFloatRect& floatrectFather) override;
	};
}


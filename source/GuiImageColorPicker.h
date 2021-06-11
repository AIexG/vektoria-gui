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

namespace VektoriaGui
{
	class CGuiImageColorPicker : public CGuiElement
	{
	public:
		CGuiImageColorPicker() = default;
		~CGuiImageColorPicker() = default;

		///<summary>Initialisation method for a slider element.</summary>
		///<param name="deviceCursor">Cursor that interacts with the GuiElement</param>
		///<param name="font">Font to be used for labels and values</param>
		void Init(V::CDeviceCursor* deviceCursor, V::CWritingFont* font);

		///<summary>Initialisation method for a slider element.</summary>
		///<param name="deviceCursor">Cursor that interacts with the GuiElement</param>
		///<param name="font">Font to be used for labels and values</param>
		///<param name="image">Image to pick a color from</param>
		void Init(V::CDeviceCursor* deviceCursor, V::CWritingFont* font, V::CImage& image);

		///<summary>Initialisation method for a slider element.</summary>
		///<param name="deviceCursor">Cursor that interacts with the GuiElement</param>
		///<param name="font">Font to be used for labels and values</param>
		///<param name="path">Image path to pick a color from</param>
		void Init(V::CDeviceCursor* deviceCursor, V::CWritingFont* font, char* path);

		///<summary>Initialisation method for a slider element.</summary>
		///<param name="deviceCursor">Cursor that interacts with the GuiElement</param>
		///<param name="font">Font to be used for labels and values</param>
		///<param name="floatRect">Size and position for the GuiElement</param>
		void Init(V::CDeviceCursor* deviceCursor, V::CWritingFont* font, V::CFloatRect& floatRect);

		///<summary>Initialisation method for a slider element.</summary>
		///<param name="deviceCursor">Cursor that interacts with the GuiElement</param>
		///<param name="font">Font to be used for labels and values</param>
		///<param name="floatRect">Size and position for the GuiElement</param>
		///<param name="image">Image to pick a color from</param>
		void Init(V::CDeviceCursor* deviceCursor, V::CWritingFont* font, V::CFloatRect& floatRect, V::CImage& image);

		///<summary>Initialisation method for a slider element.</summary>
		///<param name="deviceCursor">Cursor that interacts with the GuiElement</param>
		///<param name="font">Font to be used for labels and values</param>
		///<param name="floatRect">Size and position for the GuiElement</param>
		///<param name="path">Image path to pick a color from</param>
		void Init(V::CDeviceCursor* deviceCursor, V::CWritingFont* font, V::CFloatRect& floatRect, char* path);

		///<summary>Set a new image for the picker by path.</summary>
		///<param name="path">Path to the image.</param>
		void SetImage(char* path);

		///<summary>Set a new image for the picker.</summary>
		///<param name="image">Image to be set.</param>
		void SetImage(V::CImage& image);

		///<summary>Returns last picked color.</summary>
		V::CColor GetColor();

		///<summary>Returns true if the color value has updated in the last tick.</summary>
		bool HasUpdated();

		///<summary>Sets the distance from viewport.</summary>
		///<param name="layer">Distance from viewport, less means closer, range: ]0;1[.</param>
		virtual void SetLayerGui(float layer = GUI_DEFAULT_LAYER) override;

		///<summary>Recalculates and updates the size and position of the rect, call when window resizes.</summary>
		virtual void ReSize() override;

	protected:
		bool m_bHasUpdated = false;

		V::CColor m_zcColor;
		V::CImage m_ziImage;
		V::CTexture m_ztImage;

		V::CTexture m_ztPreview;
		V::CImage m_ziPreview;
		V::CMaterial m_zmPreview;
		V::CFloatRect m_frPreview;
		V::CColor m_zcPreview;
		COverlay m_zoPreview;

		// Interactable absolute position and inverse size
		float m_fPosAbsX, m_fPosAbsY;
		float m_fInverseSizeAbsX, m_fInverseSizeAbsY;

		float m_fPreviewPosX, m_fPreviewPosY;

		///<summary>Method to be called in Init().</summary>
		///<param name="deviceCursor">Cursor that interacts with the GuiElement</param>
		///<param name="font">Font to be used for labels and values</param>
		///<param name="floatRect">Size and position for the GuiElement</param>
		void Initialisation(V::CDeviceCursor* deviceCursor, V::CWritingFont* font, V::CFloatRect& floatRect);

		///<summary>Method to be called every tick in the application.</summary>
		///<param name="fTimeDelta">Time since last tick</param>
		virtual void Tick(float& fTimeDelta, V::CFloatRect& floatrectFather);
	};
}


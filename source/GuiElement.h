#pragma once
#include "Vektoria\Root.h"
#include <string>

//--------------------------------------------------------------------------------------------
// CGuiElement
//
// Description: Base overlay element class for Vektoria, registers clicking,
//              grabbing and hovering the element with the cursor, no visuals.
// Autor      : Alex Grüßhaber
// Copyright  : GNU GPL
//--------------------------------------------------------------------------------------------

#define GUI_POSITION_NONE			0
#define GUI_POSITION_TOP_LEFT		1
#define GUI_POSITION_TOP_RIGHT		2
#define GUI_POSITION_BOTTOM_LEFT	3
#define GUI_POSITION_BOTTOM_RIGHT	4
#define GUI_DEFAULT_LAYER			0.199F

/**
 * TODO:
 * - Fix grabbing nothing, dragging onto element and releasing triggers click
 */

namespace Vektoria
{
	class CGuiElement : public COverlay
	{
	public:
		CGuiElement() = default;
		~CGuiElement() = default;

		///<summary>Initialisation method for a basic gui element.</summary>
		///<param name="deviceCursor"> Cursor that interacts with the GuiElement </param>
		///<param name="font"> Font to be used for labels and values </param>
		void Init(CDeviceCursor* deviceCursor, CWritingFont* font);

		///<summary>Initialisation method for a basic gui element.</summary>
		///<param name="deviceCursor"> Cursor that interacts with the GuiElement </param>
		///<param name="font"> Font to be used for labels and values </param>
		///<param name="floatRect"> Size and position for the GuiElement </param>
		void Init(CDeviceCursor* deviceCursor, CWritingFont* font, CFloatRect& floatRect);

		///<summary>Returns true if cursor is above the element.</summary>
		bool IsHovered();

		///<summary>Returns true if user grabs the element.</summary>
		bool IsGrabbed();

		///<summary>Returns true if user clicks the element.</summary>
		bool IsClicked();

		///<summary>Returns the text of the gui elements label.</summary>
		std::string GetLabel();

		///<summary>Sets the text of the gui elements label.</summary>
		///<param name="text"> The text to be set. </param>
		void SetLabel(std::string text);

		///<summary>Sets the size of the gui element in pixel.</summary>
		///<param name="iSize"> The size for width and height. </param>
		void SetSize(int iSize);

		///<summary>Sets the size of the gui element in pixel.</summary>
		///<param name="iWidth"> The width in pixel to be set. </param>
		///<param name="iHeight"> The height in pixel to be set. </param>
		virtual void SetSize(int iWidth, int iHeight);
		
		///<summary>Sets the position of the gui element in pixel, aligns it to the top left of the viewport.</summary>
		///<param name="iTop"> The distance from the top edge in pixel. </param>
		///<param name="iLeft"> The distance from the left edge in pixel. </param>
		void SetPositionTopLeft(int iTop, int iLeft);

		///<summary>Sets the position of the gui element in pixel, aligns it to the top right of the viewport.</summary>
		///<param name="iTop"> The distance from the top edge in pixel. </param>
		///<param name="iRight"> The distance from the right edge in pixel. </param>
		void SetPositionTopRight(int iTop, int iRight);

		///<summary>Sets the position of the gui element in pixel, aligns it to the bottom left of the viewport.</summary>
		///<param name="iBottom"> The distance from the bottom edge in pixel. </param>
		///<param name="iLeft"> The distance from the left edge in pixel. </param>
		void SetPositionBottomLeft(int iBottom, int iLeft);

		///<summary>Sets the position of the gui element in pixel, aligns it to the bottom right of the viewport.</summary>
		///<param name="iBottom"> The distance from the bottom edge in pixel. </param>
		///<param name="iRight"> The distance from the right edge in pixel. </param>
		void SetPositionBottomRight(int iBottom, int iRight);

		///<summary>Sets the Labels dimension and position.</summary>
		///<param name="floatrect"> Dimension and position. </param>
		void SetLabelRect(CFloatRect& floatrect);

		///<summary>Sets the distance from viewport.</summary>
		///<param name="layer"> Distance from viewport, less means closer, range: ]0;1[. </param>
		virtual void SetLayerGui(float layer = GUI_DEFAULT_LAYER);

		///<summary>Recalculates and updates the size and position of the rect, call when window resizes.</summary>
		virtual void ReSize();

	protected:
		// Element states
		bool m_bIsHovered = false;
		bool m_bIsGrabbed = false;
		bool m_bIsClicked = false;

		// Positioning
		int m_iPositionFlag = GUI_POSITION_NONE;
		int m_iWidth = 0, m_iHeight = 0, m_iTopBottom = 0, m_iLeftRight = 0;

		// Cursor
		CDeviceCursor* m_pdc;

		// Base Rect
		CFloatRect m_zfrBase;

		// Label
		CWriting m_zwLabel;
		CWritingFont* m_pwfFont;
		std::string m_sLabel;
		int m_iLabelLength = 16;

		// Styling
		CMaterial m_zmBase;
		CMaterial m_zmInteractable;

		// Interactable area
		COverlay m_zoInteractable;

		///<summary>Returns true if it is the first tick, call before CGuiElement::Tick() in derived classes.</summary>
		bool IsFirstTick();

		///<summary>Method to be called every tick in the application.</summary>
		///<param name="fTimeDelta"> Time since last tick </param>
		void Tick(float& fTimeDelta, CFloatRect& floatrectFather) override;

	private:
		bool m_bFirstTick = true;
	};
}


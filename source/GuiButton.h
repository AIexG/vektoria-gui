#pragma once
#include "GuiElement.h"

//--------------------------------------------------------------------------------------------
// CGuiButton
//
// Description: Button overlay element for Vektoria, registers clicking, grabbing and
//              hovering the element with the cursor adds nicer visuals.
// Autor      : Alex Grüßhaber
// Copyright  : GNU GPL
//--------------------------------------------------------------------------------------------

namespace VektoriaGui
{
	class CGuiButton : public CGuiElement
	{
	public:
		CGuiButton() = default;
		~CGuiButton() = default;

		///<summary>Initialisation method for a basic gui element.</summary>
		///<param name="deviceCursor">Cursor that interacts with the GuiElement</param>
		///<param name="font">Font to be used for labels and values</param>
		void Init(V::CDeviceCursor* deviceCursor, V::CWritingFont* font);

		///<summary>Initialisation method for a basic gui element.</summary>
		///<param name="deviceCursor">Cursor that interacts with the GuiElement</param>
		///<param name="font">Font to be used for labels and values</param>
		///<param name="floatRect">Size and position for the GuiElement</param>
		void Init(V::CDeviceCursor* deviceCursor, V::CWritingFont* font, V::CFloatRect& floatRect);

		///<summary>Sets the text of the gui elements label.</summary>
		///<param name="text">The text to be set.</param>
		void SetLabel(std::string text);

		void SetMaterialNormal(V::CMaterial& material);
		void SetMaterialHover(V::CMaterial& material);
		void SetMaterialClick(V::CMaterial& material);

	protected:
		V::CMaterial m_zmHover;
		V::CMaterial m_zmClick;

		///<summary>Method to be called every tick in the application.</summary>
		///<param name="fTimeDelta">Time since last tick</param>
		virtual void Tick(float& fTimeDelta, V::CFloatRect& floatrectFather);
	};
}


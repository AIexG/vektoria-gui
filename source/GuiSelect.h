#pragma once
#include "GuiElement.h"
#include "GuiButton.h"
#include <string>
#include <vector>

//--------------------------------------------------------------------------------------------
// CGuiSelect
//
// Description: Select overlay element for Vektoria, allows selecting an item
//				from a list.
// Autor      : Alex Grüßhaber
// Copyright  : GNU GPL
//--------------------------------------------------------------------------------------------

#define GUI_SELECT_POSITION_NONE	-1

namespace Vektoria
{
	class CGuiSelect : public CGuiElement
	{
	public:
		CGuiSelect() = default;
		~CGuiSelect();

		///<summary>Initialisation method for a basic gui element.</summary>
		///<param name="deviceCursor">Cursor that interacts with the GuiElement</param>
		///<param name="font">Font to be used for labels and values</param>
		void Init(CDeviceCursor * deviceCursor, CWritingFont * font);

		///<summary>Initialisation method for a basic gui element.</summary>
		///<param name="deviceCursor">Cursor that interacts with the GuiElement</param>
		///<param name="font">Font to be used for labels and values</param>
		///<param name="optionsVisible">Amount of visible options in the list.</param>
		void Init(CDeviceCursor * deviceCursor, CWritingFont * font, int optionsVisible);

		///<summary>Initialisation method for a basic gui element.</summary>
		///<param name="deviceCursor">Cursor that interacts with the GuiElement</param>
		///<param name="font">Font to be used for labels and values</param>
		///<param name="optionsVisible">Amount of visible options in the list.</param>
		///<param name="floatRect">Size and position for the GuiElement</param>
		void Init(CDeviceCursor * deviceCursor, CWritingFont * font, int optionsVisible, CFloatRect & floatRect);

		///<summary>Add a new option to the select field, returns false if key already exists.</summary>
		///<param name="name">Display name and key of the option.</param>
		bool AddOption(std::string name);

		///<summary>Returns true if the value has updated in the last tick.</summary>
		bool HasUpdated();

		///<summary>Scrolls the list up, returns true if successful.</summary>
		bool ScrollUp();
		
		///<summary>Scrolls the list down, returns true if successful.</summary>
		bool ScrollDown();

		///<summary>Returns the active position. Returns "-1" if no option is active.</summary>
		int GetActivePosition();

		///<summary>Sets the active position. Returns true if successful.</summary>
		///<param name="pos">The elements position to be set to active. Set "-1" to deactivate all.</param>
		bool SetActivePosition(int pos);

		///<summary>Returns the name/key of the currently active option, returns an empty string if non is active.</summary>
		std::string GetActiveName();

		///<summary>Sets the distance from viewport.</summary>
		///<param name="layer">Distance from viewport, less means closer, range: ]0;1[.</param>
		virtual void SetLayerGui(float layer = GUI_DEFAULT_LAYER) override;

	protected:
		bool m_bHasUpdated = false;

		int m_iActive = -1, m_iPosition = 0;
		int m_iOptionsVisible;
		int m_iOptionsScrollable;

		CMaterial m_zmOptionActive;
		CMaterial m_zmOptionInactive;
		std::vector<CGuiElement*> m_vOptions;
		CFloatRect m_zfrOptionBase;

		CMaterial m_zmArrowButtonNormal;
		CMaterial m_zmArrowButtonHover;
		CMaterial m_zmArrowButtonClick;
		CGuiButton m_zgbUpButton;
		CGuiButton m_zgbDownButton;

		///<summary>Update all option rect positions and their visibility.</summary>
		void UpdateOptions();

		///<summary>Method to be called every tick in the application.</summary>
		///<param name="fTimeDelta">Time since last tick</param>
		//void Tick(float& fTimeDelta);
		void Tick(float& fTimeDelta, CFloatRect& floatrectFather) override;
	};
}


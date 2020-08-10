#pragma once
#include "GuiElement.h"
#include "GuiUtils.h"
#include "Math.h"

//--------------------------------------------------------------------------------------------
// CGuiSlider
//
// Description: Slider overlay element for Vektoria, allows setting a value
//				between a minimum and maximum value.
// Autor      : Alex Grüßhaber
// Copyright  : GNU GPL
//--------------------------------------------------------------------------------------------

namespace Vektoria
{
    class CGuiSlider : public CGuiElement
    {
    public:
        CGuiSlider() = default;
        ~CGuiSlider() = default;

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
        ///<param name="fMin">Minimal value the slider displays (Default: 0.0)</param>
        ///<param name="fMax">Maximal value the slider displays (Default: 100.0)</param>
        ///<param name="fDefault">Value to display slider on first load (Default: 50.0)</param>
        ///<param name="fStep">Steps the slider can take by moving (Default: 1.0)</param>
        ///<param name="floatRect">Size and position for the GuiElement</param>
        void Init(CDeviceCursor* deviceCursor, CWritingFont* font, float fMin, float fMax, float fDefault, float fStep);

        ///<summary>Initialisation method for a slider element.</summary>
        ///<param name="deviceCursor">Cursor that interacts with the GuiElement</param>
        ///<param name="font">Font to be used for labels and values</param>
        ///<param name="fMin">Minimal value the slider displays (Default: 0.0)</param>
        ///<param name="fMax">Maximal value the slider displays (Default: 100.0)</param>
        ///<param name="fDefault">Value to display slider on first load (Default: 50.0)</param>
        ///<param name="fStep">Steps the slider can take by moving (Default: 1.0)</param>
        void Init(CDeviceCursor* deviceCursor, CWritingFont* font, float fMin, float fMax, float fDefault, float fStep, CFloatRect& floatRect);

        ///<summary>Returns the value of the current slider position.</summary>
        float GetValue();

        ///<summary>Sets slider position to specified value, adjusts the value if out of range or between steps.</summary>
        ///<param name="value">Value to set slider to</param>
        void SetValue(float value);

        ///<summary>Sets minimal value, returns false if it cannot be set.</summary>
        ///<param name="fMin">New minimal value.</param>
        float GetMin();
        bool SetMin(float fMin);

        ///<summary>Sets maximum value, returns false if it cannot be set.</summary>
        ///<param name="fMax">New maximum value.</param>
        float GetMax();
        bool SetMax(float fMax);

        ///<summary>Sets default value, returns false if it cannot be set.</summary>
        ///<param name="fDefault">New default value.</param>
        float GetDefault();
        bool SetDefault(float fDefault);

        ///<summary>Sets step size, returns false if it cannot be set.</summary>
        ///<param name="fStep">New step size.</param>
        float GetStep();
        bool SetStep(float fStep);

        ///<summary>(Re-)Initializes slider parameters, returns false if any value cannot be set, sets slider value to default if not in min-max range.</summary>
        ///<param name="fMin">New minimal value.</param>
        ///<param name="fMax">New maximum value.</param>
        ///<param name="fDefault">New default value.</param>
        ///<param name="fStep">New step size.</param>
        bool InitParameters(float fMin, float fMax, float fDefault, float fStep);

        ///<summary>Returns true if slider has updated its value in the last tick.</summary>
        bool HasUpdated();

        ///<summary>Sets the distance from viewport.</summary>
        ///<param name="layer">Distance from viewport, less means closer, range: ]0;1[.</param>
        virtual void SetLayerGui(float layer = GUI_DEFAULT_LAYER) override;

        ///<summary>Recalculates and updates the size and position of the rect, call when window resizes.</summary>
        virtual void ReSize() override;

    protected:
        float m_fMin = 0.0f;
        float m_fMax = 100.0f;
        float m_fDefault = 50.0f;
        float m_fStep = 1.0f;
        float m_fRange, m_fStepInverse, m_fValue;
        float m_fPosAbsX;																// X position of the outer float rect
        float m_fCursorToValueFactor;													// Transforms the relative cursor position to a value
        float m_fValueToPositionFactor;													// Transforms a value to a x position between 0 and 1

        bool m_bIsUpdating = false;														// Flag gets set if the user is currently updating the value
        bool m_bHasUpdated = false;														// Flag gets set if the value has updated the current tick

        // Handle
        float m_fHandleWidth = 0.1f;
        CFloatRect m_zfrHandle;
        COverlay m_zoHandle;
        CMaterial m_zmHandleBackground;

        // Handle Track (only visual)
        COverlay m_zoTrackVisual;
        CMaterial m_zmTrackVisual;

        // Value Display
        CWriting m_zwValue;

        ///<summary>Method to be called every tick in the application.</summary>
        ///<param name="fTimeDelta">Time since last tick</param>
        //void Tick(float& fTimeDelta);
        void Tick(float& fTimeDelta, CFloatRect& floatrectFather) override;
    };
}


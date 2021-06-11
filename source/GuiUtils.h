#pragma once
#include "Vektoria\Root.h"
#include <string>

//--------------------------------------------------------------------------------------------
// GuiUtils
//
// Description: Utility class, primarily intended for gui usage.
// Autor      : Alex Grüßhaber
// Copyright  : GNU GPL
//--------------------------------------------------------------------------------------------

namespace V = Vektoria;

static std::string alignCenter(std::string input, int width = 16)
{
	return std::string((width - input.length()) * 0.5, ' ') + input;
}

static std::string alignRight(std::string input, int width = 16)
{
	return std::string(width - input.length(), ' ') + input;
}

///<summary>Returns the absolute position and size of an overlay.</summary>
///<param name="overlay">The overlay to compare against.</param>
static V::CFloatRect fetchRectAbsolutePosition(V::COverlay* overlay)
{
	V::CFloatRect zfrOutput = overlay->GetRect();
	V::CNode* znTmp = overlay;

	while (znTmp->GetParent() != nullptr && znTmp->GetParent()->m_eKind == S_KIND_OVERLAY) {
		znTmp = znTmp->GetParent();
		V::COverlay* zoTmp = static_cast<V::COverlay*>(znTmp);

		zfrOutput.SetXPos(
			zfrOutput.GetXPos() * zoTmp->GetRect().GetXSize() + zoTmp->GetRect().GetXPos()
		);

		zfrOutput.SetYPos(
			zfrOutput.GetYPos() * zoTmp->GetRect().GetYSize() + zoTmp->GetRect().GetYPos()
		);

		zfrOutput.SetXSize(
			zfrOutput.GetXSize() * zoTmp->GetRect().GetXSize()
		);

		zfrOutput.SetYSize(
			zfrOutput.GetYSize() * zoTmp->GetRect().GetYSize()
		);
	}

	return zfrOutput;
}

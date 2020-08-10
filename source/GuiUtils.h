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

static std::string Center(std::string input, int width = 16)
{
	return std::string((width - input.length()) * 0.5, ' ') + input;
}

static std::string Right(std::string input, int width = 16)
{
	return std::string(width - input.length(), ' ') + input;
}

///<summary>Returns the absolute position and size of an overlay.</summary>
///<param name="overlay">The overlay to compare against.</param>
static Vektoria::CFloatRect GetRectAbsolute(Vektoria::COverlay* overlay)
{
	Vektoria::CFloatRect zfrOutput = overlay->GetRect();
	Vektoria::CNode* znTmp = overlay;

	while (znTmp->GetParent() != nullptr && znTmp->GetParent()->m_eKind == S_KIND_OVERLAY) {
		znTmp = znTmp->GetParent();
		Vektoria::COverlay* zoTmp = static_cast<Vektoria::COverlay*>(znTmp);

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

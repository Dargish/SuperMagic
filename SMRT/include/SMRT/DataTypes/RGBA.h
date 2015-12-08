#pragma once

#include <SMRT/SMRT.h>

SMRT_NAMESPACE_ENTER
{
	struct RGBA
	{
		float r, g, b, a;

		static RGBA White();
		static RGBA Black();
		static RGBA Red();
		static RGBA Green();
		static RGBA Blue();

		RGBA();
		RGBA(float r_, float g_, float b_, float a_ = 1.0f);

		RGBA(const RGBA& other);
		RGBA& operator=(const RGBA& other);

		bool operator==(const RGBA& other) const;
		bool operator!=(const RGBA& other) const;
	};
}
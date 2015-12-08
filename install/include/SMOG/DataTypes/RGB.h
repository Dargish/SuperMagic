#pragma once

#include <SMOG/SMOG.h>

SMOG_NAMESPACE_ENTER
{
	struct RGB
	{
		float r, g, b;

		static RGB White();
		static RGB Black();
		static RGB Red();
		static RGB Green();
		static RGB Blue();

		RGB();
		RGB(const RGB& other);
		RGB(float r_, float g_, float b_);

		RGB& operator=(const RGB& other);

		bool operator==(const RGB& other) const;
		bool operator!=(const RGB& other) const;
	};
}
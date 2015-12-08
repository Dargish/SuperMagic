#include <SMRT/DataTypes/RGBA.h>

SMRT_NAMESPACE_ENTER
{
	RGBA RGBA::White()
	{
		return RGBA(1.0f, 1.0f, 1.0f);
	}

	RGBA RGBA::Black()
	{
		return RGBA(0.0f, 0.0f, 0.0f);
	}

	RGBA RGBA::Red()
	{
		return RGBA(1.0f, 0.0f, 0.0f);
	}

	RGBA RGBA::Green()
	{
		return RGBA(0.0f, 1.0f, 0.0f);
	}

	RGBA RGBA::Blue()
	{
		return RGBA(0.0f, 0.0f, 1.0f);
	}

	RGBA::RGBA() :
		r(1.0f), g(1.0f), b(1.0f), a(1.0f)
	{
		
	}

	RGBA::RGBA(float r_, float g_, float b_, float a_ /*= 1.0f*/) :
		r(r_), g(g_), b(b_), a(a_)
	{

	}
	
	RGBA::RGBA(const RGBA& other) :
		r(other.r), g(other.g), b(other.b), a(other.a)
	{

	}

	RGBA& RGBA::operator=(const RGBA& other)
	{
		r = other.r;
		g = other.g;
		b = other.b;
		a = other.a;
		return *this;
	}

	bool RGBA::operator==(const RGBA& other) const
	{
		return (
			r == other.r &&
			g == other.g &&
			b == other.b &&
			a == other.a);
	}

	bool RGBA::operator!=(const RGBA& other) const
	{
		return !(*this == other);
	}
}

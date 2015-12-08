#include <SMOG/DataTypes/RGB.h>

SMOG_NAMESPACE_ENTER
{
	RGB RGB::White()
	{
		return RGB(1.0f, 1.0f, 1.0f);
	}

	RGB RGB::Black()
	{
		return RGB(0.0f, 0.0f, 0.0f);
	}

	RGB RGB::Red()
	{
		return RGB(1.0f, 0.0f, 0.0f);
	}

	RGB RGB::Green()
	{
		return RGB(0.0f, 1.0f, 0.0f);
	}

	RGB RGB::Blue()
	{
		return RGB(0.0f, 0.0f, 1.0f);
	}

	RGB::RGB() :
		r(1.0f), g(1.0f), b(1.0f)
	{
		
	}
	
	RGB::RGB(const RGB& other) :
		r(other.r), g(other.g), b(other.b)
	{

	}

	RGB::RGB(float r_, float g_, float b_) :
		r(r_), g(g_), b(b_)
	{

	}

	RGB& RGB::operator=(const RGB& other)
	{
		r = other.r;
		g = other.g;
		b = other.b;
		return *this;
	}

	bool RGB::operator==(const RGB& other) const
	{
		return (
			r == other.r &&
			g == other.g &&
			b == other.b);
	}

	bool RGB::operator!=(const RGB& other) const
	{
		return !(*this == other);
	}
}

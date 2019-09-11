#include "Math.h"

namespace Numea
{
	
	/*void Function::set(const int& index, std::initializer_list<float> values)
	{
		
	}

	float Function::get(std::initializer_list<float> input)
	{
		std::vector<float> key(input);
		return values[key];
	}
	*/
	
	float Operators::interpolate(const float& x, const float& x0, const float& x1, const float& y0, const float& y1) const
	{
		return y0+(x-x0)*(y1-y0)/(x1-x0);
	}
	
	
	float EulerIntegrator::getNextY(const Function<float, float>& function, const float dt, float t, float y)
	{ 
		return y+dt*function(t, y);
	}

	
}

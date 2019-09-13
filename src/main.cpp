
#include "FileUtils.h"
#include "Plot.h"
#include "Math.h"
#include <cmath>


	int main()
	{
		using namespace Numea;
		
		/*Variable<4> cosine;
		float n = 80.0f;
		for(int i = 0; i<=n; i++)
		{
			float x = (float)i*3.1415f/n;
			float y = (float)cos(x);
			
			float prevX = (float)(i-1)*3.1415f/n;
			float prevY = (float) cos(prevX);
			
			cosine.add({x, y, prevX, (prevY+y)/2.0f});
			
		}
		std::cout << cosine << std::endl;*/
		
		Operators I;
		//std::cout << I.integral(cosine, 0.0f, 3.1415f, 0, 1) << std::endl;*/
		
		
		Function<float, float> vFunc([](float t, float x){return (float)(-cos(x));});//dv/dt = -cos(x) = vFunc(x)
		Function<float, float> xFunc([](float t, float x){return x;});				 //dx/dt = v = xFunc(v);	
		
		Function<float> cosine([](float x){return cos(x);});
		//std::cout << I.integral(cosine, 0.0f, 3.1416f/2.0f, 0.01f) << std::endl;
		
		DataFileWriter fileWriter("test.txt");
		
		EulerIntegrator iterator;
		float t = 0.0f;
		float x = 1.0f;
		float v = 0.0f;
		float dt = 0.001f;
		float tmax = 10.0f;
		Variable<3> c;
		for(int i =0; i<tmax/dt; i++)
		{
			v = iterator.getNextY(vFunc, dt, t, x);
			x = iterator.getNextY(xFunc, dt, t, v);
			t+=dt;
			fileWriter.writeLine(t, x, 0*exp(t));
		}
		
		Plot2d plot("1st plot");
		plot.setXAxisLabel("Time (s)");
		plot.addSeries("test.txt", "y(t)", 0, 1, LineType::LINE);
		plot.addSeries("test.txt", "exp(t)", 0, 2, LineType::LINE);
		plot.display();
		
		
		
		return 0;
	}

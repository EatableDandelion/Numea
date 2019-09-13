#pragma once

#include <map>
#include <vector>
#include <array>
#include <initializer_list>
#include <iostream>
#include <functional>

namespace Numea
{
	
	template<std::size_t N>
	class Variable
	{
		public:
			int add(const std::initializer_list<float>& input)
			{
				std::array<float, N> line;
				int i = 0;
				for(const float& f : input)
				{
					line[i] = f;
					i++;
				}
				values.push_back(line);
				return getSize()-1;
			}
			
			float get(const int& index, const int& column)
			{
				return values[index][column];
			}
			
			std::array<float, N>& operator[](const int& index)
			{
				return values[index];
			}
			
			int getSize() const
			{
				return values.size();
			}
			
			int getDimension() const
			{
				return N;
			}

			
		private:
			std::vector<std::array<float, N>> values;
	};
	
	template<std::size_t N>
	std::ostream& operator<<(std::ostream& stream, Variable<N>& var)
	{
		for(int i = 0; i<var.getSize(); i++)
		{
			for(int j = 0; j<N; j++)
			{
				stream << std::to_string(var[i][j]) << " ";
			}
			stream << std::endl;
		}
		return stream;
	}
	
	/**
	Wrapper for math functions. The template parameter is the list of variable.
	Usage:
	Function<float, float> myFunc([](float v, float w){return v*w;});
	std::cout << myFunc(1.31f, 2.0f) << std::endl;
	*/
	template<typename... Args>
	class Function
	{
		public:
			Function(std::function<float(Args...)> f):func(f)
			{}
			
			float operator()(Args... args) const
			{
				return func(std::forward<Args>(args)...);
			}
			
			std::function<float(Args...)> getFunc()
			{
				return func;
			}
			
			/** Fixes one or several variables as constant:
				Function<float, float> xFunc([](float t, float x){return t+x;});
				Function<float> subF = xFunc.sub<float>(std::placeholders::_1, 1.0f);
			*/
			template<typename... SubArgs, typename... AllArgs>
			Function<SubArgs...> sub(AllArgs... args)
			{
				return Function<SubArgs...>(std::bind(func, std::forward<AllArgs>(args)...));
			}
			
		private:
			std::function<float(Args...)> func;
	};
	
	
	class Operators
	{
		public:
		
			template<std::size_t N>
			float integral(Variable<N>& var, const float& x0, const float& x1, const int& xAxisIndex, const int& yAxisIndex)
			{
				float firstPart = 0.0f;
				float middlePart = 0.0f;
				float lastPart = 0.0f;
				int startIndex = 0;
				int endIndex = 0;
				/** /!\ This calculation assumes that the x values are already sorted!!**/
				
				//Find the lower bound
				int previousIndex = -1;
				int index = 0;
				while((var[index][xAxisIndex] < x0) && index<var.getSize())
				{
					previousIndex = index;
					index++;
				}	
				
				//The bound is found, determine if the range is at the beginning, the middle or the end of the available x values.
				float firstX, firstY, secondX, secondY;
				if(previousIndex != -1 && index < var.getSize()-1) // The integration range of integration is in the middle, best case scenario
				{
					firstX = x0;
					secondX = var[index][xAxisIndex];
					
					firstY = interpolate(firstX, var[previousIndex][xAxisIndex], var[index][xAxisIndex], var[previousIndex][yAxisIndex], var[index][yAxisIndex]);
					secondY = var[index][yAxisIndex];
					firstPart = (secondY+firstY)/2.0f*(secondX-firstX);
					startIndex = index;
					
				}
				else if(previousIndex == -1)//The integration range starts before the available data: change the lower bound to the first available x
				{
					startIndex = 0;
				}
				else // The integration range starts after the last data point, the integral is 0
				{
					return 0.0f;
				}
				//startIndex = index;
				
				//Find the upper bound
				previousIndex = startIndex;
				index = previousIndex+1;
				while((var[index][xAxisIndex] < x1) && index<var.getSize())
				{
					previousIndex = index;
					index++;
				}
				endIndex = index;
				
				float penultimateX, penultimateY, ultimateX, ultimateY;
				if(previousIndex != startIndex && index < var.getSize())
				{
					penultimateX = var[previousIndex][xAxisIndex];
					ultimateX = x1;
					
					penultimateY = var[previousIndex][yAxisIndex];
					ultimateY = interpolate(ultimateX, var[previousIndex][xAxisIndex], var[index][xAxisIndex], var[previousIndex][yAxisIndex], var[index][yAxisIndex]); 
					endIndex = previousIndex;
					lastPart = (ultimateY+penultimateY)/2.0f*(ultimateX-penultimateX);
					
				}
				else if(index == var.getSize())//The integration range ends after the available data.
				{
					endIndex = index-1;
				}

				for(int i = startIndex; i<endIndex; i++)
				{
					
					middlePart += (var[i+1][yAxisIndex]+var[i][yAxisIndex])/2.0f * (var[i+1][xAxisIndex]-var[i][xAxisIndex]);
					
				}
				
				return firstPart+middlePart+lastPart;
			}
		
			float integral(Function<float>& func, const float& x0, const float& x1, const float& dx);
		
			float interpolate(const float& x, const float& x0, const float& x1, const float& y0, const float& y1) const;
		
	};
	
	class EulerIntegrator
	{
		public:
		
			float getNextY(const Function<float, float>& function, const float dt, float t, float y);
			
		private:
			
		
	};
}
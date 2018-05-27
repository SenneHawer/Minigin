#pragma once

namespace sen
{
	struct float2
	{
		float2()
			:x(0.0f)
			, y(0.0f)
		{}
		float2(float x, float y)
			:x(x)
			, y(y)
		{}

		float x, y;
	};
	
	struct Rectf
	{
		Rectf()
			:left(0.0f)
			, bottom(0.0f)
			, width(0.0f)
			, height(0.0f)
		{}

		Rectf(float left, float bottom, float width, float height)
			:left(left)
			, bottom(bottom)
			, width(width)
			, height(height)
		{}

		float left;
		float bottom;
		float width;
		float height;
	};

	struct Circlef
	{
		Circlef()
			:center(0.0f, 0.0f)
			,radius(0.0f)
		{}
		Circlef(const float2& center, float radius)
			:center(center)
			,radius(radius)
		{}
		Circlef(float centerX, float centerY, float radius)
			:center(centerX, centerY)
			,radius(radius)
		{}

		//Variables
		float2 center;
		float radius;
	};


}



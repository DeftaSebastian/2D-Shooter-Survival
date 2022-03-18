#pragma once

#include "components/simple_scene.h"

namespace m1
{
	class Bullet
	{
	private:
		float translateX;
		float translateY;
		float directionX;
		float directionY;
		float direction;
	
	public:
		Bullet()
		{

		};

		Bullet(float translateX, float translateY)
		{
			this->translateX = translateX;
			this->translateY = translateY;
		};

		float getTranslateX()
		{
			return this->translateX;
		};

		float getTranslateY()
		{
			return this->translateY;
		};

		float getDirection()
		{
			return this->direction;
		}

		float getDirectionX()
		{
			return this->directionX;
		};

		float getDirectionY()
		{
			return this->directionY;
		};

		void setTranslateX(float newTranslateX)
		{
			this->translateX = newTranslateX;
		};

		void setTranslateY(float newTranslateY)
		{
			this->translateY = newTranslateY;
		};

		void setDirection(float newDirection)
		{
			this->direction = newDirection;
		};

		void setDirectonX(float newDirectionX)
		{
			this->directionX = newDirectionX;
		};

		void setDirectionY(float newDirectionY)
		{
			this->directionY = newDirectionY;
		}

		~Bullet()
		{

		};
	};

}
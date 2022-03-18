#pragma once

#include "components/simple_scene.h"


namespace m1
{
	class Enemies 
	{
	private:
		float spawnX;
		float spawnY;
		float translateX;
		float translateY;
		float speed;
		float directionEnemy;

	public:
		Enemies()
		{

		};

		Enemies(float spawnX, float spawnY, float translateX, float translateY, float speed, float directionEnemy)
		{
			this->spawnX = spawnX;
			this->spawnY = spawnY;
			this->spawnX = spawnX;
			this->spawnY = spawnY;
			this->translateX = translateX;
			this->translateY = translateY;
			this->speed = speed;
			this->directionEnemy = directionEnemy;
		};

		float getSpawnX()
		{
			return this->spawnX;
		};

		float getSpawnY()
		{
			return this->spawnY;
		};


		float getTranslateX()
		{
			return this->translateX;
		};

		float getTranslateY()
		{
			return this->translateY;
		};

		float getSpeed()
		{
			return this->speed;
		}

		float getDirectionEnemy()
		{
			return this->directionEnemy;
		}
		void setSpawnX(float newSpawnX)
		{
			this->spawnX = newSpawnX;
		};

		void setSpawnY(float newSpawnY)
		{
			this->spawnY = newSpawnY;
		};

		void setTranslateX(float newTranslateX)
		{
			this->translateX = newTranslateX;
		};

		void setTranslateY(float newTranslateY)
		{
			this->translateY = newTranslateY;
		};

		void setSpeed(float speed)
		{
			this->speed = speed;
		}

		void setDirectionEnemy(float newDirection)
		{
			this->directionEnemy = newDirection;
		}

		~Enemies()
		{

		};


	};
}
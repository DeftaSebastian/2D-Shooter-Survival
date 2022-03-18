#pragma once

#include "components/simple_scene.h"

namespace m1
{
	class HealthKit
	{
	private:
		float spawnX;
		float spawnY;

	public:
		HealthKit()
		{

		};

		HealthKit(float spawnX, float spawnY)
		{
			this->spawnX = spawnX;
			this->spawnY = spawnY;
		};

		float getSpawnX()
		{
			return this->spawnX;
		};

		float getSpawnY()
		{
			return this->spawnY;
		};

		void setSpawnX(float newSpawnX)
		{
			this->spawnX = newSpawnX;
		};

		void setSpawnY(float newSpawnY)
		{
			this->spawnY = newSpawnY;
		};

		~HealthKit()
		{

		};
	};

}
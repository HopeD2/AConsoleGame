#pragma once

#include <list>

#include "ProjectileCollisionDetector.h"

template <typename T>
class CollisionDetectorManager {
public:
	virtual ~CollisionDetectorManager(){}
	virtual void Task() = 0;
};

template <>
class CollisionDetectorManager<CollisionDetector<Projectile> >{
private:
	std::vector<CollisionDetector<Projectile>> detectors;

public:
	CollisionDetectorManager() {

	}

	// Copy for now, think of a better way later on
	CollisionDetectorManager(std::vector<CollisionDetector<Projectile> > _detectors): detectors(_detectors) {
		
	}

	virtual void Task() {
		for (size_t i = 0; i < detectors.size(); i++)
		{
			detectors[i].CollisionTask();
		}
	}
};
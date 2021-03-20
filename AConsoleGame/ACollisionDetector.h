#pragma once

template <typename T>
class CollisionDetector{
public:
	CollisionDetector(){ }
	virtual ~CollisionDetector() {};
	virtual void CollisionTask() = 0;
};
#pragma once

#include "Observer.h"

template <typename T>
class Subject{
public:
	virtual ~Subject() {};
	virtual bool Attach(T *observer) = 0;
	virtual bool Detach(T *observer) = 0;
	virtual void Notify(T *observer) = 0;
};
#pragma once

class Observer {
public:
	virtual ~Observer() {};
	virtual bool Update() = 0;
};
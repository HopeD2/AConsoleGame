#pragma once

class AController {
public:
	virtual void GetInputs() = 0;
	virtual void CheckInputs(float elapsedTime) = 0;
};
#pragma once

class ConsoleObject {
public:
	enum FireDirection {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	struct Position {
		float x;
		float y;
	};

	struct Size {
		int length;
		int breadth;
	};

	struct Velocity {
		float dx;
		float dy;
	};

protected:
	Position pos;
	Size size;
	Velocity velo;
public:
	ConsoleObject() {
		pos = { -1,-1 };
		size = { 0,0 };
		velo = { 0,0 };
	}

	ConsoleObject(Position p, Size s, Velocity v) {
		pos = p;
		size = s;
		velo = v;
	}

	~ConsoleObject() {

	}

	const Position& GetPosition() const;
	const Size& GetSize() const;
	const Velocity& GetVelocity() const;

	void setPosition(Position const p);
	void setSize(Size const s);
	void setVelocity(Velocity const v);

	virtual void Tick(float elapsedTime) = 0;
};

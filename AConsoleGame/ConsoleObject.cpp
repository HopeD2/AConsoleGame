
#include "ConsoleObject.h"

ConsoleObject::Position const& ConsoleObject::GetPosition() const
{
	return pos;
}

const ConsoleObject::Size & ConsoleObject::GetSize() const
{
	return size;
}

const ConsoleObject::Velocity & ConsoleObject::GetVelocity() const
{
	return velo;
}

void ConsoleObject::setPosition(Position const p)
{
	pos = p;
}

void ConsoleObject::setSize(Size const s)
{
	size = s;
}

void ConsoleObject::setVelocity(Velocity const v)
{
	velo = v;
}
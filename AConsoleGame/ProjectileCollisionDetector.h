#pragma once

#include <Windows.h>
#include <list>
#include <iterator>

#include "Projectile.h"
#include "ProjectileSubject.h"
#include "ACollisionDetector.h"
//#include "Engine.h"
#include "Pawn.h"

template <>
class CollisionDetector<Projectile> : public Subject<Projectile>{
public:
	CollisionDetector() {}
	virtual ~CollisionDetector() {
		observers.clear();
		pawns.clear();
	};
private:
	std::list<Projectile*> observers;
	std::list<Pawn*> pawns;
public:	
	// Inherited via Subject
	virtual bool Attach(Projectile * observer) override {
		// Add observers
		if (observer) {
			observers.push_back(observer);
			return true;
		}
		return false;
	}

	virtual bool Detach(Projectile * observer) override {
		// Remove em
		if (observer) {
			observers.remove(observer);
			return true;
		}
		return false;
	}
	
	virtual void Notify(Projectile* observer) override {
		observer->Update();
	}

	bool addPawn(Pawn* pawn) {
		if (pawn) {
			pawns.push_back(pawn);
			return true;
		}
		return false;
	}

	bool removePawn(Pawn* pawn) {
		if (pawn) {
			pawns.remove(pawn);
			return true;
		}
		return false;
	}


	virtual void CollisionTask(){
		for (std::list<Projectile*>::iterator it = observers.begin(); it != observers.end(); it++ )
		{
			for (std::list<Pawn*>::iterator pawnIt = pawns.begin(); pawnIt != pawns.end(); pawnIt++)
			{
				ConsoleObject::Position const& pawnPos = (*pawnIt)->GetPosition();
				ConsoleObject::Size const& pawnSize = (*pawnIt)->GetSize();
				ConsoleObject::Position const& projectilePos = (*it)->GetPosition();
				int projectilePosAsPawnPosX = (int)projectilePos.x - (int)pawnPos.x;
				int projectilePosAsPawnPosY = (int)projectilePos.y - (int)pawnPos.y;

				if (projectilePosAsPawnPosX >= 0 && projectilePosAsPawnPosX < pawnSize.length &&
					projectilePosAsPawnPosY >= 0 && projectilePosAsPawnPosY < pawnSize.breadth) 
				{
					//ConsoleObject::Position const& projectilePosAsPawnPos = { ,  };
					if ((*pawnIt)->TogglePixel(projectilePosAsPawnPosX, projectilePosAsPawnPosY)) {
						Notify(*it);
					}
				}
			}
		}
	}
};
#include "Entity.h"
#include <iostream>

Entity::Entity(float velocity, float angle, EntityType t) {

	Speed = velocity;

	MovementAngle = angle;

	mType = t;

	RemoveFromWorld = false;

}

Entity::~Entity() {
	std::cout << __FUNCTION__ << std::endl;

}

EntityType Entity::GetType() {
	return mType;
}
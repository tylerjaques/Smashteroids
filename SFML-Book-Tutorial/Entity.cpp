#include "Entity.h"

Entity::Entity(float velocity, float angle, EntityType t) {

	Speed = velocity;

	MovementAngle = angle;

	mType = t;
}

EntityType Entity::GetType() {
	return mType;
}
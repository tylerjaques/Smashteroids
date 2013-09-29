#include "Bullet.h"

const float Bullet::Distance = 250.0f;

Bullet::Bullet(float x, float y, float angle, float velocity) : translationAngle(angle) {
	setPosition(x, y);
}
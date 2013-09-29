#ifndef __BULLET_H__
#define __BULLET_H__
#include <SFML/Graphics.hpp>

class Bullet : public sf::RectangleShape {

private:
	float translationAngle;

public:
	static const float Distance;

	Bullet(float x, float y, float angle, float velocity);
};

#endif
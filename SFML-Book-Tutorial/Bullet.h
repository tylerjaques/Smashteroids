#ifndef __BULLET_H__
#define __BULLET_H__
#include "Entity.h"
#include <SFML/Graphics.hpp>

class Bullet : public Entity {

private:
	sf::RectangleShape mShape;
	float mVelocity;

public:
	static const float Distance;

	Bullet(float x, float y, float angle, float velocity);

	//inherited from entity
	void update(sf::Time deltaTime);
	
	sf::Vector2f GetPosition();
	void SetPosition(float x, float y);
	float GetRotation();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
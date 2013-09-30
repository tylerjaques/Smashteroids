#ifndef __BULLET_H__
#define __BULLET_H__
#include "Entity.h"
#include <memory>
#include <SFML/Graphics.hpp>

class Bullet : Entity {

private:
	sf::RectangleShape mShape;
	float mDistanceTraveled;
	static const float mMaxDistance;
	
	//the only constructor is private -> users must use the create method
	Bullet(float x, float y, float angle);

public:
	static const float Distance;

	//inherited from entity
	void update(sf::Time deltaTime);
	
	sf::Vector2f GetPosition();
	void SetPosition(float x, float y);
	float GetRotation();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	static std::unique_ptr<Entity> Create(float x, float y, float angle);
	sf::FloatRect GetBoundingBox();
};

#endif
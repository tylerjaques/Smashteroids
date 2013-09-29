#ifndef __ENTITY_H__
#define __ENTITY_H__
#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable {
public:
	virtual void update(sf::Time deltaTime) = 0;
	
	virtual sf::Vector2f GetPosition() = 0;
	virtual void SetPosition(float x, float y) = 0;
	virtual float GetRotation() = 0;
};
#endif
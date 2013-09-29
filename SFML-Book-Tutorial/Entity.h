#ifndef __ENTITY_H__
#define __ENTITY_H__
#include <SFML/Graphics.hpp>

//enum class EntityType { Player, Bullet, Asteroid };

class Entity : public sf::Drawable {
public:
	float Speed;
	float MovementAngle;
	bool RemoveFromWorld;

	virtual void update(sf::Time deltaTime) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	virtual sf::Vector2f GetPosition() = 0;
	virtual void SetPosition(float x, float y) = 0;
	virtual float GetRotation() = 0;
	virtual sf::FloatRect GetBoundingBox() = 0;
};
#endif
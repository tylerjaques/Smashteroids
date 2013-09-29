#ifndef __ASTEROID_H__
#define __ASTEROID_H__
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>
#include "ConfigMap.h"
#include "Entity.h"

class Asteroid : public Entity {

private:
	sf::CircleShape mShape;
	int mRotationSpeed;
	int mRotationDirection;

public:

	Asteroid(std::default_random_engine& randEngine);
	~Asteroid(void);

	//inherits from Entity
	void update(sf::Time deltaTime);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Vector2f GetPosition();
	void SetPosition(float x, float y);
	float GetRotation();
	sf::FloatRect GetBoundingBox();

	
};

#endif


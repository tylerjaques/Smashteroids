#ifndef __ASTEROID_H__
#define __ASTEROID_H__
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ConfigMap.h"
#include "Entity.h"

class Asteroid : public Entity {

private:
	sf::CircleShape mShape;
	int mSpeed;
	int mMovingAngle;
	int mRotationSpeed;
	int mRotationDirection;
	
	static const float PlayerSpeed;

public:
	Asteroid(void);
	~Asteroid(void);

	//inherits from Entity
	void update(sf::Time deltaTime);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Vector2f GetPosition();
	void SetPosition(float x, float y);
	float GetRotation();


	
};

#endif


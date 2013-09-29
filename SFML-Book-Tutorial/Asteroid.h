#ifndef __ASTEROID_H__
#define __ASTEROID_H__
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ConfigMap.h"

class Asteroid
{
public:
	Asteroid(void);
	~Asteroid(void);
	sf::ConvexShape shape;

private:
	void CreateAsteroid();

};

#endif


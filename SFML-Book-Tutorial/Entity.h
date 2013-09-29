#ifndef __ENTITY_H__
#define __ENTITY_H__
#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable {
public:
	virtual void update() = 0;
};
#endif
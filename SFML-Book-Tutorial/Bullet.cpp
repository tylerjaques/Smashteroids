#include "Bullet.h"
#include "PI.h"
#include <iostream>

const float Bullet::Distance = 250.0f;
const float Bullet::mMaxDistance = 250.0f;

//constructor is private
Bullet::Bullet(float x, float y, float angle) : Entity(250.0f, angle, EntityType::Bullet) {

	mDistanceTraveled = 0;

	mShape.setPosition(x, y);
	mShape.setRotation(MovementAngle);

	mShape.setSize(sf::Vector2f(15, 3));

	mShape.setFillColor(sf::Color::Transparent);
	mShape.setOutlineThickness(1);
	mShape.setOutlineColor(sf::Color::Red);
}

std::unique_ptr<Entity> Bullet::Create(float x, float y, float angle) {
	return std::unique_ptr<Entity>(new Bullet(x, y, angle));
}

sf::Vector2f Bullet::GetPosition() {
	return mShape.getPosition();
}

void Bullet::SetPosition(float x, float y) {
	mShape.setPosition(x, y);
}

float Bullet::GetRotation() {
	return mShape.getRotation();
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mShape, states);
}

void Bullet::update(sf::Time deltaTime) {

	if(mDistanceTraveled > mMaxDistance) {
		RemoveFromWorld = true;
		return;
	}
	
	float framespeed = Speed * deltaTime.asSeconds();
	
	float angle = MovementAngle * (PI/180.0f);

	mDistanceTraveled += framespeed;
	
	mShape.move(std::cos(angle)*(framespeed),std::sin(angle)*(framespeed));
}

sf::FloatRect Bullet::GetBoundingBox() {
	return mShape.getGlobalBounds();
}

Bullet::~Bullet() {
	std::cout << __FUNCTION__ << std::endl;
	Entity::~Entity();
	

}
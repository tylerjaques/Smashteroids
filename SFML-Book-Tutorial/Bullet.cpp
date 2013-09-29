#include "Bullet.h"
#include "PI.h"

const float Bullet::Distance = 250.0f;

//constructor is private
Bullet::Bullet(float x, float y, float angle) {

	mDistanceTraveled = 0;

	Speed = 50.0f;
	MovementAngle = angle;

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
	
	float speed = Speed * deltaTime.asSeconds();
	
	float angle = MovementAngle * (PI/180.0f);

	mDistanceTraveled += Speed;
	
	mShape.move(std::cos(angle)*(speed),std::sin(angle)*(speed));
}

sf::FloatRect Bullet::GetBoundingBox() {
	throw std::exception("Not Implemented!");
	return sf::FloatRect(0, 0, 0, 0);
}
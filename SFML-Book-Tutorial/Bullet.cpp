#include "Bullet.h"

const float Bullet::Distance = 250.0f;

//constructor is private
Bullet::Bullet(float x, float y, float angle, float velocity) : mVelocity(velocity) {

	Speed = 0;

	mShape.setPosition(x, y);
	mShape.setRotation(angle);

	mShape.setSize(sf::Vector2f(15, 15));

	mShape.setFillColor(sf::Color::Transparent);
	mShape.setOutlineThickness(1);
	mShape.setOutlineColor(sf::Color::White);
}

std::unique_ptr<Entity> Bullet::Create(float x, float y, float angle, float velocity) {
	return std::unique_ptr<Entity>(new Bullet(x, y, angle, velocity));
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

}
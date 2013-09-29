#include "Asteroid.h"

const float PI = std::atan(1.0f) * 4.0f;

Asteroid::Asteroid(std::default_random_engine& randEngine) : Entity(0, 0, EntityType::Asteroid) {
	
	int randomSize = randEngine() % 80 + 40;

	int randomNumOfSides = randEngine() % 10 + 6;

	//Create asteroid of random size and shape
	mShape = sf::CircleShape(randomSize, randomNumOfSides);
	mShape.setFillColor(sf::Color::Transparent);
	mShape.setOutlineColor(sf::Color::White);
	mShape.setOutlineThickness(2);
	mShape.setOrigin(mShape.getPosition().x + mShape.getRadius(),mShape.getPosition().y + mShape.getRadius());

	//Create asteroid at random location
	
	//Point asteroid in random direction
	MovementAngle = randEngine() % 360 + 0;
	
	//Move asteroid at random speed
	Speed = randEngine() % 10 + 150;

	//Rotate asteroid in random direction
	mRotationDirection = randEngine() % 1 + 0;

	//Rotate asteroid at random speed
	mRotationSpeed = randEngine() % 50 + 30;

	int i = 0;
}

Asteroid::~Asteroid(void) {

}

void Asteroid::update(sf::Time deltaTime){
	float speed = Speed * deltaTime.asSeconds();
	float angle = MovementAngle * (PI/180.0f);
	float rotation = 0;
	

	if (mRotationDirection == 0)
		rotation -= mRotationSpeed * deltaTime.asSeconds();
	else
		rotation += mRotationSpeed * deltaTime.asSeconds();

		
	mShape.move(std::cos(angle)*(speed),std::sin(angle)*(speed));		
	mShape.rotate(rotation);
}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mShape, states);
}

sf::Vector2f Asteroid::GetPosition() {
	return mShape.getPosition();
}
void Asteroid::SetPosition(float x, float y) {
	mShape.setPosition(x, y);
}

float Asteroid::GetRotation() {
	return MovementAngle;
}


sf::FloatRect Asteroid::GetBoundingBox() {
	throw exception("Not Implemented!");
	return sf::FloatRect(0, 0, 0, 0);
}

std::unique_ptr<Entity> Asteroid::Create(std::default_random_engine& randEngine) {
	return std::unique_ptr<Entity>(new Asteroid(randEngine));
}



#include "Asteroid.h"
#include <ctime>

const float PI = std::atan(1.0f) * 4.0f;

Asteroid::Asteroid(void) {
	srand(time(NULL));

	int randomSize = rand() % 120 + 50;

	int randomNumOfSides = rand() % 10 + 4;

	//Create asteroid of random size and shape
	mShape = sf::CircleShape(randomSize, randomNumOfSides);
	mShape.setFillColor(sf::Color::Transparent);
	mShape.setOutlineColor(sf::Color::White);
	mShape.setOutlineThickness(2);
	mShape.setOrigin(mShape.getPosition().x + mShape.getRadius(),mShape.getPosition().y + mShape.getRadius());

	//Create asteroid at random location
	
	//Point asteroid in random direction
	mMovingAngle = rand() % 360 + 0;
	
	//Move asteroid at random speed
	mSpeed = rand() % 50 + 200;

	//Rotate asteroid in random direction
	mRotationDirection = rand() % 1 + 0;

	//Rotate asteroid at random speed
	mRotationSpeed = rand() % 50 + 30;


}

Asteroid::~Asteroid(void) {

}

void Asteroid::update(sf::Time deltaTime){
	float speed = mSpeed * deltaTime.asSeconds();
	float angle = mMovingAngle * (PI/180.0f);
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
	return mMovingAngle;
}



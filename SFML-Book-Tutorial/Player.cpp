#include "Player.h"
#include "PI.h"
#include <iostream>

const float Player::PlayerSpeed = 250.f;

Player::Player() : mMaxSpeed(1000.0f), mHealth(100.0f), mAcceleration(20.0f),
	FlyingAngle(270), IsMovingUp(false), IsRotatingLeft(false), IsRotatingRight(false), Entity(0, 0, EntityType::Player) {

		mConvex.setPosition(200.f, 200.f);
	
		CreatePlayerShape();
}

Player::~Player(void) { 
	std::cout << __FUNCTION__ << std::endl;
	Entity::~Entity();
}

std::unique_ptr<Entity> Player::Shoot() {
	GunSound.play();

	sf::Vector2f pos = GetPosition();
	float translationAngle = mConvex.getRotation();
	
	return std::unique_ptr<Entity>(Bullet::Create(pos.x, pos.y, translationAngle));
}

void Player::Accelerate() {
	Speed += mAcceleration;
	if(Speed > mMaxSpeed)
		Speed = mMaxSpeed;
}

void Player::ApplyResistance(float resistance) {
	Speed -= resistance;
	if(Speed <= 0.0f)
	{
		Speed = 0.0f;
	}
}

void Player::Create(const SoundManager* soundMngr) {

	MoveSound.setBuffer(soundMngr->get("drill"));
	MoveSound.setLoop(true);
	GunSound.setBuffer(soundMngr->get("lazer"));
}

void Player::CreatePlayerShape() {

	mConvex.setPointCount(4);

	mConvex.setOrigin(30.0f,30.0f);

	mConvex.setPoint(0,sf::Vector2f(0.0f,0.0f));
	mConvex.setPoint(1,sf::Vector2f(60.0f,30.0f));
	mConvex.setPoint(2,sf::Vector2f(0.0f,60.0f));
	mConvex.setPoint(3,sf::Vector2f(15.0f,30.0f));


	mConvex.setFillColor(sf::Color::Transparent);
	mConvex.setOutlineColor(sf::Color::White);
	mConvex.setOutlineThickness(2.0f);

	mConvex.setRotation(FlyingAngle);
}

void Player::update(sf::Time deltaTime) {

	float speed = Speed * deltaTime.asSeconds();

	float rotation = 0;
	
	if (IsMovingUp) {
		Accelerate();		
		FlyingAngle = mConvex.getRotation();
	}

	if (IsRotatingLeft)
		rotation -= PlayerSpeed * deltaTime.asSeconds();

	if (IsRotatingRight)
		rotation += PlayerSpeed * deltaTime.asSeconds();
	
	float angle = FlyingAngle * (PI/180.0f);
	
	mConvex.move(std::cos(angle)*(speed),std::sin(angle)*(speed));		

	ApplyResistance(10.0f);
	mConvex.rotate(rotation);

	//sounds
	if(IsMovingUp) {
		if(MoveSound.getStatus() != sf::Sound::Playing) {
			MoveSound.play();
		}
	}
	else {
		MoveSound.stop();
	}
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mConvex, states);
}

sf::Vector2f Player::GetPosition() {
	return mConvex.getPosition();
}

void Player::SetPosition(float x, float y) {
	mConvex.setPosition(x, y);
}

float Player::GetRotation() {
	return mConvex.getRotation();
}

sf::FloatRect Player::GetBoundingBox() {
	throw exception("Not Implemented!");
	return sf::FloatRect(0, 0, 0, 0);
}
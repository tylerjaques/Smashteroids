#include "Player.h"


Player::Player()
{
	mMaxSpeed = 1000.0f;
	mHealth = 100.0f;
	Speed = 0.0f;
	mAcceleration = 20.0f;
	FlyingAngle = 270;
	setPosition(200.f, 200.f);
	CreatePlayerShape();
}

Player::~Player(void) { }

void Player::Shoot() {
	GunSound.play();
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

void Player::Create(sf::SoundBuffer& moveBuff, sf::SoundBuffer& gunBuff) {

	MoveSound.setBuffer(moveBuff);
	MoveSound.setLoop(true);

	GunSound.setBuffer(gunBuff);
}

void Player::CreatePlayerShape() {
	setPointCount(4);

	setOrigin(30.0f,30.0f);

	setPoint(0,sf::Vector2f(0.0f,0.0f));
	setPoint(1,sf::Vector2f(60.0f,30.0f));
	setPoint(2,sf::Vector2f(0.0f,60.0f));
	setPoint(3,sf::Vector2f(15.0f,30.0f));


	setFillColor(sf::Color::Transparent);
	setOutlineColor(sf::Color::White);
	setOutlineThickness(2.0f);

	setRotation(270);

}


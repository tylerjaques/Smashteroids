#include "Player.h"

const float Player::PlayerSpeed = 250.f;
const float PI = std::atan(1.0f) * 4.0f;

Player::Player() : mMaxSpeed(1000.0f), mHealth(100.0f), Speed(0.0f), mAcceleration(20.0f),
	FlyingAngle(270), mIsMovingUp(false), mIsRotatingLeft(false), mIsRotatingRight(false), mIsMovingDown(false) {

		mConvex.setPosition(200.f, 200.f);
	
		CreatePlayerShape();
}

Player::~Player(void) { }

Bullet Player::Shoot() {
	GunSound.play();

	sf::Vector2f pos = GetPosition();
	float translationAngle = FlyingAngle;
	
	return Bullet(pos.x, pos.y, translationAngle, 50);
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
	
	if (mIsMovingUp) {
		Accelerate();		
		FlyingAngle = mConvex.getRotation();
	}

	if (mIsRotatingLeft)
		rotation -= PlayerSpeed * deltaTime.asSeconds();

	if (mIsRotatingRight)
		rotation += PlayerSpeed * deltaTime.asSeconds();
	
	float angle = FlyingAngle * (PI/180.0f);
	
	mConvex.move(std::cos(angle)*(speed),std::sin(angle)*(speed));		

	ApplyResistance(10.0f);
	mConvex.rotate(rotation);
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

void Player::HandlePlayerInput(sf::Keyboard::Key key, bool isPressed) {

	mIsMovingUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	
	mIsMovingDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

	mIsRotatingLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);

	mIsRotatingRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

	if(mIsMovingUp) {
		if(MoveSound.getStatus() != sf::Sound::Playing) {
			MoveSound.play();
		}
	}
	else {
		MoveSound.stop();
	}
}
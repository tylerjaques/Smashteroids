#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ConfigMap.h"
#include "SoundManager.h"
#include "Bullet.h"
#include "Entity.h"

class Player : public Entity {
private:
	int mHealth;
	float mAcceleration;
	float mMaxSpeed;
	void CreatePlayerShape();
	sf::ConvexShape mConvex;

	bool mIsMovingUp;
	bool mIsRotatingLeft;
	bool mIsRotatingRight;
	bool mIsMovingDown;
	
	static const float PlayerSpeed;

public:
	sf::Sound GunSound;
	sf::Sound MoveSound;
	float Speed;
	float FlyingAngle;
	sf::Transform Tran;
	float mSpeed;
	sf::Transform trans;
	
	Player();
	~Player();

	void Accelerate();
	void ApplyResistance(float resistance);

	Bullet Shoot();
	void Create(const SoundManager* soundMngr);
	void HandlePlayerInput(sf::Keyboard::Key key, bool isPressed);

	//inherits from Entity
	void update(sf::Time deltaTime);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Vector2f GetPosition();
	void SetPosition(float x, float y);
	float GetRotation();
};

#endif
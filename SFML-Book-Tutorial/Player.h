#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ConfigMap.h"

class Player : public sf::ConvexShape
{
private:
	int mHealth;
	float mAcceleration;
	float mMaxSpeed;
	void CreatePlayerShape();

public:
	sf::Sound mGunSound;

	Player();
	void Shoot();
	void Accelerate();
	void ApplyResistance(float resistance);
	~Player();

	float Speed;
	float FlyingAngle;
	sf::Transform Tran;


};

#endif
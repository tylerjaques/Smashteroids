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

	void Shoot();
	void Create(sf::SoundBuffer& moveBuff, sf::SoundBuffer& gunBuff);
};

#endif
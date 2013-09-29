#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ConfigMap.h"
#include "SoundManager.h"
#include "Bullet.h"
#include "Entity.h"
#include <memory>

class Player : public Entity {
private:
	int mHealth;
	float mAcceleration;
	float mMaxSpeed;
	void CreatePlayerShape();
	sf::ConvexShape mConvex;	
	static const float PlayerSpeed;

public:
	bool IsMovingUp;
	bool IsRotatingLeft;
	bool IsRotatingRight;

	sf::Sound GunSound;
	sf::Sound MoveSound;
	float FlyingAngle;
	sf::Transform Tran;
	float mSpeed;
	sf::Transform trans;
	
	Player();

	void Accelerate();
	void ApplyResistance(float resistance);

	std::unique_ptr<Entity> Shoot();
	void Create(const SoundManager* soundMngr);

	//inherits from Entity
	void update(sf::Time deltaTime);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Vector2f GetPosition();
	void SetPosition(float x, float y);
	float GetRotation();
	sf::FloatRect GetBoundingBox();
};

#endif
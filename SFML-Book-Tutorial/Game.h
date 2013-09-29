#ifndef __GAME_H__
#define __GAME_H__
#include <SFML/Graphics.hpp>
#include "ConfigMap.h"
#include "Player.h"
#include "SoundManager.h"
#include <vector>

class Game : sf::NonCopyable {
	
private:
	sf::RenderWindow mWindow;
	sf::Texture mTexture;
	Player mPlayer;
	sf::CircleShape mPolygon;
	SoundManager mSoundManager;
	sf::Sound mSound;
	std::vector<sf::Drawable> mDrawables;


	static const float		PlayerSpeed;
	static const sf::Time	TimePerFrame;

	sf::Font mFont;
	sf::Text mStatisticsText;
	sf::Time mStatisticsUpdateTime;
	std::size_t mStatisticsNumFrames;

	bool mIsMovingUp, mIsMovingDown, mIsMovingLeft, mIsMovingRight, mIsRotatingLeft, mIsRotatingRight;

	Config::ConfigMap Settings;


public:
	Game();
	void Run();

private:
	void Load();
	void ProcessEvents();
	void Update(sf::Time deltaTime);
	void UpdateStatistics(sf::Time deltaTime);
	void Render();
	void HandlePlayerInput(sf::Keyboard::Key key, bool isPressed);
};
#endif
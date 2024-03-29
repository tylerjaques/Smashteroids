#ifndef __GAME_H__
#define __GAME_H__
#include <SFML/Graphics.hpp>
#include "ConfigMap.h"
#include "Player.h"
#include "Asteroid.h"
#include "SoundManager.h"
#include "Menu.h"
#include <vector>
#include <random>

typedef std::vector<std::unique_ptr<Entity> >::iterator EntityIterator;

class Game : sf::NonCopyable {
	
private:
	sf::RenderWindow mWindow;
	sf::Texture mTexture;
	Player mPlayer;
	SoundManager mSoundManager;
	sf::Sound mSound;
	std::vector<std::unique_ptr<Entity> > mEntities;
	std::vector<int> mItemsToDeleteIndexes;

	static const sf::Time	TimePerFrame;
	std::default_random_engine randEngine;

	sf::Font mFont;
	sf::Text mStatisticsText;
	sf::Time mStatisticsUpdateTime;
	std::size_t mStatisticsNumFrames;

	ConfigMap Settings;
	Menu mMenu;

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
	void HandleOffScreenObjects();
	void HandleCollision();
	void SpawnAsteroids(int amount);

};
#endif
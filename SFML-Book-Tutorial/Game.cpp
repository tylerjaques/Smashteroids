#include "Game.h"
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>

//const initializer
const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

//book initializes mPlayer() after mWindow, but it isn't necessary
Game::Game() : mIsMovingDown(false), 
	mIsMovingUp(false), mIsRotatingLeft(false), mIsRotatingRight(false), mStatisticsNumFrames(0), mStatisticsUpdateTime(sf::Time::Zero) {

	try {

		//get window settings from the config file
		Settings.LoadFromFile("./Resources/Configs/Settings.config");

		//build the window using specified settings
		float height = Settings.getAs<float>("height");
		float width = Settings.getAs<float>("width");
		bool vsync = Settings.getAs<bool>("vsync");
		bool fullscreen = Settings.getAs<bool>("fullscreen");

		sf::Uint32 hWndStyle = sf::Style::Default;

		if(fullscreen)
			hWndStyle = sf::Style::Fullscreen;

		mWindow.create(sf::VideoMode(width, height), "SFML App", hWndStyle);
	}
	catch(std::exception ex) {
		cout << "Error in " << __FUNCTION__ << "\n--" << ex.what();
	}
}

/*
	Loads game resources once window is shown.  Resources needed before showing
	the window should be loaded in Game constructor
*/
void Game::Load() {
	//load textures
	if (!mTexture.loadFromFile("Resources/Textures/Eagle.png"))
	{
		// Handle loading error
	}

	//load fonts
	mFont.loadFromFile("Resources/Fonts/Sansation.ttf");

	//set up the fps counter
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);

	//load sounds
	mSoundManager.LoadFromFile("./Resources/Configs/SoundMap.config");

	//give player default weapon
	mPlayer.Create(&mSoundManager);

	mAsteroid = Asteroid();

}

void Game::Run() {

	Load();

	sf::Clock clock;
	sf::Time elapsed = sf::Time::Zero;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen()) {
		
		elapsed = clock.restart();
		timeSinceLastUpdate += elapsed;
		while(timeSinceLastUpdate > TimePerFrame) {

			timeSinceLastUpdate -= TimePerFrame;
			
			ProcessEvents();

			Update(TimePerFrame);
		}

		UpdateStatistics(elapsed);

		Render();
	}
}

//move this to a helpers file / class / namespace / library
template<typename T>
std::string toString(const T& value) {
	std::stringstream stream;
	stream << value;
	return stream.str();
}

void Game::UpdateStatistics(sf::Time elapsedTime) {

	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f)) {

		mStatisticsText.setString(
			"Frames / Second = " + toString(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us" + "\n" +
			"Ship Angle = " + toString(mPlayer.GetRotation()) + "\n" +
			"Ship Flying Angle = " + toString(mPlayer.FlyingAngle) + "\n" +
			"Ship Position = " + toString(mPlayer.GetPosition().x) + "," + toString(mPlayer.GetPosition().y) + "\n" +
			"Ship Speed = " + toString(mPlayer.Speed));

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}

}

void Game::ProcessEvents() {

	sf::Event event;
	while (mWindow.pollEvent(event)) {

		switch(event.type) {

		case sf::Event::KeyPressed:
			if(event.key.code == sf::Keyboard::Escape)
				mWindow.close();
			else if(event.key.code == sf::Keyboard::Space) {
				mPlayer.Shoot();
			}
			else
				HandlePlayerInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			HandlePlayerInput(event.key.code, false);
			break;

		case sf::Event::Closed:
			mWindow.close();
			break;

		}
	}
}

void Game::HandlePlayerInput(sf::Keyboard::Key key, bool isPressed) {

	mPlayer.HandlePlayerInput(key, isPressed);
/*
	if(key == sf::Keyboard::Up)
		mIsMovingUp = isPressed;
	else if(key == sf::Keyboard::Down)
		mIsMovingDown = isPressed;
	else if(key == sf::Keyboard::Left)
		mIsRotatingLeft = isPressed;
	else if(key == sf::Keyboard::Right)
		mIsRotatingRight = isPressed;
*/


	/*if(mIsMovingUp) {
		if(mPlayer.MoveSound.getStatus() != sf::Sound::Playing) {
			mPlayer.MoveSound.play();
		}
	}
	else {
		mPlayer.MoveSound.stop();
	}*/
}

void Game::HandleOffScreenObjects() {

	float x = mPlayer.GetPosition().x;
	float y = mPlayer.GetPosition().y;
	float maxX = mWindow.getSize().x;
	float maxY = mWindow.getSize().y;

	if (x < 0)
		mPlayer.SetPosition(maxX, y);
	else if (x > maxX)
		mPlayer.SetPosition(0,y);
	if (y < 0)
		mPlayer.SetPosition(x, maxY);
	else if (y > maxX)
		mPlayer.SetPosition(x,0);

	x = mAsteroid.GetPosition().x;
	y = mAsteroid.GetPosition().y;

	if (x < 0)
		mAsteroid.SetPosition(maxX, y);
	else if (x > maxX)
		mAsteroid.SetPosition(0,y);
	if (y < 0)
		mAsteroid.SetPosition(x, maxY);
	else if (y > maxX)
		mAsteroid.SetPosition(x,0);
}


void Game::Update(sf::Time deltaTime) {

	mPlayer.update(deltaTime);
	mAsteroid.update(deltaTime);

	HandleOffScreenObjects();

}

void Game::Render() {

	mWindow.clear();

	mWindow.draw(mPlayer);
	mWindow.draw(mAsteroid);

	mWindow.draw(mStatisticsText);

	mWindow.display();

}
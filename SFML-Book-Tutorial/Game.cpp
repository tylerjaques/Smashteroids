#include "Game.h"
#include <string>
#include <sstream>
#include <iostream>
#define _USE_MATH_DEFINES // for C++
#include <cmath>

//const initializers
const float Game::PlayerSpeed = 250.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);
const float PI = std::atan(1.0f) * 4.0f;

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
	mPlayer.Create(mSoundManager["drill"], mSoundManager["lazer"]);
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
			"Ship Angle = " + toString(mPlayer.getRotation()) + "\n" +
			"Ship Flying Angle = " + toString(mPlayer.FlyingAngle) + "\n" +
			"Ship Position = " + toString(mPlayer.getPosition().x) + "," + toString(mPlayer.getPosition().y) + "\n" +		
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

	if(key == sf::Keyboard::Up)
		mIsMovingUp = isPressed;
	else if(key == sf::Keyboard::Down)
		mIsMovingDown = isPressed;
	else if(key == sf::Keyboard::Left)
		mIsRotatingLeft = isPressed;
	else if(key == sf::Keyboard::Right)
		mIsRotatingRight = isPressed;

	if(mIsMovingUp) {
		if(mPlayer.MoveSound.getStatus() != sf::Sound::Playing) {
			mPlayer.MoveSound.play();
		}
	}
	else {
		mPlayer.MoveSound.stop();
	}
}

void Game::HandleOffScreenObjects() {
	float x = mPlayer.getPosition().x;
	float y = mPlayer.getPosition().y;
	float maxX = mWindow.getSize().x;
	float maxY = mWindow.getSize().y;

	if (x < 0)
		mPlayer.setPosition(maxX, y);
	else if (x > maxX)
		mPlayer.setPosition(0,y);
	if (y < 0)
		mPlayer.setPosition(x, maxY);
	else if (y > maxX)
		mPlayer.setPosition(x,0);
}


void Game::Update(sf::Time deltaTime) {

	float speed = mPlayer.Speed * deltaTime.asSeconds();

	float rotation = 0;
	
	if (mIsMovingUp) {
		mPlayer.Accelerate();		
		mPlayer.FlyingAngle = mPlayer.getRotation();
		float angle = mPlayer.getRotation() * (PI/180.0f);
		mPlayer.trans.translate(std::cos(angle)*(speed),std::sin(angle)*(speed));
	}

	if (mIsRotatingLeft)
		rotation -= PlayerSpeed * deltaTime.asSeconds();

	if (mIsRotatingRight)
		rotation += PlayerSpeed * deltaTime.asSeconds();
	
	float angle = mPlayer.FlyingAngle * (PI/180.0f);
		mPlayer.move(std::cos(angle)*(speed),std::sin(angle)*(speed));		

	mPlayer.ApplyResistance(10.0f);
	mPlayer.rotate(rotation);

	HandleOffScreenObjects();

}

void Game::Render() {

	mWindow.clear();

	mWindow.draw(mPlayer);

	mWindow.draw(mStatisticsText);

	mWindow.display();

}
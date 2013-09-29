#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__
#include "ConfigMap.h"
#include <string>
#include <map>
#include <SFML/Audio.hpp>
#include <memory>

class SoundManager {

private:
	Config::ConfigMap mFileMap;
	std::map<std::string, sf::SoundBuffer> mSoundBuffMap;

public:
	SoundManager();
	SoundManager(std::string filepath);

	void LoadFromFile(std::string filepaths);

	void Play(std::string name);

	sf::SoundBuffer& get(std::string name);

	const sf::SoundBuffer& get(std::string name) const;
};
#endif
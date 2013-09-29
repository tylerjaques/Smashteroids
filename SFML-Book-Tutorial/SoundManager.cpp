#include "SoundManager.h"

SoundManager::SoundManager() { }

SoundManager::SoundManager(std::string filepath) {
	LoadFromFile(filepath);
}

void SoundManager::LoadFromFile(std::string filepath) {

	mFileMap.LoadFromFile(filepath);

	for(std::pair<string, string> mapping : mFileMap) {

		sf::SoundBuffer buffer;

		if(!buffer.loadFromFile(mapping.second))
		{
			std::string exstr = "Failed to load sound " + mapping.first + " at " + mapping.second;
			throw exception(exstr.c_str());
		}
		else
			mSoundBuffMap[mapping.first] = buffer;

	}
}

sf::SoundBuffer& SoundManager::get(std::string name) {
	return mSoundBuffMap[name];
}

const sf::SoundBuffer& SoundManager::get(std::string name) const {
	return mSoundBuffMap.at(name);
}
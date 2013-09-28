#include "Weapon.h"

Weapon::Weapon(unsigned dmg, sf::SoundBuffer& sndBuff, sf::Texture* txptr) {

	Damage = dmg;

	Sound.setBuffer(sndBuff);

	TexturePtr = txptr;
}

Weapon::~Weapon() {
	delete TexturePtr;
}
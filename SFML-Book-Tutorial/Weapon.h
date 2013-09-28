#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Weapon {

public:
	unsigned Damage;
	sf::Sound Sound;
	sf::Texture* TexturePtr;

	Weapon(unsigned dmg, sf::SoundBuffer& sndBuffer, sf::Texture* txptr);
	~Weapon();
};
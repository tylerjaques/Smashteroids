#include <map>
#include <SFML/Graphics.hpp>

class TextureManager : std::map<std::string, sf::Texture> {

public:
	sf::Texture& operator[](std::string name);
	const sf::Texture& operator[](std::string name) const;

};
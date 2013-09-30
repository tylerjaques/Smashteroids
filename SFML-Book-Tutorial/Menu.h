#ifndef __MENU_H__
#define __MENU_H__
#include "ConfigMap.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Menu : sf::Drawable {
private:
	bool gameStarted;
	bool isVisible;
	std::vector<sf::Text> menuItems;
	sf::Font font;
	sf::Text mnuItem;
	const ConfigMap* options;
	sf::RectangleShape bRect;

public:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	Menu();
	void Show();
	void Hide();
	bool Visible();
	void SetOptions(const ConfigMap* mapptr);
};
#endif
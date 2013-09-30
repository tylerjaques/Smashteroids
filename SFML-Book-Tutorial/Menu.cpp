#include "Menu.h"

Menu::Menu() : gameStarted(false), isVisible(false) { }

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for(sf::Text txt : menuItems)
		target.draw(txt);

	target.draw(bRect);
}

void Menu::Show() { isVisible = true; }
void Menu::Hide() { isVisible = false; }
bool Menu::Visible() { return isVisible; }

void Menu::SetOptions(const ConfigMap* mapptr) {
	options = mapptr;

	font.loadFromFile("Resources/Fonts/Sansation.ttf");
	
	mnuItem.setFont(font);
	mnuItem.setCharacterSize(18);
	mnuItem.setString("menu!");


	//set origin
	//mnuItem.setOrigin(boundingBox.width / 2.0f, top);
	mnuItem.setOrigin( floor(mnuItem.getLocalBounds().width /2) , floor(mnuItem.getLocalBounds().height /2 ));

	//configure bounding box
	bRect.setSize(sf::Vector2f(mnuItem.getLocalBounds().width, mnuItem.getLocalBounds().height));
	bRect.setFillColor(sf::Color::Transparent);
	bRect.setOutlineColor(sf::Color::White);
	bRect.setOutlineThickness(1);
	bRect.setOrigin( floor(bRect.getLocalBounds().width /2) , floor(bRect.getLocalBounds().height /2 ));

	//get centre of screen
	int x = options->getAs<int>("width") / 2;
	int y = options->getAs<int>("height") / 2;
	mnuItem.setPosition(x, y);
	bRect.setPosition(x, y);

	mnuItem.setColor(sf::Color::White);
	menuItems.push_back(mnuItem);

}
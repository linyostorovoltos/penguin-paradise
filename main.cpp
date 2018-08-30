#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main()
{

	sf::RenderWindow window(sf::VideoMode(870, 630), "Experimental Penguins Rewritten", sf::Style::Titlebar | sf::Style::Close);

  sf::Image icon;
  icon.loadFromFile("images/icon.png");
  window.setIcon(32,32, icon.getPixelsPtr());
	
	// run the program as long as the window is open 
	sf::Texture penguinTexture;
	sf::Texture backTexture;

	penguinTexture.loadFromFile("images/penguin.png");
	penguinTexture.setSmooth(true);
	backTexture.loadFromFile("images/background.png");

	float playScale = 0.2f;
	sf::Sprite penguin;
	sf::Sprite background;

	penguin.setTexture(penguinTexture);
	penguin.setOrigin(sf::Vector2f(329 * 0.5f, 341 * 0.5f));
	penguin.setScale(sf::Vector2f(playScale, playScale));

	background.setTexture(backTexture);

	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Right || event.mouseButton.button == sf::Mouse::Left)
				{
					penguin.setPosition(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
				}
			default:
				break;
			}

			window.clear();
			window.draw(background);
			window.draw(penguin);
			window.display();
		}
	}

	return 0;
}

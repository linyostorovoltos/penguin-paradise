#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

int main() {
	// creates window object
	sf::RenderWindow window(sf::VideoMode(870, 630), "Experimental Penguins Rewritten", sf::Style::Titlebar | sf::Style::Close);

	sf::Music song;
	song.openFromFile("music/music.ogg");
	song.setLoop(true);
	song.setVolume(40);
	song.play();
	bool isSongPlaying = true;

	// sets icon of window
	sf::Image icon;
	icon.loadFromFile("images/icon.png");
	window.setIcon(64, 64, icon.getPixelsPtr());

	// creates textures
	sf::Texture penguinTexture;
	sf::Texture backTexture;
	sf::Texture volumeTexture;
	sf::Texture mutedTexture;
	// loads image dependencies and sets smooth textures
	penguinTexture.loadFromFile("images/penguin.png");
	penguinTexture.setSmooth(true);
	backTexture.loadFromFile("images/background.png");
	volumeTexture.loadFromFile("images/volume.png");
	mutedTexture.loadFromFile("images/mute.png");


	//sets scale
	float playScale = 0.2f;

	//creates sprites
	sf::Sprite penguin;
	sf::Sprite background;
	sf::Sprite volume;
	//associates sprites with textures
	// also deals with origin and scaling
	penguin.setTexture(penguinTexture);
	penguin.setOrigin(sf::Vector2f(329 * 0.5f, 341 * 0.5f));
	penguin.setScale(sf::Vector2f(playScale, playScale));
	penguin.setPosition(sf::Vector2f(870/2, 630/2));

	background.setTexture(backTexture);
	volume.setTexture(volumeTexture);
	volume.setPosition(sf::Vector2f(800,20));

	while (window.isOpen()) {
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
					sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
					sf::FloatRect bounds = volume.getGlobalBounds();

					if (bounds.contains(mouse))
					{
						if (isSongPlaying == true)
						{
							song.pause();
							volume.setTexture(mutedTexture);
							isSongPlaying = false;
						}

						else if (isSongPlaying == false)
						{
							song.play();
							volume.setTexture(volumeTexture);
							isSongPlaying = true;
						}
					}
					else
					{
						penguin.setPosition(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
					}
				}
			default:
				break;
			}

			window.clear();
			window.draw(background);
			window.draw(volume);
			window.draw(penguin);
			window.display();
		}
	}

	return 0;
}

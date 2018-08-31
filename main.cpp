#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <string>

int main() {
	// creates window object
	sf::RenderWindow window(sf::VideoMode(870, 630), "Experimental Penguins Rewritten", sf::Style::Titlebar | sf::Style::Close);

	int i = 0;
	int songnumber = 2;
	std::string songlist[2] = {"music/elite.ogg", "music/holiday2011music.ogg"};
	sf::Music song;
	song.openFromFile(songlist[i]);
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
	sf::Texture firstRoomTexture;
	sf::Texture secondRoomTexture;
	sf::Texture volumeTexture;
	sf::Texture mutedTexture;
	sf::Texture starTexture;
	sf::Texture rightSignTexture;
	sf::Texture leftSignTexture;

	// loads image dependencies and sets smooth textures
	penguinTexture.loadFromFile("images/penguin.png");
	penguinTexture.setSmooth(true);

	firstRoomTexture.loadFromFile("images/firstroom.png");
	secondRoomTexture.loadFromFile("images/secondroom.png");

	volumeTexture.loadFromFile("images/volume.png");
	mutedTexture.loadFromFile("images/mute.png");
	starTexture.loadFromFile("images/skip.png");

	rightSignTexture.loadFromFile("images/rightsign.png");
	leftSignTexture.loadFromFile("images/leftsign.png");



	//sets scale
	float playScale = 0.25f;

	//creates sprites
	sf::Sprite penguin;
	sf::Sprite background;
	sf::Sprite volume;
	sf::Sprite star;
	sf::Sprite rightSign;
	sf::Sprite leftSign;

	//associates sprites with textures
	// also deals with origin and scaling
	penguin.setTexture(penguinTexture);
	penguin.setOrigin(sf::Vector2f(329 * 0.5f, 341 * 0.5f));
	penguin.setScale(sf::Vector2f(playScale, playScale));
	penguin.setPosition(sf::Vector2f(870/2, 630/2));

	background.setTexture(firstRoomTexture);

	volume.setTexture(volumeTexture);
	volume.setPosition(sf::Vector2f(800,20));

	star.setTexture(starTexture);
	star.setPosition(sf::Vector2f(750,20));

	rightSign.setTexture(rightSignTexture);
	rightSign.setPosition(sf::Vector2f(696,478));

	leftSign.setTexture(leftSignTexture);
	leftSign.setPosition(sf::Vector2f(50,476));
	leftSign.setColor(sf::Color::Transparent);

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
					sf::FloatRect skipbounds = star.getGlobalBounds();
					sf::FloatRect volumebounds = volume.getGlobalBounds();
					sf::FloatRect rightsignbounds = rightSign.getGlobalBounds();
					sf::FloatRect leftsignbounds = leftSign.getGlobalBounds();

					if (volumebounds.contains(mouse))
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
					else if (skipbounds.contains(mouse))
					{
						if (i >= songnumber - 1)
						{
							i = 0;
							song.stop();
							song.openFromFile(songlist[i]);
							isSongPlaying = true;
							volume.setTexture(volumeTexture);
							song.play();
						}
						else
						{
							i++;
							song.stop();
							song.openFromFile(songlist[i]);
							isSongPlaying = true;
							volume.setTexture(volumeTexture);
							song.play();
						}
					}
					else if (rightsignbounds.contains(mouse))
					{
						background.setTexture(secondRoomTexture);
						rightSign.setColor(sf::Color::Transparent);
						leftSign.setColor(sf::Color::White);

					}
					else if(leftsignbounds.contains(mouse))
					{
						background.setTexture(firstRoomTexture);
						rightSign.setColor(sf::Color::White);
						leftSign.setColor(sf::Color::Transparent);
					}

					else
						penguin.setPosition(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
				}
			default:
				break;
			}

			window.clear();
			window.draw(background);
			window.draw(rightSign);
			window.draw(leftSign);
			window.draw(volume);
			window.draw(star);
			window.draw(penguin);
			window.display();
		}
	}

	return 0;
}

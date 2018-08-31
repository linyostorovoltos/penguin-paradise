#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <string>

int main() {
	// creates window object
	sf::RenderWindow window(sf::VideoMode(870, 630), "Experimental Penguins Rewritten", sf::Style::Titlebar | sf::Style::Close);

	sf::View game;
	sf::View map;
	std::string currentView;

	game.setCenter(sf::Vector2f(870/2, 630/2));
	game.setSize(sf::Vector2f(870, 630));


	map.setCenter(sf::Vector2f(870/2, 630/2));
	map.setSize(sf::Vector2f(870*0.7f, 630*.7f));


	window.setView(game);
	currentView = "game";

	int i = 0;
	int songnumber = 2;
	std::string songlist[2] = {"music/epf.ogg", "music/holiday2011music.ogg"};
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
	int penguinWidth = 469;
	int penguinLength = 514;
	int currentSprite = 1;

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
	float playScale = 0.2f;

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
	penguin.setTextureRect(sf::IntRect(0,0, penguinWidth, penguinLength));
	penguin.setOrigin(sf::Vector2f(penguinWidth * 0.5f, penguinLength * 0.5f));
	penguin.setScale(sf::Vector2f(playScale, playScale));
	penguin.setPosition(sf::Vector2f(870/2, 630/2));

	background.setTexture(firstRoomTexture);
	int room = 1;
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
						if (room == 1)
						{
							room++;
							background.setTexture(secondRoomTexture);
							rightSign.setColor(sf::Color::Transparent);
							leftSign.setColor(sf::Color::White);
							penguin.setPosition(sf::Vector2f(870 / 2, 630 / 2));
						}
						else if (room == 2)
						{
							penguin.setPosition(mouse);
						}
					}
					else if(leftsignbounds.contains(mouse))
					{
						if (room == 2)
						{
							room = room - 1;
							background.setTexture(firstRoomTexture);
							rightSign.setColor(sf::Color::White);
							leftSign.setColor(sf::Color::Transparent);
							penguin.setPosition(sf::Vector2f(870 / 2, 630 / 2));
						}
						else if (room == 1){
							penguin.setPosition(mouse);
						}
					}

					else{
						penguin.setPosition(mouse);
					}
				}
			default:
				break;
			}

			window.clear();
			if (currentView == "game")
			{
				window.draw(background);
				window.draw(rightSign);
				window.draw(leftSign);
				window.draw(volume);
				window.draw(star);
				window.draw(penguin);
			}

			else if (currentView == "map")
			{
				std::cout << "Yes!" << std::endl;
			}

			window.display();
		}
	}

	return 0;
}

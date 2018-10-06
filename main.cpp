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

	game.setCenter(sf::Vector2f(870 / 2, 630 / 2));
	game.setSize(sf::Vector2f(870, 630));


	map.setCenter(sf::Vector2f(870 / 2, 630 / 2));
	map.setSize(sf::Vector2f(870, 630));


	window.setView(game);
	currentView = "game";

	int i = 0;
	int songnumber = 3;

	std::string songlist[3] = { "music/epf.ogg", "music/holiday2011music.ogg", "music/eventprep.ogg" };
	sf::Music song;
	song.openFromFile(songlist[i]);
	song.setLoop(true);
	song.setVolume(40);
	song.play();
	bool isSongPlaying = true;

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
	sf::Texture mapButtonTexture;
	sf::Texture mapTexture;
	sf::Texture mapExitTexture;

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

	mapButtonTexture.loadFromFile("images/mapbutton.png");
	mapTexture.loadFromFile("images/map.png");

	mapExitTexture.loadFromFile("images/mapexitbutton.png");

	sf::RectangleShape townOverlay(sf::Vector2f(219, 97));

	sf::Font arial;
	arial.loadFromFile("images/arial.ttf");

	//sets scale
	float playScale = 0.2f;

	//creates sprites
	sf::Sprite penguin;
	sf::Sprite background;
	sf::Sprite volume;
	sf::Sprite star;
	sf::Sprite rightSign;
	sf::Sprite leftSign;
	sf::Sprite mapButton;
	sf::Sprite mapSprite;
	sf::Sprite mapExit;

	//associates sprites with textures
	// also deals with origin and scaling
	penguin.setTexture(penguinTexture);
	penguin.setOrigin(sf::Vector2f(penguinWidth * 0.5f, penguinLength * 0.5f));
	penguin.setScale(sf::Vector2f(playScale, playScale));
	penguin.setPosition(sf::Vector2f(870 / 2, 630 / 2));

	mapButton.setPosition(sf::Vector2f(14, 546));

	mapSprite.setTexture(mapTexture);

	mapExit.setTexture(mapExitTexture);
	mapExit.setPosition(sf::Vector2f(812, 57));

	background.setTexture(firstRoomTexture);

	mapButton.setTexture(mapButtonTexture);

	int room = 1;
	volume.setTexture(volumeTexture);
	volume.setPosition(sf::Vector2f(800, 20));

	star.setTexture(starTexture);
	star.setPosition(sf::Vector2f(750, 20));

	townOverlay.setPosition(219, 316);
	townOverlay.setFillColor(sf::Color::Transparent);


	rightSign.setTexture(rightSignTexture);
	rightSign.setPosition(sf::Vector2f(696, 478));

	leftSign.setTexture(leftSignTexture);
	leftSign.setPosition(sf::Vector2f(100, 476));
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
					sf::FloatRect mapbuttonbounds = mapButton.getGlobalBounds();
					sf::FloatRect mapexitbounds = mapExit.getGlobalBounds();
					sf::FloatRect townOverlayBounds = townOverlay.getGlobalBounds();

					if (volumebounds.contains(mouse))
					{
						if (isSongPlaying == true)
						{
							if (currentView == "game") {
								song.pause();
								volume.setTexture(mutedTexture);
								isSongPlaying = false;
							}

						}

						else if (isSongPlaying == false)
						{
							if (currentView == "game") {
								song.play();
								volume.setTexture(volumeTexture);
								isSongPlaying = true;
							}

						}
					}
					else if (skipbounds.contains(mouse))
					{
						if (i >= songnumber - 1)
						{
							if (currentView == "game") {
								i = 0;
								song.stop();
								song.openFromFile(songlist[i]);
								isSongPlaying = true;
								volume.setTexture(volumeTexture);
								song.play();
							}
						}
						else
						{
							if (currentView == "game") {
								i++;
								song.stop();
								song.openFromFile(songlist[i]);
								isSongPlaying = true;
								volume.setTexture(volumeTexture);
								song.play();
							}

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
					else if (leftsignbounds.contains(mouse))
					{
						if (room == 2)
						{
							room = room - 1;
							background.setTexture(firstRoomTexture);
							rightSign.setColor(sf::Color::White);
							leftSign.setColor(sf::Color::Transparent);
							penguin.setPosition(sf::Vector2f(870 / 2, 630 / 2));
						}
						else if (room == 1) {
							penguin.setPosition(mouse);
						}
					}

					else if (mapbuttonbounds.contains(mouse))
					{
						window.setView(map);
						currentView = "map";
					}

					else if (mapexitbounds.contains(mouse)) {
						window.setView(game);
						currentView = "game";
					}

					else if (townOverlayBounds.contains(mouse)) {
						if (currentView == "map") {
							window.setView(game);
							currentView = "game";
							if (room == 1) {
								room++;
								background.setTexture(secondRoomTexture);
								rightSign.setColor(sf::Color::Transparent);
								leftSign.setColor(sf::Color::White);
								penguin.setPosition(sf::Vector2f(870 / 2, 630 / 2));
							}
						}

						else {
							penguin.setPosition(mouse);
						}
					}

					else {
						penguin.setPosition(mouse);
					}
				}
			default:
				break;
			}


			if (currentView == "game")
			{
				window.draw(background);
				window.draw(rightSign);
				window.draw(leftSign);
				window.draw(mapButton);
				window.draw(penguin);
				window.draw(volume);
				window.draw(star);
			}

			else if (currentView == "map")
			{
				window.draw(mapSprite);
				window.draw(mapExit);
				window.draw(townOverlay);
			}

			window.display();
		}


		window.clear();
	}

	return 0;
}

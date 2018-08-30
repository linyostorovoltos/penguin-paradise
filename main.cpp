#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


int main()
{
    sf::RenderWindow window(sf::VideoMode(870, 630), "Penguin Paradise");
    // run the program as long as the window is open
    sf::Texture penguintexture;
    penguintexture.loadFromFile("images/penguin.png");

    float playscale = 0.2f;

    sf::Sprite penguin;
    penguin.setTexture(penguintexture);
    penguin.setOrigin(sf::Vector2f(658*0.5f, 651*0.5f));

    penguin.setScale(sf::Vector2f(playscale, playscale));


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
                std::cout << "Mouse is at " << event.mouseButton.x << "," << event.mouseButton.y << std::endl;
                penguin.setPosition(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
              }
            default:
              break;
          }

          window.clear();
          window.draw(penguin);
          window.display();
        }
    }

    return 0;
}

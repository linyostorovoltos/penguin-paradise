#include <iostream>
#include <SFML/Graphics.hpp>


int main()
{
    sf::RenderWindow window(sf::VideoMode(2560, 1440), "Penguin Paradise");
    // run the program as long as the window is open
    sf::Texture penguintexture;
    penguintexture.loadFromFile("images/penguin.png");

    sf::Sprite penguin;
    penguin.setTexture(penguintexture);

    penguin.scale(sf::Vector2f(1.0f, 0.5f));

    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while (window.pollEvent(event))
        {
          switch (event.type)
          {
            case sf::Event::MouseButtonPressed:
              std::cout << "" << std::endl;
              if (event.mouseButton.button == sf::Mouse::Right)
              {
                std::cout << "Mouse is at " << event.mouseButton.x << "," << event.mouseButton.y << std::endl;
              }

            case sf::Event::Closed:
              window.close();
              break;
          }

          window.clear();
          window.draw(penguin);
          window.display();
        }
    }

    return 0;
}

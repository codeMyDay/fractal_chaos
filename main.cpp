#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    sf::RenderWindow window(sf::VideoMode(700, 700), "Chaos");
    window.setFramerateLimit(30);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) window.close();
        }
        window.clear();

        window.display();
        usleep(100000);
    }

    return 0;
}
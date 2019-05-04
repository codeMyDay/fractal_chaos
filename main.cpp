#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <unistd.h>
#include "vec2.hpp"

void glVertex2v(vec2 v)
{
    glVertex2f(v.x, v.y);
}

int main(int argc, char **argv)
{
    vec2 v0(1.f, 1.f);
    vec2 v1(0.4f, -0.2f);

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

        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINES);
        glVertex2v(v0);
        glVertex2v(v1);
        glEnd();

        window.display();
        usleep(100000);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) window.close();
    }

    return 0;
}
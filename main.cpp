#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <unistd.h>
#include "vec2.hpp"

#include <vector>

#include <iostream>

void glVertex2v(vec2 v)
{
    glVertex2f(v.x, v.y);
}

void drawVectorPoints(std::vector<vec2> *v)
{
    glBegin(GL_POINTS);
    for(int i=0; i<v->size(); i++)
        glVertex2v(v->at(i));
    glEnd();
}

int main(int argc, char **argv)
{
    std::vector<vec2> initial_points;
    initial_points.push_back(vec2(-1.0, 1.0));
    initial_points.push_back(vec2(0.0, 1.0));
    initial_points.push_back(vec2(1.0, 1.0));
    initial_points.push_back(vec2(-1.0, -1.0));
    initial_points.push_back(vec2(0.0, -1.0));
    initial_points.push_back(vec2(1.0, -1.0));
    initial_points.push_back(vec2(-1.0, 0.0));
    initial_points.push_back(vec2(1.0, 0.0));

    int initial_points_count = initial_points.size();

    float delay = 100;

    int inc_point_size = 5;

    sf::Clock delay_timer;

    std::vector<vec2> points;
    points.push_back(vec2(rand()%3-1, rand()%3-1));

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

        if(delay_timer.getElapsedTime().asMicroseconds() > delay)
        {
            for(int i=0; i<inc_point_size; i++)
            {
                int rand_point = rand()%initial_points_count;

                vec2 new_point = (points[points.size()-1] + 2*initial_points[rand_point])/3.f;

                points.push_back(new_point);
            }

            delay_timer.restart();
        }

        drawVectorPoints(&initial_points);
        drawVectorPoints(&points);

        window.display();
        usleep(10000);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) window.close();
    }

    return 0;
}
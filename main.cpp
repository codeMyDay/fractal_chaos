#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <unistd.h>
#include "vec2.hpp"
#include <cstdlib>
#include <time.h>
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

void addPoints(std::vector<vec2> *initial_points, std::vector<vec2> *points, int add_points_count)
{
    for(int i=0; i<add_points_count; i++)
        {
            int rand_point = rand()%initial_points->size();

            vec2 new_point = (points->at(points->size()-1) + 2.0*initial_points->at(rand_point))/3.f;

            points->push_back(new_point);
        }
}

void addMiddlePoints(std::vector<vec2> *points)
{
    int points_count = points->size();

    for(int i=0; i<points_count-1; i++)
    {
        vec2 middle = (points->at(i) + points->at(i+1))/2.0;
        points->push_back(middle);
    }

    vec2 middle = (points->at(0) + points->at(points_count-1))/2.0;
    points->push_back(middle);
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    std::vector<vec2> initial_points;

    float delay = 100;

    int add_points_count = 5;
    if(argc > 1)
        add_points_count = std::atoi(argv[1]);

    sf::Clock delay_timer;

    std::vector<vec2> points;
    points.push_back(vec2(rand()%3-1, rand()%3-1));

    sf::RenderWindow window(sf::VideoMode(700, 700), "Chaos");
    window.setFramerateLimit(30);

    bool is_points_input_end = false;
    bool mouse_left_pressed = false;
    bool space_pressed = false;

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) window.close();
        }
        window.clear();

        if(!is_points_input_end)
        {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouse_left_pressed)
            {
                sf::Vector2i mouse_coords = sf::Mouse::getPosition(window);
                mouse_coords.y = window.getSize().y - mouse_coords.y;
                mouse_coords -= sf::Vector2i(window.getSize())/2;

                vec2 mouse_pos(mouse_coords.x/float(window.getSize().x/2.0), mouse_coords.y/float(window.getSize().y/2.0));

                if((abs(mouse_pos.x) <= 1.0) && (abs(mouse_pos.y) <= 1.0))
                    initial_points.push_back(mouse_pos);

                mouse_left_pressed = true;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !space_pressed)
            {
                addMiddlePoints(&initial_points);

                space_pressed = true;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                is_points_input_end = true;
            }

            if(mouse_left_pressed && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
                mouse_left_pressed = false;

            if(space_pressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                space_pressed = false;

            drawVectorPoints(&initial_points);
        }
        else
        {
            if(delay_timer.getElapsedTime().asMicroseconds() > delay)
            {
                addPoints(&initial_points, &points, add_points_count);

                delay_timer.restart();
            }

            drawVectorPoints(&initial_points);
            drawVectorPoints(&points);
        }

        window.display();
        usleep(10000);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) window.close();
    }

    return 0;
}
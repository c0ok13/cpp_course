#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
float chng = 0;
float xmax = 0;
float wp = 0;
int main()
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Simple Event Loop");
    sf::Clock clock;
    sf::Vector2f position = {10, 350};

    constexpr float BALL_SIZE = 40;
    sf::CircleShape shape(BALL_SIZE);
    shape.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

    float speedX = 100.f;
    float amplitudeY = 80.f;
    float periodY = 2;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        float time = clock.getElapsedTime().asSeconds();
        float wavePhase = wp - time * float(2 * M_PI);
        const float x = xmax + speedX * time;
        const float y = amplitudeY * std::sin(wavePhase / periodY);
        sf::Vector2f offset = {x, y};

        if (x + 2 * BALL_SIZE + 6 >= WINDOW_WIDTH)
        {
            xmax = x;
            clock.restart();
            speedX = -speedX;
            wp = wavePhase;
        }
        if (x + 10 < 0)
        {
            xmax = x;
            clock.restart();
            speedX = -speedX;
            wp = wavePhase;
        }
        shape.setPosition(position + offset);
        window.clear();
        window.draw(shape);
        window.display();
    }
}
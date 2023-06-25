#include <SFML/Graphics.hpp>

sf::RenderWindow gameWindow;

// Prototypes
void update();
void draw();

// Setup game loop interpolation
sf::Clock timer;
const int TICKS_PER_SECOND = 60;
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
const int MAX_FRAMESKIP = 5;
long next_game_tick = timer.getElapsedTime().asMilliseconds();
int loops = 0;
float interpolation = 0.0;

sf::CircleShape shape(100.f);

int main()
{
    gameWindow.create(sf::VideoMode(800, 600), "Moon Grandpa", sf::Style::Close);

    shape.setFillColor(sf::Color::Green);

    while (gameWindow.isOpen())
    {
        sf::Event event;
        while (gameWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                gameWindow.close();
            }
        }

        loops = 0;
        while (timer.getElapsedTime().asMilliseconds() > next_game_tick && loops < MAX_FRAMESKIP)
        {
            update();
            next_game_tick += SKIP_TICKS;
            loops++;
        }

        interpolation = float(timer.getElapsedTime().asMilliseconds() + SKIP_TICKS - next_game_tick) / float(SKIP_TICKS);
        draw();
    }

    return 0;
}

void update()
{
}

void draw()
{
    gameWindow.clear();
    gameWindow.draw(shape);
    gameWindow.display();
}
#if !defined(GAME_HPP)
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <grid.hpp>

class Game
{

public:
    Game();
    int run();
    void update();

public:
    static const int WINDOW_HEIGHT = 600, WINDOW_WIDTH = 600;

private:
    void update(sf::Time);
    void render();
    void processEvents();

private:
    sf::RenderWindow mWindow;
    int N_ROWS = 20, N_COLUMNS = 20;
    Grid mGrid;
    sf::Time timePerFrame = sf::seconds(1.f / 8.f);
};

#endif // GAME_HPP

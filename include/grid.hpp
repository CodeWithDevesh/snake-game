#if !defined(GRID_HPP)
#define GRID_HPP
#include <iostream>
#include <SFML/Graphics.hpp>
#include <gridCell.hpp>
#include <vector>

class Grid : public sf::Drawable
{
    friend class Game;

public:
    Grid(int rows, int columns);
    void setup();

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    int update();
    void changeDir(Direction dir);
    sf::Vector2i getNextCell(sf::Vector2i);
    void placeFood();

private:
    int nRows, nColumns;
    std::vector<std::vector<GridCell>> cells;
    std::vector<sf::Vector2i> snake;
    bool updated = false;
};

#endif // GRID_HPP

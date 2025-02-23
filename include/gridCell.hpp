#if !defined(GRID_CELL_HPP)
#define GRID_CELL_HPP

#include <SFML/Graphics.hpp>
#include <states.hpp>

class GridCell : public sf::Drawable
{
public:
    GridCell(sf::Vector2f size, sf::Vector2f pos);
    void setState(State state);
    void setDirection(Direction dir);
    Direction getDirection();
    State getState();

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    sf::Vector2f size, pos;
    sf::RectangleShape shape;
    Direction dir = NONE;
    State state = EMPTY;
};

#endif // GRID_CELL_HPP

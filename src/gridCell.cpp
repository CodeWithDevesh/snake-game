#include <gridCell.hpp>

GridCell::GridCell(sf::Vector2f size, sf::Vector2f pos) : shape(size)
{
    this->pos = pos;
    this->size = size;
    shape.setFillColor(sf::Color::Black);
    shape.setPosition(pos.x * size.x, pos.y * size.y);
    // shape.setOutlineColor(sf::Color::White);
    // shape.setOutlineThickness(5);
}

void GridCell::setState(State state)
{
    this->state = state;
    switch (state)
    {
    case EMPTY:
        shape.setFillColor(sf::Color::Black);
        break;
    case FOOD:
        shape.setFillColor(sf::Color::Yellow);
        break;
    default:
        shape.setFillColor(sf::Color::Blue);
        break;
    }
}

void GridCell::setDirection(Direction dir)
{
    this->dir = dir;
}

State GridCell::getState()
{
    return state;
}

Direction GridCell::getDirection()
{
    return dir;
}

void GridCell::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(shape, states);
}

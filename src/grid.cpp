#include <grid.hpp>
#include <game.hpp>

Grid::Grid(int rows, int columns)
{
    nRows = rows;
    nColumns = columns;
    sf::Vector2f size = sf::Vector2f(Game::WINDOW_WIDTH / columns, Game::WINDOW_HEIGHT / rows);

    for (int i = 0; i < rows; i++)
    {
        std::vector<GridCell> col;
        for (int j = 0; j < columns; j++)
            col.push_back(GridCell(size, sf::Vector2f(j, i)));
        cells.push_back(col);
    }
}

void Grid::setup()
{
    for (auto x : cells)
        for (auto y : x)
        {
            y.setState(EMPTY);
            y.setDirection(NONE);
        }

    snake = std::vector<sf::Vector2i>();
    cells[0][0].setState(TAIL);
    cells[0][0].setDirection(RIGHT);
    cells[0][1].setState(SNAKE);
    cells[0][1].setDirection(RIGHT);
    cells[0][2].setState(SNAKE);
    cells[0][2].setDirection(RIGHT);
    cells[0][3].setState(HEAD);
    cells[0][3].setDirection(RIGHT);
    snake.push_back(sf::Vector2i(3, 0));
    snake.push_back(sf::Vector2i(2, 0));
    snake.push_back(sf::Vector2i(1, 0));
    snake.push_back(sf::Vector2i(0, 0));

    placeFood();
}

void Grid::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto x : cells)
    {
        for (auto y : x)
        {
            target.draw(y, states);
        }
    }
}

int Grid::update()
{
    std::vector<sf::Vector2i> newPos;
    for (auto pos : snake)
    {
        sf::Vector2i nextPos = getNextCell(pos);
        updated = true;
        // If the snake collides with the food then increase its length and place food somewhere else
        if (cells[pos.y][pos.x].getState() == HEAD && cells[nextPos.y][nextPos.x].getState() == FOOD)
        {
            cells[nextPos.y][nextPos.x].setState(cells[pos.y][pos.x].getState());
            cells[nextPos.y][nextPos.x].setDirection(cells[pos.y][pos.x].getDirection());
            cells[pos.y][pos.x].setState(SNAKE);
            newPos.push_back(nextPos);
            newPos.push_back(pos);
            for (int i = 1; i < snake.size(); i++)
            {
                newPos.push_back(snake[i]);
            }
            snake = newPos;
            placeFood();
            return 0;
        }

        // The snake collides with itself
        if (cells[nextPos.y][nextPos.x].getState() != EMPTY)
            return -1;

        cells[nextPos.y][nextPos.x].setState(cells[pos.y][pos.x].getState());
        if (cells[pos.y][pos.x].getState() == HEAD)
            cells[nextPos.y][nextPos.x].setDirection(cells[pos.y][pos.x].getDirection());
        if (cells[pos.y][pos.x].getState() == TAIL)
            cells[pos.y][pos.x].setDirection(NONE);
        cells[pos.y][pos.x].setState(EMPTY);
        newPos.push_back(nextPos);
    }
    snake = newPos;
    return 0;
}

sf::Vector2i Grid::getNextCell(sf::Vector2i pos)
{
    GridCell cell = cells[pos.y][pos.x];

    switch (cell.getDirection())
    {
    case UP:
        return sf::Vector2i(pos.x, (pos.y == 0) ? nRows - 1 : pos.y - 1);
    case DOWN:
        return sf::Vector2i(pos.x, (pos.y == nRows - 1) ? 0 : pos.y + 1);
    case LEFT:
        return sf::Vector2i((pos.x == 0) ? nColumns - 1 : pos.x - 1, pos.y);
    case RIGHT:
        return sf::Vector2i((pos.x == nColumns - 1) ? 0 : pos.x + 1, pos.y);
    default:
        return pos;
    }
}

void Grid::changeDir(Direction dir)
{
    if (snake.empty() || !updated)
        return;
    if (cells[snake[0].y][snake[0].x].getDirection() * -1 == dir || cells[snake[0].y][snake[0].x].getDirection() == dir)
        return;
    cells[snake[0].y][snake[0].x].setDirection(dir);
    updated = false;
}

void Grid::placeFood()
{
    bool placed = false;
    while (!placed)
    {
        int x = std::rand() % nColumns;
        int y = std::rand() % nRows;
        placed = true;
        for (auto z : snake)
            if (z.x == x && z.y == y)
            {
                placed = false;
                break;
            }
        if(placed){
            cells[y][x].setState(FOOD);
        }
    }
}
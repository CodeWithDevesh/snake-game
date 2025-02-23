#include <game.hpp>

Game::Game() : mWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake", sf::Style::Titlebar | sf::Style::Close),
               mGrid(N_ROWS, N_COLUMNS)
{
    mWindow.setSize(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT));
    mWindow.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width - WINDOW_WIDTH) / 2, (sf::VideoMode::getDesktopMode().height - WINDOW_HEIGHT) / 2));
}

int Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    mGrid.setup();
    while (mWindow.isOpen())
    {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;
            processEvents();
            update(timePerFrame);
        }
        render();
    }

    return 0;
}

void Game::render()
{
    mWindow.clear();
    mWindow.draw(mGrid);
    mWindow.display();
}

void Game::update(sf::Time delta)
{
    if(mGrid.update() != 0){
        std::cout << "Game Over" << std::endl;
        mWindow.close();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            mWindow.close();
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::W:
                mGrid.changeDir(UP);
                break;
            case sf::Keyboard::S:
                mGrid.changeDir(DOWN);
                break;
            case sf::Keyboard::A:
                mGrid.changeDir(LEFT);
                break;
            case sf::Keyboard::D:
                mGrid.changeDir(RIGHT);
                break;
            default:
                break;
            }
        }
    }
}